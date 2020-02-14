//stack class file
#include "stack.h"
#include <iostream>

using namespace std;

stack::stack(node* newHead)  {
  head = newHead; 
}

void stack::push(node* add) {
  if (head != NULL) {
    node* current = head;
    while (current -> getNext() != NULL) {
      current = current -> getNext();
    }
    current -> setNext(add);
  }
  else {
    head = add;
  }
}

node* stack::pop() {
  node* current = head;
  node* Rtrn = NULL;
  if (current != NULL) {
    while (current -> getNext() != NULL && current -> getNext() -> getNext() != NULL) {
      current = current -> getNext(); 
    }
    if (current -> getNext() != NULL) {
      Rtrn = current -> getNext();
      current -> setNext(NULL); 
    }
    else {
      Rtrn = current;
      head = NULL;
    }
  }
  return Rtrn; 

}

node* stack::peek() {
  return head; 
} 

