#include "disk.h"

disk::disk(unsigned int id): id_{id}
{
	curr_cyl_ptr = clook.begin();

}
void disk::destroy()
{
	for(auto &p: clook)
	{
		delete p;
		p = nullptr;

	
	}
	clook.clear();
	curr_cyl_ptr = clook.begin();
}
void disk::push(PCB* p)
{
	if(clook.empty())
	{
		//cout << "Process " << p->getID() << " address: " << p << endl;
		clook.push_front(p);
		cout << "Process " << p->getID() << " queued in disk " << id_ << endl;
		curr_cyl_ptr = clook.begin();

		return;
	}

	else 
		for(list<PCB*>::iterator it = clook.begin(); it !=clook.end();)
		{

			if((*it)->getCylinder() > p->getCylinder())
			{
				clook.insert(it, p); //insert() inserts before current iterator.
				cout << "Process " << p->getID() << " queued in disk " << id_ << endl;

				return;

			}

			++it;

			if(it == clook.end())
			{
				clook.insert(it, p);

				return;
			}

		}

	
}

PCB* disk::intrp()
{



	if(!clook.empty())
	{

		PCB* pcb_ptr = *curr_cyl_ptr;

		cout << "Process " << (*curr_cyl_ptr)->getID()  << " dequeued from disk " << id_ <<  '.' << endl;
	
		curr_cyl_ptr = clook.erase(curr_cyl_ptr);

		if(curr_cyl_ptr == clook.end())
		{
			curr_cyl_ptr = clook.begin();
		
		}
		return pcb_ptr;
	}

	else 
	{
		
		string error = "ERROR: Empty disk " + uitos(id_) + " queue.";

		return nullptr;

	}

	

}

unsigned int disk::diskHeadLocation()
{
	if(clook.empty())
		return 0;

	return (*curr_cyl_ptr)->getCylinder();

}

unsigned int disk::qSize()
{
	return clook.size();

}
bool disk::empty()
{

	return clook.empty();

}


void disk::print()
{

	cout << "disk " << id_;
}
void disk::setCylinders(unsigned int c)
{
	cylinders = c;

}

list<PCB*>& disk::queue_list()
{
	return clook;


}
list<PCB*>::iterator* disk::getHeadPosition()
{

	return &curr_cyl_ptr;

}






