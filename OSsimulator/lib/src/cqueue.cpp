#include "../include/cqueue.h"

template<typename type>
cqueue<type>::cqueue(): front_{0}, back_{0}
{


}
template<typename type>
cqueue<type>::cqueue(size_t init_size): size_{init_size}, front_{0}, back_{0}
{

	array = new type [size_];


}

template<typename type>
void cqueue<type>::resize()
{

	size_t newSize = size_*2;

	type* newArray = new type[newSize];

	copy(array, newArray, newSize, numItems);
	
	delete[] array;

	array = newArray;
	size_ = newSize;

}





template<typename type>
bool cqueue<type>::push(const type& item)
{

	if( (back_+1)%size_ == front_ )
	{
		resize();

	}

	//cout << "(copy)back: " << back << " pushing " << item << endl;
	array[back_] = item;
	back_ = (back_+1)%size_;
	


	numItems++;
/*
	cout << "\nPUSHED" << endl;
	cout << "front_ : " << front_ << endl;
	cout << "array[front_] : " << array[front_] << endl;
	cout << "back_ : " << back_ << endl;
	cout << "array[back_] : " << array[back_] << endl;
	cout << "numItems : " << numItems << endl;
*/
	return true;

}

template<typename type>
bool cqueue<type>::push(type && item)
{

	
	if( (back_+1)%size_==front_)
	{

		resize();

	}
	//cout << "(move)back: " << back << " pushing " << item << endl;


	array[back_] = std::move(item);

	back_ = (back_+1)%size_;

	numItems++;



	return true;

}

template<typename type>
bool cqueue<type>::pop()
{

	//cout << "front: " << front << endl;
	if(front_ == back_)
	{
		return false;
	}


	front_ = (front_+1)%size_;
	
	numItems--;

/*
	cout << "\nPOPPED" << endl;
	cout << "front_ : " << front_ << endl;
	cout << "array[front_] : " << array[front_] << endl;
	cout << "back_ : " << back_ << endl;
	cout << "array[back_] : " << array[back_] << endl;
	cout << "numItems : " << numItems << endl;
*/
	return true;

}
template<typename type>
bool cqueue<type>::empty()
{

	return (front_ == back_);

}
template<typename type>
type& cqueue<type>::front()
{

	return array[front_];


}


template<typename type>
const type& cqueue<type>::operator[](int index) const
{

	return array[index];


}


template<typename type>
size_t cqueue<type>::size() const
{

	return size_;

}

template<typename type>
size_t cqueue<type>::getNumItems() const
{
	return numItems;


}


template<typename type>
cqueue<type>& cqueue<type>::operator=(const cqueue<type>& rhs)
{
	delete [] array;
	//cout << "numItems : " << numItems << endl;
	array = new type(rhs.size_);
	size_ = rhs.size_;
	front_ = rhs.front_;
	back_ = rhs.back_;
	numItems = rhs.numItems;

	copy(rhs.array, array, rhs.size_ ,rhs.numItems);

	return *this;

}
/*
template<typename type>
cqueue<type>& cqueue<type>::operator=(cqueue<type>&& rhs)
{
	delete [] array;
	array = new type(std::move(rhs.size_));
	size_ = std::move(rhs.size_);
	front_ = std::move(rhs.front_);
	back_ = std::move(rhs.back_);
	numItems = std::move(rhs.numItems);
	empty_ = std::move(rhs.empty_);

	copy(rhs.array, array, rhs.numItems);

	delete [] rhs.array;

	return *this;

}
*/

template<typename friendItemType>
ostream& operator<<(ostream& out_stream, const cqueue<friendItemType>& cq)
{
	//cout << "numItems: " << cq.getNumItems() << endl;
	for(size_t i = cq.front_; i < cq.back_; i++)
		out_stream << cq[i] << ' ';

	return out_stream;
}






template<typename friendItemType>
void copy(friendItemType arrayFrom[], friendItemType arrayTo[], size_t arrayToSize, size_t numItems)
{

	//no way to resize a given array since it is a primitive data type.
	if(numItems > arrayToSize)
		return;

	for(int i=0; i<numItems; i++)
	{
		//cout << "arrayTo[i] " << arrayTo[i]; 
		arrayTo[i] = arrayFrom[i];
		//cout << " = " << "arrayFrom[i] " << arrayFrom[i] << endl;
	}
	

}








