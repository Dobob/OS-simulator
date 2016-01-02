#ifndef SYSTEM_H
#define SYSTEM_H


#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "pcb.h"
#include "memory.h"
#include "segment.h"
#include "../device/devControl.h"
#include "scheduler.h"
#include "../lib/include/useful.h"

/*

	Process ID are not recycled. Once used, it won't be used again if the process terminates.

*/

unsigned int PID::next_PID = 1;
class mySystem
{
	private:
	unsigned int slice;
	unsigned int completedProcesses=0;
	unsigned int totalProcessTime=0;
	double avgTotalProcessTime=0.0;


	memory mem;
	devControl devCtrl;
	scheduler schedule;


	public:

	mySystem();
  ~mySystem();

	void addReady(PCB* p);
	

	void devReq(string com);
	void devInterrupt(string com);


	bool emptyCPU();

	void allocate(PCB* p);
	void putInPool(PCB* p);
	void checkJobPool();
	void getMemoryLocation(PCB* p, unsigned int& segNumber, unsigned int& offset);
	bool decipherLogicAddr(string& memLoca, string& segNumber, string& offset);


	void initCylinders(string d);
	void setMemSize();	
	void setTimeSlice();
	void selectMemLoc(unsigned int limit);
	//updated CPUBurstcount, avgBurstTime, and totalExecTime of process after the process leaves the CPU.
	void setProcessTime(PCB* p);
	void activeProcessID(unsigned int& id);
	void snapshot(string com);
	void comCheck(string& command);
	void readWriteCheck(string & rw);
	void run();

	void snapshotReady();
	void snapshotPrinter();
	void snapshotDisk();
	void snapshotCDRW();



	unsigned int cylinderRequest(unsigned int id);
	

	//vector<unsigned int> printerQ(unsigned int id);
	//vector<unsigned int> readyQ();
};


#include "../src/system.cpp"


#endif
