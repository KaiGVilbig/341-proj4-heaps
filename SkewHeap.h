// CMSC 341 - Fall 2019 - Project 4

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Grader;

// ENUM of valid data types
enum type_t {ISSTRING, ISINT};

struct Node{
  enum type_t tagged_union;   // Type of data in node
  union {
    string data_string;       // Store string or int; but
    int data_int;             // not both
  };
  Node *right;                // Right child
  Node *left;                 // Left child

  // Constructor for int data
  Node(int data){  
    data_int = data;
    right = nullptr;
    left = nullptr;
    tagged_union = ISINT;
  }

  // Constructor for string data
  Node(string data) : data_string(data) {
    right = nullptr;
    left = nullptr;
    tagged_union = ISSTRING;
  }

  // Need a destructor because the union includes string
  ~Node() {
    if ( tagged_union == ISSTRING ) {
      data_string.~string();
    }
  }
};

// Defines pri_fn as a function pointer
typedef int (*pri_fn)(Node *);

class SkewHeap {
public:

  friend Grader;

  // Constructor.  Must specify priority function.
  SkewHeap(pri_fn pri);

  // Destructor, copy constructor, assignment operator
  ~SkewHeap(); 
  SkewHeap(const SkewHeap& rhs);
  const SkewHeap& operator=(const SkewHeap& rhs);

  // Priority function get and set
  pri_fn getPriFn() const;
  void setPriFn (pri_fn pri);

  // Return true if the skew heap is empty
  bool empty() const;

  // Overloaded insertion operators.  One for string data, one for
  // integer data.
  void insert(string data);
  void insert(int data);

  // Access highest priority element in the skew heap.
  Node* front() const;

  // Remove the highest priority element from the skew heap.
  void removeTop();

  // Merge two heaps.  Merged heap in *this; sh is empty afterwards.
  void skewHeapMerge(SkewHeap& sh);

  // Print inorder traversal.
  void inorder() const;
  
  // Dump the contents of the heap in decreasing priority order.
  void dump() const;

private:
  Node *m_heap;          // Root pointer
  pri_fn priority;       // Current priority function

  //************************************
  //
  // PRIVATE HELPER FUNCTIONS GO HERE!
  //
  //************************************
  void swap(Node* root, Node* sh, Node* sh1)
  {
		Node* temp = sh;
		root->left = sh1;
		root->right = temp;
  }

  Node* merge(Node* sh, Node* sh1)
  {
	  if (sh == nullptr)
	  {
		  return sh1;
	  }
	  if (sh1 == nullptr)
	  {
		  return sh;
	  }

		if (priority(sh) < priority(sh1))
		{
			Node *temp = sh;
			sh = sh1;
			sh1 = temp;
			swap(sh, sh->left, sh->right);
		}
		else if (sh->left != nullptr && sh->right != nullptr)
		{
			swap(sh, sh->left, sh->right);
		}
		else if (sh->left != nullptr && sh->right == nullptr)
		{
			sh->right = sh->left;
			sh->left = nullptr;
		}
		else if (sh->right != nullptr && sh->left == nullptr)
		{
			sh->left = sh->right;
			sh->right = nullptr;
		}

		sh->left = merge(sh->left, sh1);

		return sh;
  }

  void inorderP(Node* sh) const
  {
	  if (empty() || sh == nullptr) return;

	  cout << "(";
	  inorderP(sh->left);

	  sh->tagged_union == ISINT ? cout << sh->data_int : cout << sh->data_string;

	  inorderP(sh->right);
	  cout << ")";

	  return;
  }

  Node* dumpP(Node* last, Node* sh, Node* sh1) const
  {
	  if (empty() || sh == nullptr) return sh1;

	  sh1 = dumpP(last, sh->left, sh1);

	  if (sh != last && priority(sh) < priority(last) && priority(sh) > priority(sh1))
	  {
		  sh1 = sh;
	  }

	  sh1 = dumpP(last, sh->right, sh1);

	  return sh1;
  }

  Node* getLowest(Node* sh, Node* sh1) const
  {
	  if (empty() || sh1 == nullptr) return sh;

	  sh = getLowest(sh, sh1->left);

	  if (sh != sh1 && priority(sh) > priority(sh1))
	  {
		  sh = sh1;
	  }

	  sh = getLowest(sh, sh1->right);

	  return sh;
  }

  Node* preorder(Node* sh)
  {
	  if (sh == nullptr) return sh;

	  Node* temp = nullptr;
	  sh->tagged_union == ISINT ? temp = new Node(sh->data_int) : temp = new Node(sh->data_string);

	  if (sh->left != nullptr)
	  {
		  temp->left = preorder(sh->left);
	  }
	  if (sh->right != nullptr)
	  {
		  temp->right = preorder(sh->right);
	  }

	  return temp;
  }

  Node* rebuild(Node* a)
  {
	  Node* fin = a;

	  Node* max = getMax(a, a);
	  Node* temp = nullptr;
	  max->tagged_union == ISINT ? temp = new Node(max->data_int) : temp = new Node(max->data_string);
	  removeN(max, m_heap);


	  temp->left = a;
	  a = temp;

	  if (max == fin)
	  {
		  removeN(fin, a);
	  }

	  while (max != fin)
	  {
		  a->left = rebuild(a->left);
		  return a;
	  }
	  return a;
  }

  Node* getMax(Node* sh, Node* sh1)
  {
	  if (empty() || sh1 == nullptr) return sh;

	  sh = getMax(sh, sh1->left);

	  if (sh != sh1 && priority(sh) < priority(sh1))
	  {
		  sh = sh1;
	  }

	  sh = getMax(sh, sh1->right);
	  return sh;
  }

  void removeN(Node* a, Node* curr)
  {

	  if (curr->left == a)
	  {
		  delete curr->left;
		  curr->left = nullptr;
		  return;
	  }
	  else if (curr->right == a)
	  {
		  delete curr->right;
		  curr->right = nullptr;
		  return;
	  }

	  if (curr->left != nullptr)
	  {
		  removeN(a, curr->left);
	  }
	  if (curr->right != nullptr)
	  {
		  removeN(a, curr->right);
	  }
  }

  void postorder(Node* a)
  {
	  if (empty()) return;

	  if (a->left != nullptr)
	  {
		  postorder(a->left);
	  }
	  if (a->right != nullptr)
	  {
		  postorder(a->right);
	  }

	  delete a;
	  a = nullptr;
  }
};

#endif
