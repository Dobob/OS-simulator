#include "printer.h"

printer::printer()
{



}
void printer::destroy()
{
	while(!print_q.empty())	
	{
		delete print_q.front();
		print_q.front() = nullptr;
		print_q.pop();
	}

}
printer::printer(unsigned int id): id_{id}
{



}
void printer::push(PCB* p)
{
	
	print_q.push(p);

	cout << "Process " << p->getID() << " queued in printer " << id_ << '.' << endl;

}

PCB* printer::intrp()
{


	if(!print_q.empty())
	{
		cout << "Process " << print_q.front()->getID() << " dequeued from printer " << id_ << endl;

		PCB * PCB_ptr = print_q.front();

		print_q.pop();

		return PCB_ptr;
	}

	else 
	{
		
		string error = "ERROR: Empty printer " + uitos(id_) + " queue.";

		return nullptr;

	}

	

}




unsigned int printer::qSize()
{
	return print_q.size();


}
bool printer::empty()
{

	return print_q.empty();

}


void printer::print()
{

	cout << "printer " << id_;
}


vector<PCB*> printer::queue_vector()
{
	vector<PCB*> ret_vec;

	queue<PCB*> temp_q = print_q;

	while(!temp_q.empty())
	{
		PCB* p = temp_q.front();
		//cout << "PID: " << id << endl;
		ret_vec.push_back(p);
/*
		cout << "INSIDE queue_vector() ID: " << p.getID() << endl;
		cout << "INSIDE queue_vector() action: " << p.getAct() << endl;
		cout << "INSIDE queue_vector() file: " << p.getFile() << endl;
		cout << "INSIDE queue_vector() memloca: " << p.getMem() << endl;
*/
		temp_q.pop();
	}
		


	return ret_vec;


}










