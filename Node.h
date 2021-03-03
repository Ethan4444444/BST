//Ethan Pawl
//ejp190003

#ifndef NODE_H
#define NODE_H

template <typename S>
class Node {
private:
   Node* left;
   Node* right;
   S payload;
public:
   Node() {left = nullptr; right = nullptr;}
   Node(S& p) {left = nullptr; right = nullptr; payload = p;}

   Node*& getLeft() {return left;}
   Node*& getRight() {return right;}
   S& getPayload() {return payload;}

   void setLeft(Node* l) {left = l;}
   void setRight(Node* r) {right = r;}
   void setPayload(S p) {payload = p;}

   bool operator>(Node& rhs) {return payload > rhs.payload;}
   bool operator<(Node& rhs) {return payload < rhs.payload;}
   bool operator==(Node& rhs) {return payload == rhs.payload;}

   friend std::ostream& operator<<(std::ostream& os, Node& rhs) {
      os << rhs.payload;
      return os;
   }
};

#endif // NODE_H
