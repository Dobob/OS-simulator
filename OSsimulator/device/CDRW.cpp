#include "CDRW.h"

CDRW::CDRW(unsigned int id): id_{id}
{



}
void CDRW::destroy()
{
	while(!CDRW_q.empty())	
	{
		delete CDRW_q.front();
		CDRW_q.front() = nullptr;
		CDRW_q.pop();
	}

}
void CDRW::push(PCB* p)
{
	
	CDRW_q.push(p);

	cout << "Process " << p->getID() << " queued in CDRW " << id_ << endl;

}

PCB* CDRW::intrp()
{

	if(!CDRW_q.empty())
	{
		cout << "Process " << CDRW_q.front()->getID() << " dequeued from CDRW " << id_ <<  '.' << endl;

		PCB* PCB_ptr = CDRW_q.front();

		CDRW_q.pop();

		return PCB_ptr;
	}

	else 
	{
		
		string error = "ERROR: Empty CDRW " + uitos(id_) + " queue.";

		return nullptr;

	}
	

}


unsigned int CDRW::qSize()
{
	return CDRW_q.size();


}
bool CDRW::empty()
{

	return CDRW_q.empty();

}


void CDRW::print()
{

	cout << "CDRW " << id_;
}


vector<PCB*> CDRW::queue_vector()
{

	vector<PCB*> ret_vec;

	queue<PCB*> temp_q = CDRW_q;

	while(!temp_q.empty())
	{
		PCB* p = temp_q.front();
		//cout << "PID: " << id << endl;
		ret_vec.push_back(p);

		temp_q.pop();
	}
		


	return ret_vec;


}
