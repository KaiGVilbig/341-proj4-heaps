#include "TypedHeap.h"

void TypedHeap::insertToHeaps(vector<string> vec)
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (isdigit(vec[i][0]))
		{
			intHeap.insert(stoi(vec[i]));
		}
		else
		{
			stringHeap.insert(vec[i]);
		}
	}
	
}

// Merge the integer and string heaps; save in totalHeap.
void TypedHeap::combineHeaps()
{
	totalHeap.skewHeapMerge(intHeap);
	totalHeap.skewHeapMerge(stringHeap);
}

// Print all three heaps (integer, string, total).
void TypedHeap::printHeaps() const
{
	cout << "IntHeap Holds:";
	if (!intHeap.empty())
	{
		intHeap.dump();
	}

	cout << "\nStringHeap Holds:";
	if (!stringHeap.empty())
	{
		stringHeap.dump();
	}

	cout << "\nTotalHeap Holds:";
	if (!totalHeap.empty())
	{
		totalHeap.dump();
	}
	cout << endl;
}

// Change the priority function.
void TypedHeap::changePriority(pri_fn pri)
{
	intHeap.setPriFn(pri);
	stringHeap.setPriFn(pri);
	totalHeap.setPriFn(pri);
}