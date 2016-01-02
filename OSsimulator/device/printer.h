#ifndef PRINTER_H
#define PRINTER_H


#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "../include/pcb.h"
#include "../lib/include/useful.h"

using namespace std;

class printer
{

	private:

	unsigned int id_;
	queue<PCB*> print_q;


	public:
	printer();

	void destroy();
	printer(unsigned int id);


	unsigned int qSize();
	bool empty();

	void push(PCB* p);
	void print();

	//fix intrp return type so you don't have to throw exception.
	PCB* intrp();

	//returns id of all queued processes in this device.
	vector<PCB*> queue_vector();

};


#include "printer.cpp"


#endif
