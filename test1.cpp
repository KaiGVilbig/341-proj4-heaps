// CMSC 341 - Fall 2019 - Project 4
// Basic test of TypedHeap class

#include <iostream>
#include "TypedHeap.h"

// Prototypes for two priority functions
int PriorityCalc1(Node *);
int PriorityCalc2(Node *);

int main() {

  TypedHeap t1(PriorityCalc1);

  vector<string> vec;
  vec.push_back("1234");
  vec.push_back("Hello");
  vec.push_back("9734");
  vec.push_back("3412");
  vec.push_back("Students");

  t1.insertToHeaps(vec);
  t1.printHeaps();

  cout << "\nMerging...\n";

  t1.combineHeaps();
  t1.printHeaps();

  cout << "\nChanging Priority Fn...\n";
  
  t1.changePriority(PriorityCalc2);
  t1.printHeaps();

  return 0;
}

int PriorityCalc1(Node *node){
  int sum = 0;
  if(node->tagged_union == ISINT){
    return node->data_int;
  }
  else{
    int size = node->data_string.size();
    for(int i = 0; i < size; i++){
      sum = sum + node->data_string[i];
    }
  }
  return sum;
}

int PriorityCalc2(Node *node){
  int sum = 0;
  if(node->tagged_union == ISINT){
    return (-1 * (node->data_int));
  }
  else{
    int size = node->data_string.size();
    for(int i = 0; i < size; i++){
      sum = sum + node->data_string[i];
    }
  }
  return (-1 *sum);
}
