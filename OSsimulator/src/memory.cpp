#include "../include/memory.h"

memory::memory()
{
	Segment hole(0, 0, 0);
	mem_.push_back(hole);

	available_ = 0;
	used_ = 0;
}

memory::memory(unsigned int size)
{
	size_ = size;
	available_ = size;
	used_ = 0;

	Segment hole(0, 0, size_);
	mem_.push_back(hole);

}
memory::memory(list<Segment> l)
{
	if(l.empty())
	{
		Segment hole(0, size_);
		l.push_back(hole);

	}

	mem_ = l;
	unsigned int sizeCounter =0;

	for(auto s: l)
	{
		sizeCounter += s.limit();

	}

	size_ = sizeCounter;

	updateAccount();
	
}

unsigned int memory::size()
{

	return size_;
}
unsigned int memory::available()
{

	return available_;
}
unsigned int memory::used()
{

	return used_;
}


bool compareSegments(Segment a, Segment b)
{

	return a.base() < b.base();

}

list<Segment>::iterator memory::getFirstHole(list<Segment>& mem_)
{
	list<Segment>::iterator itr = mem_.begin();

	for(; itr != mem_.end() && !itr->isHole(); ++itr)
	{
		//you want the iterator to the first hole
	}

	return itr;

}
void memory::setSize(unsigned int size)
{
	size_ = size;
	available_ = size;
	used_ = 0;

	Segment hole(0, 0, size_);
	mem_.push_back(hole);
	updateAccount();

}
void memory::mergeHoles()
{
/*
	cout << "Before merging all holes: " << endl;
	for(auto i: mem_)
	{
		cout << i << " PID: " << i.pid() << endl;
	}
	cout << endl;

*/
	list<Segment>::iterator curItr = mem_.begin();
	list<Segment>::iterator nextItr = mem_.begin();
	//cout << "Before merging holes: \n" << endl;
	//cout << *this;

	//This for-loops merges all fragmented holes
	for(; curItr != mem_.end(); ++curItr)
	{

		if(curItr->isHole())
		{
			//cout << "Hole: " << *curItr << endl;
			nextItr = curItr;
			++nextItr;
			while(nextItr != mem_.end() && nextItr->isHole())
			{
				
				//cout << "Next segment is hole: " << *nextItr << endl;
				//cout << "Merging " << *curItr << " with " << *nextItr << endl;
				(*curItr) = (*curItr).merge(*nextItr);
				//cout << "RESULT: " << *curItr << endl;	
				nextItr = mem_.erase(nextItr);
			
			}

		}

		//if it is not a hole, we skip with ++curItr

	}

}
void memory::moveSegmentsUp()
{
	list<Segment>::iterator firstHole;
	list<Segment>::iterator tempItr;
	list<Segment>::iterator curItr = mem_.begin();
	list<Segment>::iterator nextItr = mem_.begin();

	mergeHoles();


	curItr = mem_.begin();
	firstHole = getFirstHole(mem_);

	//TODO: 0. This loop is BUGGED!
	//This for-loop fills up holes by moving segments "upward" or toward lower memory
	for(; curItr != mem_.end(); ++curItr)
	{

		//if it is not hole, move it up to the base of first hole
		if(!curItr->isHole())
		{

			//sets segment's base to the hole's base
			curItr->setBase(firstHole->base());	


			//limit doesn't change, but firstHole must be updated
			firstHole->setBase(curItr->base() + curItr->limit());

			nextItr = curItr;
			++nextItr;
			
			if(nextItr->isHole() && nextItr != mem_.end())
			{

				//merge first hole and current hole

				(*firstHole) = firstHole->merge(*nextItr);
				mem_.erase(nextItr);
			}
	
		}

	}

	mem_.sort(compareSegments);


}

void memory::free(PCB& p)
{
	//1.For each segment in p, make them a hole
	//You can find the segments using the PID
	//might be more efficient if segTable is a table of pointers to Segments.
	//But then you have to implement the destructor for the segTable.

	vector<Segment*> segTable = p.getSegTable();

	for(auto segPtr: segTable)
	{

		segPtr->free();
	}

	//mergeHoles();

	//moveSegmentsUp();

	updateAccount();

	//2. Call merge holes on memory.
	
	

}
bool memory::allocate(PCB* p, unsigned int limit)
{

	//1. put in memory

	list<Segment>::iterator memItr = mem_.begin();
	list<Segment>::iterator insertedSegItr;

	for(; memItr != mem_.end(); ++memItr)
	{

		if(memItr->isHole())
		{
			//check size of hole(base plus limit)

			//actual used memory = base to sizeOfHole-1
			unsigned int sizeOfHole = memItr->limit();
			
			if(sizeOfHole >= limit)
			{
				unsigned int holeBase = memItr->base();
				Segment segToInsert(p->getID(), holeBase, limit);
			
				segToInsert.fill();

				insertedSegItr = mem_.insert(memItr, segToInsert);
				//cout << "After inserting process: " << endl;


				//insertedSegItr = memItr;
				//--insertedSegItr;

				Segment* segPtr = &(*insertedSegItr);

				p->insertSegTable(segPtr);

				unsigned int newHoleLimit = memItr->limit() - limit;
				//cout << "@@@@@@@@@@@@New Hole Limit: " << newHoleLimit << endl;
				memItr->setLimit(newHoleLimit);
				//reduced hole size has base = segbase + seglimit

				//new hole limit is old limit minus process limit
				

				if(newHoleLimit == 0)
				{
					//cout << "ERASING HOLE 1" << endl;
					mem_.erase(memItr);

				}
		
				else
				{
					memItr->setBase(holeBase+limit);

				}


				return true;
			}

		}


	}

	//If hasn't returned yet, then that means no space is found.
	//So put in job pool

	return false;

}


void memory::updateAccount()
{
	list<Segment>::iterator itr = mem_.begin();

	available_=0;

	for(; itr!= mem_.end(); ++itr)
	{

		if(itr->isHole())
		{
			
			available_ = available_ + itr->limit();

		}
		
	}

	used_ = size_-available_;

}

void memory::printAccount()
{
	cout << "size: " << size_ << endl;
	cout << "available: " << available_ << endl;
	cout << "used: " << used_ << endl;


}
ostream& operator<<(ostream& out_stream, const memory& m)
{

	cout << left << setw(5) << "PID" << setw(8) << "Hole?" << setw(10) << "seg(B, L)" << endl;

	
	for(auto itr: m.mem_)
	{
//cout << "pid: " << itr.pid() << " hole " << itr.isHole() << endl;
	 out_stream << left << setw(5) << itr.pid() << setw(8) << itr.isHole() << '(' << itr.base() << ", " <<  itr.limit()  << setw(10) << ')' << endl;

	}
/*
	cout << left << setw(5) << "PID" << setw(10) << "seg(B, L)" << setw(5) << "Hole?" << endl;
	for(auto itr: m.mem_)
	{

	 out_stream << left << setw(5) << itr.pid() << setw(20) << '(' << itr.base() << ", " <<  itr.limit()  << ')' << setw(8) << itr.isHole() << endl;

	}
*/

	return out_stream;

}



























