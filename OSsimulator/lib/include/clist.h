#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <iostream>
#include <list>
#include "useful.h"

using namespace std;


/*
	This implementation of circular array with size limited by size_t, 
	as a result a bool variable is needed to maximize index usage.


*/

template<typename type>
class cvector
{
	private:

	vector<type> vec(100);
	size_t front_, back_;
	size_t numItems=0;
	//bool empty_;



	public:
	cvector();
	cvector(size_t init_size);

	//push methods return false on the insertion that made the array full.
	//the array is full when (back_+1)%size_ == front_
	bool push(const type& t);
	bool push(type && t);

	//array is empty when front_ == (back+1)%size
	bool pop();
	bool empty();



	void resize();

	type& front();

	size_t size() const;
	size_t getNumItems() const;


	const type & operator[](int index) const;

	cqueue<type>& operator=(const cqueue<type>& rhs); 
	cqueue<type>& operator=(cqueue<type>&& rhs); 

	template<class friendItemType>
	friend ostream& operator<<(ostream& out_stream, const cvector<friendItemType>& cv);

	//precondition: cqueueTo must be large enough to hold numItems of items.
	//template<class friendItemType>
	//friend void copy(cqueue cqueueFrom, friendItemType cqueueTo[], size_t arrayToSize, size_t numItems );

};

#include "../src/clist.cpp"

#endif
