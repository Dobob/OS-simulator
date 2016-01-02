#include "../include/scheduler.h"

scheduler::scheduler() 
{

}
void scheduler::destroy()
{
	while(!CPU.empty())
	{
		delete CPU.front();
		CPU.front() = nullptr;
		CPU.pop();
	}
	while(!ready_q.empty())
	{
		delete ready_q.front();
		ready_q.front() = nullptr;
		ready_q.pop();
	}
}
void scheduler::add(PCB* p)
{

	//alternatively process[p.getID()] = true;
	//But we would have to assume the vector is of proper size.
	//By using push instead, it allows for better dynamic ID handling.
	//process.push_back(true);
 

	ready_q.push(p);

	cout << "Process " << p->getID() << " is ready." << endl;




	//If CPU is empty, take first ready element and put it in CPU
	if(CPU.empty() && !ready_q.empty())
	{
		CPU.push(ready_q.front());

		CPU.front()->setStat(2);

		ready_q.pop();

		cout << "CPU was empty, process " << p->getID() << " was moved to CPU." << endl;
	}
	
		
		//cout << "END OF ADD " << endl;

}

bool scheduler::terminate(unsigned int& totalProcessTime, memory& mem)
{

	if(CPU.empty())
	{
		//cout << "ERROR: CPU currently idle!" << endl;
		return false;
	}

 	if(!CPU.empty() )
	{
		PCB* p = CPU.front();
		mem.free(*p);
		unsigned int id = p->getID();
		totalProcessTime = p->getTotalExecTime();

		//Since we use local PCB values, we don't need to invoke delete.
		CPU.front()->setStat(4);

		cout << left << setw(12) << "PID" << setw(13) << "Total Time" << setw(13) << "Average Time" << endl;
		cout << endl << "----process" << endl;
		cout << left << setw(12) << id << setw(13) << p->getTotalExecTime() << setw(13) << p->getAvgCPUBurst() << endl;

		//PCB info is lost once it is entirely out of scope.
		CPU.pop(); //after this function exits, all references to p would be lost and data is automatically deallocated.

		delete p;
		p = nullptr;
			
	}

	if(!ready_q.empty())
	{
		//put next process in line into CPU
		CPU.push( ready_q.front());

		CPU.front()->setStat(2);

		ready_q.pop();


	}

	return true;

}
bool scheduler::cleanCPU()
{


	if(CPU.empty())
	{
		cout << "ERROR: CPU currently idle!" << endl;
		return false;
	}

	if(!CPU.empty())
	{
		unsigned int id = CPU.front()->getID();
		//return CPU process to ready_q
		//CPU.front().setStat(1);
		
		//ready_q.push(current_process);
		//cout << "Address ref: " << (&CPU.front()) << endl;
		//The system determines where the process goes, thus it determines what the status of the process is.
		CPU.pop();

		cout << "Process " << id << " was removed from CPU." << endl;

	}

	if(!ready_q.empty())
	{
		//put next process in line into CPU
		//cout << "ready_q.front(): " << ready_q.front() << endl;
		CPU.push( ready_q.front() );

		CPU.front()->setStat(2);


		cout << "Process " << CPU.front()->getID() << " was moved to CPU." << endl;
		//cout << "popping ready_q" << endl;
		ready_q.pop();

	}

	return true;
}


queue<PCB*> scheduler::readyQ()
{
/*
	vector<unsigned int> ret_vec;

	cqueue<PCB> temp_q;
	temp_q = ready_q;

	cout << "ids.size() before: " << ret_vec.size() << endl;
	cout << "ready_q.getNumItems(): " << ready_q.getNumItems() << endl;
	cout << "temp_q.getNumItems(): " << temp_q.getNumItems() << endl;

	while(!temp_q.empty())
	{
		unsigned int id = temp_q.front().getID();

		ret_vec.push_back(id);
		cout << "temp_q is not empty, popping..." << endl;
		temp_q.pop();
	}
		

*/

	return ready_q;
}

bool scheduler::emptyCPU()
{

	return CPU.empty();



}
void scheduler::activeProcess(unsigned int& id)
{
	
	if(!CPU.empty())
		id = CPU.front()->getID();



}
PCB* scheduler::activeProcess()
{
	//cout << "CPU.front.getStat(): " << CPU.front().getStat() << endl;
	PCB * cur_active_proc = CPU.front();
	//cout << "cur_active_proc->getStat(): " << cur_active_proc->getStat() << endl;
	if(!CPU.empty())
		return cur_active_proc;

	else if(CPU.empty())
	 cout <<"ERROR: CPU currently idle!" << endl;

	return nullptr;

}
/*

status::void run()
{

}



status::void wait()
{

}



status::void terminate()
{

}


*/

