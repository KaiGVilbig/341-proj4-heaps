// CMSC 341 - Fall 2019 - Project 4

#include "SkewHeap.h"
using namespace std;

	// Constructor.  Must specify priority function.
SkewHeap::SkewHeap(pri_fn pri)
{
	m_heap = nullptr;
	priority = pri;
}

	// Destructor, copy constructor, assignment operator
SkewHeap::~SkewHeap()
{
	postorder(m_heap);
	m_heap = nullptr;
}
SkewHeap::SkewHeap(const SkewHeap& rhs)
{
	m_heap = nullptr;
	priority = rhs.priority;
	m_heap = preorder(rhs.m_heap);
}

const SkewHeap& SkewHeap::operator=(const SkewHeap& rhs)
{
	m_heap = nullptr;
	priority = rhs.priority;
	m_heap = preorder(rhs.m_heap);
	return *this;
}

	// Priority function get and set
pri_fn SkewHeap::getPriFn() const
{
	return priority;
}
void SkewHeap::setPriFn(pri_fn pri)
{
	priority = pri;
	if (m_heap != nullptr)
	{
		m_heap = rebuild(m_heap);
	}
}

	// Return true if the skew heap is empty
bool SkewHeap::empty() const
{
	return m_heap == nullptr ? true : false;
}

	// Overloaded insertion operators.  One for string data, one for
	// integer data.
void SkewHeap::insert(string data)
{
	if (empty())
	{
		m_heap = new Node(data);
	}
	else
	{
		SkewHeap tempHeap(priority);
		tempHeap.m_heap = new Node(data);
		skewHeapMerge(tempHeap);
		tempHeap = nullptr;
	}
}
void SkewHeap::insert(int data)
{
	if (empty())
	{
		m_heap = new Node(data);
	}
	else
	{
		SkewHeap tempHeap(priority);
		tempHeap.m_heap = new Node(data);
		skewHeapMerge(tempHeap);
		tempHeap = nullptr;
	}
}

	// Access highest priority element in the skew heap.
Node* SkewHeap::front() const
{
	return m_heap;
}

	// Remove the highest priority element from the skew heap.
void SkewHeap::removeTop()
{
	if (empty()) return;
	
	Node* tempN = m_heap;
	m_heap = m_heap->left;

	SkewHeap temp(priority);
	temp.m_heap = tempN->right;
	skewHeapMerge(temp);
	delete tempN;
	tempN = nullptr;
	temp.m_heap = nullptr;
}

	// Merge two heaps.  Merged heap in *this; sh is empty afterwards.
void SkewHeap::skewHeapMerge(SkewHeap& sh)
{
	m_heap = merge(m_heap, sh.m_heap);
	sh = nullptr;
}

	// Print inorder traversal.
void SkewHeap::inorder() const
{
	inorderP(m_heap);
	return;
}

	// Dump the contents of the heap in decreasing priority order.
void SkewHeap::dump() const
{

	Node* printN = m_heap;
	Node* lowest = getLowest(printN, m_heap);

	int last = priority(m_heap);
	cout << "\nData is: ";
	cout.width(25); m_heap->tagged_union == ISINT ? 
		cout << left << m_heap->data_int : cout << left << m_heap->data_string;
	cout << "Priority is:\t" << last;

	while (priority(printN) != priority(lowest))
	{
		printN = dumpP(printN, m_heap, lowest);
		cout << "\nData is: ";
		cout.width(25); printN->tagged_union == ISINT ?
			cout << left << printN->data_int : cout << left << printN->data_string;
		cout << "Priority is:\t" << priority(printN);
	}
	cout << endl;
}