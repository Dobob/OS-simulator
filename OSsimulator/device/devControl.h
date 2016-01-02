#ifndef DEVICE_H
#define DEVICE_H


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include "../lib/include/useful.h"


#include "printer.h"
#include "disk.h"
#include "CDRW.h"

using namespace std;

class devControl
{

	private:

	//We want to separate the device class from here.
	//This is because each device has its own queue.
	//Vector is better in this case since device id are best being sequential.
	//Process ID requires allocation fo special ID for some important processes, so it will not be sequential.
	vector<printer> pv;
	vector<disk> dv;
	vector<CDRW> cv;
	list<PCB*> jobPool;

	public:
	devControl();

	void destroy();
	//initialize a printer, disk, and a CD/RW with respective ids p, d, and c
	devControl(unsigned int p, unsigned int d, unsigned int c);

	//enqueues to the correct device.
	void pushPrinter(PCB* p, unsigned int id);
	void pushDisk(PCB* p, unsigned int id);
	void pushCDRW(PCB* p, unsigned int id);

	void comCheck(string& command);

	//Checks to see if device queue is empty.
	bool pEmpty(unsigned int id);
	bool dEmpty(unsigned int id);
	bool cEmpty(unsigned int id);

	//interrupt dequeues from correct device in the vector, then returns the process dequeued.
	PCB* pIntrp(string pname);
	PCB* dIntrp(string dname);
	PCB* cIntrp(string cname);

	//returns size of device queues.
	unsigned int pSize();
	unsigned int dSize();
	unsigned int cSize();

	void read(PCB& p, unsigned int id);
	void write(PCB& p, unsigned int id);


	list<PCB*>& getJobPool();

	//MAKE EFFICIENT: use pointers to PCBs.
	void allPrinterQ(vector< vector<PCB*> >& v);
	void allDiskQ(vector< list<PCB*>* >& v);
	void allCDRWQ(vector< vector<PCB*> >& v);


	unsigned int getCurrentCylinder(unsigned int diskNumber);
	list<PCB*>::iterator* getHeadPosition(unsigned int diskNumber);

	friend class mySystem;

};


#include "devControl.cpp"


#endif
