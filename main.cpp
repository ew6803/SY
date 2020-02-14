/* This project is a shunting yard algorithim, it allows a user to enter a math equation in infix, convert it to postfix for a binary expression tree, and can output the function in prefix, infix, or postfix notation. 
Ethan Wang
2/13/19
*/

#include "node.h"
#include "stack.h"
#include "q.h"
#include <cstring>
#include <iostream>

using namespace std;
//Builds bunary tree with postfix expression
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
//Checks presedence
bool presedence(char after, char before) {
  if ((after == '+' || after == '-') && (before == '*' || before == '/' || before == '^')) {
    return true;
  }
  else if ((after == '*' || after == '/') && before == '^') {
    return true; 
  }
  else if ((after == '+' || after == '-') && (before == '+' || before == '-')) {
    return false; 
  }
  else if ((after == '*' || after == '/') && (before == '*' || before == '/')) {
    return false; 
  }
  else {
    return false;
  }
  
}
//Shunting Yard Algorithim, takes the infix equation and converts to postfix. 
q* shuntingyard(q* post, char* infix) {
  bool running = true; 
  stack* stack1 = NULL;
  for (int i = 0; i < strlen(infix); i++) {
    if (isdigit(infix[i]) == true) {
    char* data = new char[100];
    int init = i;
    data[0] = infix[i];
    node* nNode = new node(data);
    post -> enqueue(nNode); 
  }
    else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
    if (stack1 == NULL) {
      char* data = new char[1];
      data[0] = infix[i];
      node* nNode = new node(data);
      stack1 = new stack(nNode); 
      } 
    else { 
      char* data = new char[1];
      data[0] = infix[i];
      node* nNode = new node(data);
      node* compare = stack1 -> pop();
      if (compare != NULL) {
	if (presedence(data[0], compare -> getData()[0]) == true) {
	  post -> enqueue(compare);
	    node* qq = stack1 -> pop();
	    if (presedence(data[0], qq -> getData()[0]) == false) {
	      stack1 -> push(qq);
	    }
	    else {
	      post -> enqueue(qq); 
	    }
	}
      }
      stack1 -> push(compare);
      stack1 -> push(nNode); 
    }
  }
  else if (infix[i] == '(') {
    char* para = new char[1];
    para[0] = '(';
    node* node2 = new node(para);
    if (stack1 == NULL) {
      stack1 = new stack(node2);
      }
    else {
    stack1 -> push(node2);
    }
  }
  else if (infix[i] == ')') {
      node* pop = stack1 -> pop();
      if (pop -> getData()[0] != '(') {
	post -> enqueue(pop);	
      }
    pop = stack1 -> pop(); 
  }
    
  }
  while (running == true) {
    node* enq = stack1 -> pop();
  if (enq != NULL) {
    post -> enqueue(enq);
  }
  else {
     running = false; 
    }
  }  
  return post;
}

//Takes binary tree and outputs in infix notation
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

//Takes binary tree and outputs in prefix notation
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

//Takes binary tree and ouputs in postfix notation
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

//Main, UI and Function Caller
int main() {
  cout << "Welcome, Equation? Do not use Spaces\n";
  q* initial = new q();
  char* input = new char [100];
  cin.getline(input, 100);
  initial = shuntingyard(initial, input);
  node* binary = buildtree(initial);
  cout << "Say which form you wish for it to be in, postfix, infix, prefix? \n";
  char* format = new char[100];
  cin.getline(format, 100);
    if (strcmp(format, "postfix") == 0) {
    postfix(binary);
  }
  else if (strcmp(format, "infix") == 0) {
    infix(binary);
  }
  else if (strcmp(format, "prefix") == 0) {
    prefix(binary); 
    }
  else {
    cout << " \n" << "I don't really want to make another while look so its gonna exit now, you did not type the correct thing. \n";
  }
  
}

