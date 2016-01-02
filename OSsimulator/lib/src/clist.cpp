#include "../include/clist.h"

template<typename type>
cvector<type>::cvector(): front_{0}, back_{0}
{


}
template<typename type>
cvector<type>::cvector(size_t init_size): size_{init_size}, front_{0}, back_{0}
{

	array = new type [size_];


}

template<typename type>
void cvector<type>::resize()
{

	size_t newSize = size_*2;

	type* newArray = new type[newSize];

	copy(array, newArray, newSize, numItems);
	
	delete[] array;

	array = newArray;
	size_ = newSize;

}


template<typename type>
bool cvector<type>::push(const type& item)
{

	if( (back_+1)%size_ == front_ )
	{
		vec.resize(2*vec.size());

	}

	//cout << "(copy)back: " << back << " pushing " << item << endl;
	vec[back_] = item;
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
bool cvector<type>::push(type && item)
{

	
	if( (back_+1)%size_==front_)
	{

		resize();

	}
	//cout << "(move)back: " << back << " pushing " << item << endl;


	vec[back_] = std::move(item);

	back_ = (back_+1)%size_;

	numItems++;



	return true;

}

template<typename type>
bool cvector<type>::pop()
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
bool cvector<type>::empty()
{

	return (front_ == back_);

}
template<typename type>
type& cvector<type>::front()
{

	return array[front_];


}


template<typename type>
const type& cvector<type>::operator[](int index) const
{

	return vec[index];


}


template<typename type>
size_t cvector<type>::size() const
{

	return size_;

}

template<typename type>
size_t cvector<type>::getNumItems() const
{
	return numItems;


}


template<typename friendItemType>
ostream& operator<<(ostream& out_stream, const cvector<friendItemType>& cv)
{
	//cout << "numItems: " << cq.getNumItems() << endl;
	for(size_t i = cv.front_; i < cq.back_; i++)
		out_stream << cv[i] << ' ';

	return out_stream;
}











