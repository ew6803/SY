#include "node.h"
#include <iostream>

node::node(char* sData) {
  data = sData;
  right = NULL;
  left = NULL;
  next = NULL;
}

node* node::getRight() {
  return right; 
}

node* node::getLeft() {
  return left; 
}

node* node::getNext() {
  return next; 
}
char* node::getData() {
  return data; 
}

void node::setRight(node* sRight) {
  right = sRight; 
}

void node::setLeft(node* sLeft) {
  left = sLeft; 
}

void node::setNext(node* sNext) {
  next = sNext; 
}

bool node::testRight() {
  if (right != NULL) {
    return true; 
  }
  return false; 
}

bool node::testLeft() {
  if (left != NULL) {
    return true; 
  }
  return false; 
}
