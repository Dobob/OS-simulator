#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "pcb.h"
#include "../lib/include/cqueue.h"

class scheduler
{
	private:
	//The index corresponds to whetther ID# is active: process[0] == true means ID#0 is in use;
	//vector<bool> process;

	//queue<PCB> ready_q;
	queue<PCB*> CPU;

	queue<PCB*> ready_q;



	
	public:

	scheduler();
	void destroy();
	//passes new process to scheduler. 
	//Currently adds to ready queue.
	void add(PCB* p);

	//returns total time used by terminated process.
	bool terminate(unsigned int& totalProcessTime, memory& mem);
	bool cleanCPU();

	void activeProcess(unsigned int& id);

	bool emptyCPU();

	PCB* activeProcess();

	queue<PCB*> readyQ();

	//friend class mySystem;


};



#include "../src/scheduler.cpp"

#endif
