#ifndef CDRW_H
#define CDRW_H


#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "../include/pcb.h"
#include "../lib/include/useful.h"

using namespace std;

class CDRW
{

	private:
	unsigned int id_;
	queue<PCB*> CDRW_q;

	public:

	CDRW(unsigned int id);
	void destroy();

	unsigned int qSize();
	bool empty();

	void push(PCB* p);
	void print();
	
	//fix intrp return type so you don't have to throw exception.
	PCB* intrp();

	//returns id of all queued processes in this device.
	vector<PCB*> queue_vector();
};


#include "CDRW.cpp"


#endif
