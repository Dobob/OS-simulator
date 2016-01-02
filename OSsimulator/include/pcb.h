#ifndef PCB_H
#define PCB_H


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility> 
#include "pid.h"
#include "segment.h"



/*
65 - 90 A-Z

97 - 122 a-z
*/

class PCB
{
	private:
	//Each time a PCB is created, a new unique PID is automatically generated.
	PID id_;

	//JOB_POOL = 0, TERMINATED = 4
	enum status {JOB_POOL, READY, RUNNING, WAITING, TERMINATED};
	status s;

	enum action {IDLE, READ, WRITE};
	action act;
	
	unsigned int physicalMemLoca;

	string file;

	//pair of segment number and offset
	//list<pair<unsigned int, unsigned int>> logicAddress;

	//Processes initialized a limitsTable when pushed into job pool
	vector<unsigned int> limitsTable;
	//Processes initialized a segTable when pushed into memory
	vector<Segment*> segTable;


	unsigned int size_;
	unsigned int fileLen;

	//cylinder only used for disk
	unsigned int cylinder=0;
	unsigned int totalExecTime=0;
	unsigned int CPUBurstCount=0;
	double avgCPUBurst=0.0;



	public:

	PCB();	
	PCB(const PCB& p);
	PCB(PCB&& p);
	PCB(unsigned int stat);
	//no need to implement destructor since nothing is stored in the heap.
	~PCB();

	unsigned int size() const;
	unsigned int getID() const;
	unsigned int getStat() const;
	unsigned int getCylinder() const;
	unsigned int getFileLen();
	unsigned int getTotalExecTime();
	unsigned int getMem();
	vector<unsigned int>* getLimitsTable();
	vector<Segment*>& getSegTable();


	void printSegTable();


	double getAvgCPUBurst();
	char getAct();
	
	string getActString();
	string getFile();


	void insertSegTable(Segment*& s);

	void setSize(unsigned int s);
	void setStat(unsigned int stat);
	void setAct(unsigned int a);
	void setTotalExecTime(unsigned int t);
	void setFile(string f);
	void setMem(unsigned int m);
	void setFileLen(unsigned int fl);
	void setPID();
  void updateAvgCPUBurst();
	void updateCPUBurstCount();
	void setCylinder(unsigned int c);
	void addTime(unsigned int t);

	PCB& operator=(const PCB& p);
	PCB& operator=(PCB&& p);

	//friend class mySystem;
	//friend class memory;
	//friend class scheduler;
	//friend class devControl;
	//friend class disk;
	friend ostream& operator<<(ostream& out_stream, const PCB& p);

};


#include "../src/pcb.cpp"


#endif
