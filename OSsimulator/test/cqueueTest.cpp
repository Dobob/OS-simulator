#include <iostream>
#include "../include/system.h"
#include "../include/PCB.h"
#include "../lib/include/cqueue.h"

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

	cqueue<PCB> p = cqueue<PCB>(3);

	cout << p << endl;

	cout << p.getNumItems();

	PCB a, b, c;

	p.push(a);
	p.push(b);
	p.push(c);
	cout << endl;
	cout << p << endl;

	cout << p.getNumItems();


	cqueue<PCB> p1 = cqueue<PCB>(5);
	PCB d, e, f, g, h;

	p1.push(d);
	p1.push(e);
	p1.push(f);
	p1.push(g);
	p1.push(h);


	cout << endl;
	cout << p1 << endl;
	cout << p1.getNumItems();
	cout << endl;
	p = p1;

	cout << p << endl;
	cout << p1 << endl;

	cout << p.getNumItems() << endl;
	cout << p1.getNumItems() << endl;
	cout << p.empty() << endl;
	cout << "@pop1: " << endl;
	p.pop();
	cout << "@pop2: " << endl;
	p.pop();
	cout << "@pop3: " << endl;
	p.pop();
	cout << "@pop4: " << endl;
	p.pop();
	cout << "@pop5: " << endl;
	p.pop();
	cout << "@pop6: " << endl;
	p.pop();

	return 0;
}



