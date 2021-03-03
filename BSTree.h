//Ethan Pawl
//ejp190003

#ifndef BSTREE_H
#define BSTREE_H

#include "Node.h"
#include <iostream>

template <typename T>
class BSTree {
private:
   Node<T>* root;

   void insertTraversal(Node<T>&, Node<T>*); //helper method to implement recursion
   void deleteTraversal(T, Node<T>*&); //helper method to implement recursion
   void deleteNode(Node<T>*&); //helper method to actually delete the node once we have found the node to delete
   Node<T>* searchTraversal(T, Node<T>*); //helper method to implement recursion
   void printInOrderTraversal(Node<T>*); //helper method to implement recursion
public:
   BSTree() {root = nullptr;}
   BSTree(Node<T>* r) {root = r;}

   void setRoot(Node<T>* r) {root = r;}
   Node<T>* getRoot() const {return root;}

   void insert(Node<T>&);
   void treeDelete(T to_delete);
   Node<T>* search(T);
   void printInOrder();
};

template<typename T>
void BSTree<T>::insert(Node<T>& to_insert) { //pass in an already-constructed Node to insert
   if(!root) {
      root = &to_insert; //if the tree has no root, insert to_insert as the root
   }
   else {
      insertTraversal(to_insert, root);
   }
}

template<typename T>
void BSTree<T>::insertTraversal(Node<T>& to_insert, Node<T>* current_node) {
   if(to_insert > *current_node) { //if the payload to insert is greater than current_node's payload
      if(current_node->getRight()) { //if current_node has a right child
         insertTraversal(to_insert, current_node->getRight()); //call insertTraversal on the right subtree
      }
      else { //if current_node has no right child
         current_node->setRight(&to_insert); //make to_insert the right child of the current node
      }
   }
   else if(to_insert < *current_node) {//if the payload to insert is less than current node's payload
      if(current_node->getLeft()) { //if current_node has a left child
         insertTraversal(to_insert, current_node->getLeft()); //call insertTraversal on the left subtree
      }
      else { //if current_node has no left child
         current_node->setLeft(&to_insert); //make to_insert the left child of current_node
      }
   }
   //else do nothing (no insertion)
}

template<typename T>
void BSTree<T>::treeDelete(T to_delete) { //pass in a DVD to delete the Node which holds that same DVD
   deleteTraversal(to_delete, root);
}

template<typename T>
void BSTree<T>::deleteTraversal(T to_delete, Node<T>*& current_node) { //reference to a pointer because I want to modify the pointers IN the tree
   if(current_node) { //if the current node is not a nullptr
      if(to_delete < current_node->getPayload()) { //if the payload to delete is less than current node's payload
         deleteTraversal(to_delete, current_node->getLeft()); //call deleteTraversal on the left subtree
      }
      else if(to_delete > current_node->getPayload()) { //if the payload to delete is greater than current_node payload
         deleteTraversal(to_delete, current_node->getRight()); //call deleteTraversal on right subtree
      }
      else { //if we have found node to delete
         deleteNode(current_node); //delete the node
      }
   }
}

template<typename T>
void BSTree<T>::deleteNode(Node<T>*& current_node) { //reference to a pointer because I want to modify the pointers IN the tree
      Node<T>* temp_ptr = nullptr; //initialize a temporary pointer to reconfigure the tree after deletion
      if(current_node) {
         if(current_node->getLeft() == nullptr) {//if no left child
            temp_ptr = current_node;
            current_node = current_node->getRight(); //replace node to delete with its right child
            delete temp_ptr; //delete node we want to delete
         }
         else if(current_node->getRight() == nullptr) { //if no right child
            temp_ptr = current_node;
            current_node = current_node->getLeft(); //replace node to delete with its left child
            delete temp_ptr; //delete node we want to delete
         }
         else { //if the node has two children
            temp_ptr = current_node->getRight(); //set the temp pointer to be current_node's right child
            while(temp_ptr->getLeft()) {
               temp_ptr = temp_ptr->getLeft(); //move temp ptr to the leftmost ancestor in the right subtree
            }
            temp_ptr->setLeft(current_node->getLeft()); //attach the left child of current_node to the leftmost ancestor (making the left subtree a left subtree in the right subtree)
            temp_ptr = current_node; //point back to the current_node
            current_node = current_node->getRight(); //replace current_node with its right child
            delete temp_ptr; //delete the node we want to delete
         }
      }
   }

template<typename T>
Node<T>* BSTree<T>::search(T to_find) { //pass in a DVD and find the Node which holds that DVD
   Node<T>* found = nullptr; //this will store the location of the Node we are looking for, if we find it
   found = searchTraversal(to_find, root);
   return found;
}

template<typename T>
Node<T>* BSTree<T>::searchTraversal(T to_find, Node<T>* current_node) {
   Node<T>* found = nullptr; //this will store the location of the Node we are looking for, if we find it
   if(current_node) { //if the current node is not a nullptr
      if(to_find > current_node->getPayload()) { //if our value to find is greater than current node's payload
         found = searchTraversal(to_find, current_node->getRight()); //call searchTraversal on right subtree
      }
      else if(to_find < current_node->getPayload()) { //if our value to find is less than current node's payload
         found = searchTraversal(to_find, current_node->getLeft()); //call searchTraversal on left subtree
      }
      else { //if our current node is the one we are looking for
         found = current_node;
      }
   }

   return found;
 }

 template<typename T>
 void BSTree<T>::printInOrder() {
   printInOrderTraversal(root);
}

template<typename T>
void BSTree<T>::printInOrderTraversal(Node<T>* current_node) {
   if(current_node) { //if the current_node is not a nullptr
      printInOrderTraversal(current_node->getLeft()); //traverse left subtree
      std::cout << *current_node << std::endl; //output data in current_node
      printInOrderTraversal(current_node->getRight()); //traverse right subtree
   }
}


#endif // BSTREE_H
