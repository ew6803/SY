#include "node.h"
class stack {
 public:
  stack(node*);
  node* pop();
  node* peek();
  void push(node*);
  node* head; 
};
