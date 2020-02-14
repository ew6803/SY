//queue class file
#include "q.h"
#include <iostream>

using namespace std;

q::q() {
  qhead = NULL;
  qtail = NULL;

}

void q::enqueue(node* push) {
  if (qtail != NULL) {
    qtail->setNext(push);
    qtail = push; 
  }
  else {
    qhead = push;
    qtail = push; 
  }
}


node* q::dequeue() {
  node* rtrn = qhead;
  if (qhead != NULL) {
    qhead = qhead -> getNext();
  }
  if (qhead == NULL) {
    qtail = NULL;
  }
  return rtrn;
}

node* q::getQueueHd() {
  return qhead;
}
node* q::getQueueTl() {
  return qtail; 
}
