#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "system.h"
#include "segment.h"
#include "../lib/include/useful.h"




/*
	<B, L>
	<12, 7>

physical addr:	12 13 14 15 16 17 18
offset:       	0  1  2  3  4  5  6

The above offsets are all valid as long as offset < L
	
*/
class memory
{
	private:

	//contains filled and unfilled memory segments
	list<Segment> mem_;

	unsigned int size_;
	unsigned int available_;
	unsigned int used_;


	public:
	memory();
	memory(unsigned int size);
	memory(list<Segment> m);

	//void destroy();
	bool allocate(PCB* p,  unsigned int limit);
	//void insert(list<Segment>::iterator hole, unsigned int limit)
	//uses first fit
	//fills process p's segTable as well
	//vertical view of memory: lower address on top, higher address on bottom
	void moveSegmentsUp();
	void mergeHoles();
	void free(PCB& p);
	void updateAccount();
	void printAccount();
	void setSize(unsigned int s);

	list<Segment>::iterator getFirstHole(list<Segment>& segList);

	unsigned int size();
	unsigned int available();
	unsigned int used();

	//friend class mySystem;
	//friend class scheduler;

	friend ostream& operator<<(ostream& out_stream, const memory& m);
};


#include "../src/memory.cpp"


#endif
