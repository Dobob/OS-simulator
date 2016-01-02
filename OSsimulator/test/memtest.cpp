#include <iostream>
#include "../include/system.h"
#include "../include/memory.h"
#include <vector>

using namespace std;

int main()
{	

	memory mem(10);
	PCB p1;
	p1.setPID();
	PCB p2;
	p2.setPID();
	PCB p3;
	p3.setPID();
	mem.allocate(p1, 1);
	mem.allocate(p2, 2);
	mem.allocate(p3, 3);

	cout << mem << endl;

	p1.printSegTable();
	p2.printSegTable();
	p3.printSegTable();
	return 0;

}







/*
Segment merge( Segment prevSeg, Segment curSeg)
{
	Segment retSeg;

	//they cannot have the same base anyway
	if(prevSeg.base() < curSeg.base())
		retSeg.setBase(prevSeg.base());

	else if(prevSeg.base() > curSeg.base())
		retSeg.setBase(curSeg.base());

	if(prevSeg.limit() < curSeg.limit())
		retSeg.setLimit(curSeg.limit());	

	else if(prevSeg.limit() > curSeg.limit())
		retSeg.setLimit(prevSeg.limit());



	return retSeg;

}

bool compareSegmentsTest(Segment a, Segment b)
{

	return a.base() < b.base();

}

list<Segment>::iterator getFirstHole(list<Segment>& segList)
{
	list<Segment>::iterator itr = segList.begin();

	for(; itr != segList.end() && !itr->isHole(); ++itr)
	{
		//you want the iterator to the first hole
	}

	return itr;

}

void mergeHoles(list<Segment>& segList)
{
	cout << "Before merging all holes: " << endl;
	for(auto i: segList)
	{
		cout << i << " PID: " << i.pid() << endl;
	}
	cout << endl;

	bool prevIsHole = false;

	list<Segment>::iterator curItr = segList.begin();
	list<Segment>::iterator nextItr = segList.begin();


	//This for-loops merges all fragmented holes
	for(; curItr != segList.end(); ++curItr)
	{

		if(curItr->isHole())
		{
			nextItr = curItr;
			++nextItr;
			while(nextItr != segList.end() && nextItr->isHole())
			{
				
				(*curItr) = (*curItr).merge(*nextItr);
				nextItr = segList.erase(nextItr);
			
			}

		}

		//if it is not a hole, we skip with ++curItr

	}

}
void mergeHolesUp(list<Segment>& segList)
{
	

	list<Segment>::iterator firstHole;
	list<Segment>::iterator tempItr;
	list<Segment>::iterator curItr = segList.begin();
	list<Segment>::iterator nextItr;

	mergeHoles(segList);

	cout << "After merging all holes: " << endl;
	for(auto i: segList)
	{
		cout << i << " PID: " << i.pid() << endl;
	}

	cout << endl;
	curItr = segList.begin();
	firstHole = getFirstHole(segList);

	//TODO: this loop is BUGGED!
	//This for-loop fills up holes by moving segments "upward" or toward lower memory
	for(; curItr != segList.end(); ++curItr)
	{

		//if it is not hole, move it up to the base of first hole
		if(!curItr->isHole())
		{
			//cout << "current hole: " << *firstHole << endl;
			//cout << "current segment: " << *curItr << endl;
			//sets segment's base to the hole's base
			curItr->setBase(firstHole->base());	
			//cout << "Segment new: " << *curItr << endl;


			//limit doesn't change, but firstHole must be updated
			firstHole->setBase(curItr->base() + curItr->limit());
			//cout << "Hole new: " << *firstHole << endl;

			nextItr = curItr;
			++nextItr;
			
			if(nextItr->isHole() && nextItr != segList.end())
			{
				//cout << "nextItr contains: " << *nextItr << endl;
				//merge first hole and current hole

				(*firstHole) = firstHole->merge(*nextItr);
				//cout << "after merging holes: " << *firstHole << endl;
				segList.erase(nextItr);
			}
			//cout << endl;
	
		}

	}

	cout << "After moving segments up: " << endl;
	for(auto i: segList)
	{
		cout << i << " PID: " << i.pid() << endl;
	}
	cout << endl;


	segList.sort(compareSegmentsTest);

	cout << "After sorting: " << endl;
	for(auto i: segList)
	{
		cout << i << " PID: " << i.pid() << endl;
	}

}

void freeTest(PCB& p, list<Segment>& segList)
{
	list<Segment>::iterator itr = segList.begin();

	unsigned int pid = p.getID();
	for(; itr != segList.end(); ++itr)
	{

		if(itr->pid() == pid)
		{
			itr->free();

		}


	}

	mergeHolesUp(segList);

}



void mergeHolesTest()
{
	list<Segment> s;


	Segment a(0, 0, 5);
	Segment b(1, 5, 10);
	b.fill();
	Segment c(0, 15, 17);
	//c.fill();
	Segment d(2, 32, 30);
	d.fill();
	Segment e(0, 62, 55);
	Segment f(0, 117, 70);

	s.push_back(a);
	s.push_back(b);
	s.push_back(c);
	s.push_back(d);
	s.push_back(e);
	s.push_back(f);

	mergeHolesUp(s);
	

}

bool allocateTest(PCB& p, unsigned int limit, list<Segment> segTable)
{

	list<Segment>::iterator memItr = segTable.begin();
	cout << "BEFORE: " << endl;
	for(auto i: segTable)
	{

		cout << i << " hole: " << i.isHole() << endl;

	}
	for(; memItr != segTable.end(); ++memItr)
	{

		if(memItr->isHole())
		{
			//check size of hole(base plus limit)

			//actual used memory = base to sizeOfHole-1
			unsigned int sizeOfHole = memItr->limit();

			if(sizeOfHole >= limit)
			{
					unsigned int holeBase = memItr->base();
				Segment segToInsert(holeBase, limit);
				segToInsert.fill();
				cout << "Inserting segment: " << segToInsert << endl;
				cout << "into hole: " << *memItr << endl;

				Segment * segPtr = &segToInsert;
				segTable.insert(memItr, segToInsert);
				p.insertSegTable(segPtr);

				//reduced hole size has base = segbase + seglimit

				if(memItr->limit() == limit)
				{
					cout << "memItr->limit() == limit" << endl;
					segTable.erase(memItr);

				}
		
				else
				{
					memItr->setBase(holeBase+limit);

					//if hole's base equals its limit, it is deleted, so remove from memory list
					//otherwise the hole still exists
					if(memItr->base() == memItr->limit())
					{
						segTable.erase(memItr);

					}

				}
			
				return true;

			}
		}
	}

	cout << "AFTER: " << endl;
	for(auto i: segTable)
	{

		cout << i << " hole: " << i.isHole() << endl;

	}

	return false;

}
void test(PCB& p)
{
	Segment segToInsert(0, 1);
	Segment* segPtr = &segToInsert;
	p.insertSegTable(segPtr);

}

*/






