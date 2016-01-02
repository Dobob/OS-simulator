#include <iostream>
#include <list>
#include <vector>

using namespace std;

class numBox
{
	private:
	int num;

	public:

	numBox() : num{-1}{}

	void setNum(int n)
	{
		num = n;
		
	}

	int getNum() const
	{
		return num;

	}

	
	friend ostream& operator<<(ostream& out_stream, const numBox& outBox)
	{
		out_stream << outBox.getNum();

		return out_stream;

	}

};

int main(){

	list<int> n = list<int>(4); //creates a list with size 4

	list<int>::iterator it = n.begin();

	for(int i =0; it!= n.end(); ++it, i++)
	{
		(*it) = i; 
		cout << *it << ' ';

	}
	cout << endl;
	n.insert(n.end(), 10);
	it = n.begin();
	for(int i =0; it!= n.end(); ++it)
	{
		cout << *it << ' ';
	}

	cout << endl;
	int a = 7;
	it = n.begin();

	for(int i =0; it!= n.end(); ++it)
	{
		if((*it) >= a)
		{	
			cout << "*it = " << *it << endl;
			n.insert(it, a);
			break;
		}
	}




	cout << endl;
	it = n.begin();
	for(int i =0; it!= n.end(); ++it)
	{
		cout << *it << ' ';
	}

	cout << endl;
	it = n.begin();
	for(int i =0; it!= n.end(); ++it)
	{
		if(*it == a)
			n.erase(it);
	}
	cout << endl;
	it = n.begin();
	for(int i =0; it!= n.end(); ++it)
	{
		cout << *it << ' ';
	}



	list<int> n1; 

	n1.push_front(2);


	



	return 0;









}














