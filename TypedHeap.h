// CMSC 341 - Fall 2019 - Project 4

#ifndef TYPEDHEAP_H
#define TYPEDHEAP_H

#include "SkewHeap.h"
#include <vector>

class TypedHeap {

public:
  // Constuctor (in-line). Must provide priority function.
  explicit TypedHeap(pri_fn pri) : intHeap(pri), stringHeap(pri), totalHeap(pri) {};

  // Provide a vector of strings.  For each string, determine whether
  // it represents an integer; if so, insert it into the integer skew
  // heap.  Otherwise, insert it into the string skew heap.
  void insertToHeaps(vector<string> vec);

  // Merge the integer and string heaps; save in totalHeap.
  void combineHeaps();

  // Print all three heaps (integer, string, total).
  void printHeaps() const;

  // Change the priority function.
  void changePriority(pri_fn pri);
  
private:
  SkewHeap intHeap, stringHeap, totalHeap;
};


#endif
