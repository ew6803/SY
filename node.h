#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>
using namespace std;

class node {
 public:
  node(char*);
  node* getRight();
  node* getLeft();
  node* getNext();
  char* getData(); 
  bool testRight();
  bool testLeft();
  void setRight(node*);
  void setLeft(node*);
  void setNext(node*);
  char* data;
  node* next;
  node* left;
  node* right; 
  


};
#endif 
