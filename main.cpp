#include <iostream>
#include "node.h"
#include "stack.h"
#include "q.h"
#include <cstring>
#include <ctype.h>

q* shunt(q*, char*);
bool check(char, char);
void postfix(node*);
void prefix(node*);
void infix(node*);
node* buildtree(q* postfix);

using namespace std;

int main() {
  cout << "Welcome, Equation? \n";
  q* initial = new q();
  char* input = new char [100];
  cin.getline(input, 100);
  initial = shunt(initial, input);
  node* binary = buildtree(initial);
  cout << "Say which form you wish for it to be in \n";
  char* format = new char[100];
  cin.getline(format, 100);
  if (strcmp(format, "postfix") == 0) {
    postfix(binary);
    cout << endl; 
  }
  else if (strcmp(format, "infix") == 0) {
    infix(binary);
    cout << endl;
  }
  else if (strcmp(format, "prefix") == 0) {
    prefix(binary);
    cout << endl; 
  }
  
}

void infix(node* btree) {
  if ((*btree -> getData() == '+' || '-' || '*' || '/' || '^' )) {
    cout << "(";
  }
  if (btree -> getLeft() != NULL) {
    infix(btree->getLeft());
  }
  cout << btree -> getData() << "";
  if (btree -> getRight() != NULL) {
    infix(btree -> getRight()); 
  }
  if ((*btree -> getData() == '+' || '-' || '*' || '/' || '^')) {
    cout << ")";
  }
}

void prefix(node* btree) {
  if (btree != NULL) 
    cout << btree -> getData() << " ";
  {
    if (btree -> testLeft() == true) {
      prefix(btree -> getLeft()); 
    }
    if (btree -> testRight() == true) {
      prefix(btree -> getRight()); 
    }
  }
}

void postfix(node* btree) {
  if (btree != NULL) {
    if (btree -> getLeft() != NULL)  {
      postfix(btree -> getLeft()); 
    }
    if (btree -> getRight() != NULL) {
      postfix(btree -> getRight()); 
    }
    cout << btree -> getData() << " "; 
  }
}

q* shunt(q* post, char* infix) {
  stack* stack1 = NULL;
  for (int i = 0; i < strlen(infix); i++) {
    if (isdigit(infix[i]) == true) {
    char* data = new char[100];
    bool run = true;
    int init = i;
    data[0] = infix[i];
    while (run == true) {
      if(isdigit(infix[i+1])) {
	i = i+1;
	data[i - init] = infix[i]; 
      }
      else {
	run = false; 
      }
    }
    data[i+1] = '\0';
    node* nNode = new node(data);
    post -> enqueue(nNode); 
  }
  else if (infix[i] == '(') {
    char* para = new char[1];
    para[0] = '(';
    node* node2 = new node(para);
    if (stack1 == NULL) {
      stack1 = new stack(node2);
      //stack1 -> peek(); 
    }
    else {
      stack1 -> push(node2); 
    }
  }
  else if (infix[i] == ')') {
    bool remove = false;
    while (remove == false) {
      node* pop = stack1 -> pop();
      if (pop -> getData()[0] != '(') {
	post -> enqueue(pop);	
      }
      else {
	remove = true; 
      }
    }
  }
  else {
    if (stack1 == NULL) {
      char* data = new char[2];
      data[0] = infix[i];
      node* nNode = new node(data);
      stack1 = new stack(nNode); 
    }
    else {
      char* data = new char[2];
      data[0] = infix[i];
      node* nNode = new node(data);
      node* compare = stack1 -> pop();
      bool tt = true;
      int count = 0;
      if (compare != NULL) {
	tt = check(data[0], compare -> getData()[0]);
	if (tt == true) {
	  post -> enqueue(compare);
	  count++;
	  bool run = true;

	  while (run == true) {
	    count++;
	    node* qq = stack1 -> pop();
	    if(qq == NULL) {
	      run = false;
	    }
	    else if (check(data[0], qq -> getData()[0]) == false) {
	      stack1 -> push(qq);
	      run = false;
	    }
	    else {
	      post -> enqueue(qq); 
	    }
	  }
	}
      }
      if (count == 0) {
	stack1 -> push(compare);
      }
      stack1 -> push(nNode); 
    }
  }
 }

bool run = true;
while (run == true) {
  node* enq = stack1 -> pop();
  if (enq == NULL) {
    run = false;
  }
  else {
    post -> enqueue(enq);
  }
 }
return post;
}

node* buildtree(q* input) {
  stack* tree = new stack(NULL);
  while(input -> getQueueHd() != 0) {
    if(isdigit(*input->getQueueHd() -> getData())) {
      node* fill = new node(input -> getQueueHd() -> getData());
      tree -> push(fill);
      input -> dequeue();
    }
    else {
      node* current = new node(input -> getQueueHd() -> getData());
      current -> setRight(tree -> pop());
      current -> setLeft(tree -> pop());
      tree -> push(current);
      input -> dequeue();
    }
  }
  return tree -> peek();
}


bool check (char after, char before) {
  if ((after == '+' || after == '-') && (before == '/' || before == '*' || before == '^')) {
    return true;
  }
  else if ((after == '-' || after == '+') && (before == '-' || before == '+')) {
    return false; 
  }
  else if ((after == '/' || after == '*') && (before == '/' || before == '*')) {
    return false; 
  }
  else if ((after == '*' || after == '/') && before == '^') {
    return true;
  }
  else {
    return false;
  }
  
}
