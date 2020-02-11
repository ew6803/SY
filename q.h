#include "node.h"

class q {
 public: 
   q();
   void enqueue(node*);
   node* dequeue();
   node* getQueueHd();
   node* getQueueTl();
   node* qhead;
   node* qtail; 
};
