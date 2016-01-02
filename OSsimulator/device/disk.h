#ifndef DISK_H
#define DISK_H


#include <iostream>
#include <string>
#include <list>
#include "../include/pcb.h"
#include "../lib/include/useful.h"
using namespace std;



class disk
{

	private:
	unsigned int id_=0;
	unsigned int cylinders=0;

	list<PCB*> clook;

	list<PCB*>::iterator curr_cyl_ptr;


	public:
	
	disk(unsigned int id);
	void destroy();

	unsigned int qSize();
	bool empty();

	void push(PCB* p);
	void print();

	void setCylinders(unsigned int c);
	
	//fix intrp return type so you don't have to throw exception.
	//When intrp is called, the disk requests are sorted according to CLOOK algorithm.
	PCB* intrp();

	//returns id of all queued processes in this device.
	list<PCB*>& queue_list();
	unsigned int diskHeadLocation();

	list<PCB*>::iterator* getHeadPosition();


	friend class devControl;
	friend class mySystem;
};


#include "disk.cpp"


#endif
