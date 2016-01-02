#include "../include/system.h"


mySystem::mySystem()
{

	string p, d, c;

	cout << "How many devices of each type are in your system?" << endl

			 << "Printers: ";
	
	cin >> p;

	while( !isNumber(p) || isNegative(p) )
	{
		cout << "Entry is invalid, enter number of printers again: ";
		cin >> p;

	}

	cout << "Disks: ";
	cin >> d;
	while(!isNumber(d) || isNegative(d) )
	{
		cout << "Entry is invalid, enter number of disks again: ";
		cin >> d;

	}


	while(!isNumber(d) || isNegative(d) )
	{
		cout << "Entry is invalid, enter number of disks again: ";
		cin >> d;

	}

	cout << "CD/RW: ";
	cin >> c;
	while(!isNumber(c) || isNegative(c))
	{
		cout << "Entry is invalid, enter number of CD/RW again: ";
		cin >> c;

	}

	cout << endl;

	devCtrl = devControl( stoui(p), stoui(d), stoui(c));

	cout << endl;

	initCylinders(d);
	setMemSize();
	setTimeSlice();
}

mySystem::~mySystem()
{
	//destroy everything
	schedule.destroy();
	devCtrl.destroy();

}

void mySystem::setMemSize()
{
	string memSize;
	cout << "Enter the memory size: ";
	cin >> memSize;

	while(!isNumber(memSize) || isNegative(memSize))
	{
		cout << "Invalid entry, enter a non-negative number: ";
		cin >> memSize;

	}

	unsigned int memorySize = stoui(memSize);

	mem = memory(memorySize);


}

void mySystem::initCylinders(string d)
{

	unsigned int numDisks = stoui(d);
	string cylinders;

	cout << "Enter the number of cylinders for each disk: " << endl;
	for(unsigned int i =1; i <= numDisks; i++)
	{
		cout << "For disk " << i << ": ";
		cin >> cylinders;

		while(!isNumber(cylinders) || isNegative(cylinders) )
		{
			cout << "Entry is invalid, enter number of cylinders again: ";
			cin >> cylinders;

		}
		
		devCtrl.dv[i-1].setCylinders( stoui(cylinders));
	}

	cout << endl;
}

void mySystem::setTimeSlice()
{


	string timeSlice;

	cout << "Enter the time slice(ms): ";

	cin >> timeSlice;

	while(!isNumber(timeSlice) || isNegative(timeSlice) )
	{
		cout << "Entry is invalid, enter the time slice again(ms): ";
		cin >> timeSlice;

	}
	
	slice = stoui(timeSlice);

	cout << endl;


}
void mySystem::addReady(PCB* p)
{

	schedule.add(p);


}

bool mySystem::emptyCPU()
{

	return schedule.emptyCPU();



}

void mySystem::readWriteCheck(string & rw)
{

	while(rw != "r" && rw != "R" && rw != "w" && rw != "W" )
	{
		cout << "ERROR: unknown command, enter again(r/w): ";
		cin >> rw;
	}

}
void mySystem::setProcessTime(PCB* p)
{

	//
	// Get new CPU Burst time
	//
	string timeElapsed;
	cout << "Enter execution time for process " << p->getID() << ": ";
	cin >> timeElapsed;
	while(!isNumber(timeElapsed) || isNegative(timeElapsed) || stoui(timeElapsed) > slice)
	{
		cout << "Invalid entry, enter execution time again(0 <= entry <= time slice): ";
		cin >> timeElapsed;

	}

	//
	// Set new CPU Burst time
	//
	//cout << "timeElapsed: " << timeElapsed << endl;
	//cout << "stoui(timeElapsed): " << stoui(timeElapsed) << endl;
	p->addTime(stoui(timeElapsed));

	p->updateCPUBurstCount();

}

void mySystem::activeProcessID(unsigned int& id)
{


	schedule.activeProcess(id);


}

unsigned int mySystem::cylinderRequest(unsigned int id)
{
	string cylinder;

	cout << "Enter the cylinder number: ";

	cin >> cylinder;


	while(!isNumber(cylinder) || isNegative(cylinder) || (stoui(cylinder)>(devCtrl.dv[id-1].cylinders -1)))
	{
		cout << "Cylinders start at 0." << endl;
		cout << "Enter unsigned integer not exceeding cylinder count: ";
		cin >> cylinder;

	}


	return stoui(cylinder);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																							DEVICE REQUEST
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool mySystem::decipherLogicAddr(string& memLoca, string& segNumber, string& offset)
{

	string segNum_str = "";
	string offset_str = "";
	bool parsingSegNum = true;

	bool foundSegNumber = false;
	bool foundComma = false;
	bool foundOffset = false;

	for(unsigned int i=0; i< memLoca.length(); i++)
	{
		if(parsingSegNum && isdigit(memLoca[i]))
		{
			foundSegNumber = true;
			segNum_str += memLoca[i];

		}
		else if(memLoca[i] == ',')
		{
			foundComma = true;
			parsingSegNum = false;

		}
		if(!parsingSegNum && isdigit(memLoca[i]))
		{

			foundOffset = true;
			offset_str += memLoca[i];

		}
	}

	segNumber = segNum_str;
	offset = offset_str;

	return foundSegNumber && foundComma && foundOffset;

}


void mySystem::getMemoryLocation(PCB* p, unsigned int& segNumber, unsigned int& offset)
{
	string memLoca;
	string segNum_str;
	string offset_str;
	bool validEntry = false;

	cin.ignore (numeric_limits<streamsize>::max(), '\n'); 

	cout << "Enter memory location (segment#, comma, space, offset): ";

	getline(cin, memLoca, '\n');

	//cout << "memLoca: " << memLoca << endl;

	validEntry = decipherLogicAddr(memLoca, segNum_str, offset_str);

	while(!isNumber(segNum_str) || !isNumber(offset_str) ||  segNum_str[0] =='-' || offset_str[0] =='-' || !validEntry)
	{
		//cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		cout << "Invalid logical address, enter again: ";
		getline(cin, memLoca, '\n');
		validEntry = decipherLogicAddr(memLoca, segNum_str, offset_str);

	}

	segNumber = stoui(segNum_str);
	offset = stoui(offset_str);
	vector<Segment*> segTable = p->getSegTable();

	unsigned int limit = mem.size()+1;

	if(segNumber < segTable.size())
		limit = segTable[segNumber]->limit();


	while(segNumber >= segTable.size() || offset >= limit || !validEntry)
	{
		//cin.ignore (numeric_limits<streamsize>::max(), '\n'); 
		cout << "Invalid logical address, enter again: ";
		getline(cin, memLoca, '\n');
		validEntry = decipherLogicAddr(memLoca, segNum_str, offset_str);


		while(!isNumber(segNum_str) || !isNumber(offset_str) ||  segNum_str[0] =='-' || offset_str[0] =='-' || !validEntry)
		{
			//cin.ignore (numeric_limits<streamsize>::max(), '\n'); 
			cout << "Invalid entry, enter again: ";
			getline(cin, memLoca, '\n');
		
			validEntry = decipherLogicAddr(memLoca, segNum_str, offset_str);

		}

		segNumber = stoui(segNum_str);
		offset = stoui(offset_str);
	}
	
}

void mySystem::devReq(string com)
{

	if(!schedule.emptyCPU())
		switch(com[0])
		{
			case 'p' :
			{
				unsigned int id = stoui(com.substr(1, com.length()-1) );
			

				if( id > devCtrl.pSize())
					cout << "Printer " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;

				else if(id <= devCtrl.pSize() && id> 0)
				{ 

					PCB* cur_active_proc = schedule.activeProcess();
				
					if(cur_active_proc != nullptr)
					{
						unsigned int segNumber=0, offset=0;

						getMemoryLocation(cur_active_proc, segNumber, offset);
						vector<Segment*> segTable = cur_active_proc->getSegTable();
						unsigned int physicalAddr = (segTable[segNumber]->base() + offset);
						cur_active_proc->setMem(physicalAddr);
						cout << "Corresponding physical address: " << physicalAddr << endl;
						setProcessTime(cur_active_proc);

						



						//move process to device
						cur_active_proc->setAct(2);
						devCtrl.pushPrinter(cur_active_proc, id);

						schedule.cleanCPU();


						cout << endl;


						cout << "Process " << cur_active_proc->getID() << ": requested physical address: " << physicalAddr << endl << endl;
						snapshotPrinter();
						cout << endl;
				
					}

					else if(cur_active_proc == nullptr)	
						cout << "ERROR: CPU is currently idle!" << endl;

				}
				else 					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl;

				break;

			}


			case 'd' :
			{
				unsigned int id = stoui(com.substr(1, com.length()-1) );
			
				//cout << "disk size: " << devCtrl.dSize() << endl;
				if( id > devCtrl.dSize())
					cout << "Disk " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;


				else if(id <= devCtrl.dSize())
				{ 

					PCB* cur_active_proc = schedule.activeProcess();
		
					//cout << "Process status before term:" << cur_active_proc->getStat() << endl;
					//cout << "Process " << cur_active_proc->getID() << " queued in disk " << id << endl;

					if(cur_active_proc != nullptr)
					{
						unsigned int segNumber=0, offset=0;

						getMemoryLocation(cur_active_proc, segNumber, offset);

						vector<Segment*> segTable = cur_active_proc->getSegTable();
						unsigned int physicalAddr = (segTable[segNumber]->base() + offset);
						cur_active_proc->setMem(physicalAddr);
						cout << "Corresponding physical address: " << physicalAddr << endl;


						setProcessTime(cur_active_proc);

				

						string read_or_write;

						cout << "Do you wish to read or write to disk?(r/w) ";
						cin >> read_or_write;


						
						readWriteCheck(read_or_write);
						cur_active_proc->setCylinder(cylinderRequest(id));



						if(read_or_write == "r" || read_or_write == "R")
							cur_active_proc->setAct(1);

						else if(read_or_write == "w" || read_or_write == "W")
							cur_active_proc->setAct(2);

						//move process to device

						devCtrl.pushDisk(cur_active_proc, id);

						schedule.cleanCPU();

						cout << endl;

						cout << "Process " << cur_active_proc->getID() << ": requested physical address: " << physicalAddr << endl << endl;
						snapshotDisk();
						cout << endl;
						//cout << "Process status after term:" << cur_active_proc->getStat() << endl;
					}

					else if(cur_active_proc == nullptr)	
						cout << "ERROR: CPU is currently idle!" << endl;

				}
				else 					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl;

				break;
			}



			case 'c' :
			{
				unsigned int id = stoui(com.substr(1, com.length()-1) );
			
				if( id > devCtrl.cSize())
					cout << "Disk " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;


				else if(id <= devCtrl.cSize())
				{ 

					PCB* cur_active_proc = schedule.activeProcess();
		
					//cout << "Process status before term:" << cur_active_proc->getStat() << endl;
					//cout << "Process " << cur_active_proc->getID() << " queued in disk " << id << endl;

					if(cur_active_proc != nullptr)
					{
						unsigned int segNumber=0, offset=0;
						getMemoryLocation(cur_active_proc, segNumber, offset);


						vector<Segment*> segTable = cur_active_proc->getSegTable();
						unsigned int physicalAddr = (segTable[segNumber]->base() + offset);
						cur_active_proc->setMem(physicalAddr);
						cout << "Corresponding physical address: " << physicalAddr << endl;
						setProcessTime(cur_active_proc);
			


						string read_or_write;
		
						cout << "Do you wish to read or write to CD/RW?(r/w) ";
						cin >> read_or_write;

						readWriteCheck(read_or_write);
						

						if(read_or_write == "r" || read_or_write == "R")
							cur_active_proc->setAct(1);

						else if(read_or_write == "w" || read_or_write == "W")
							cur_active_proc->setAct(2);
						//move process to device

						devCtrl.pushCDRW(cur_active_proc, id);

						schedule.cleanCPU();

						cout << endl;


						cout << "Process " << cur_active_proc->getID() << ": requested physical address: " << physicalAddr << endl << endl;
						snapshotCDRW();
						cout << endl;
						//cout << "Process status after term:" << cur_active_proc->getStat() << endl;
					}

					else if(cur_active_proc == nullptr)	
						cout << "ERROR: CPU is currently idle!" << endl;

				}
				else 					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl << endl;

				break;

			}

		}

	else cout << "ERROR: CPU currently idle!" << endl;

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																					DEVICE INTERRUPT
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mySystem::devInterrupt(string com)
{


	switch(com[0])
	{
		case 'P' :
		{

			if(devCtrl.pSize() > 0)
			{

				unsigned int id = stoui(com.substr(1, com.length()-1));

				if( id > devCtrl.pSize())
					cout << "Printer " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;


				else if(!devCtrl.pEmpty(id) && id > 0) 	
				{
					PCB * PCB_ptr = devCtrl.pIntrp(com);

					if(PCB_ptr != nullptr)
					{
						PCB_ptr->setAct(0);
						PCB_ptr->setStat(1);
						cout << "Adding process " << PCB_ptr->getID() << " to the back of ready queue." << endl;
						addReady(PCB_ptr);
					}
				

				}

				else if(devCtrl.pEmpty(id)) 	
				{
				
					cout << "ERROR: Printer " << com.substr(1, com.length()-1) << " is empty!" << endl;
					

				}
				else if(id <= 0) 	
				{
					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl;
					
				}

			}


			else if(devCtrl.cSize() == 0)
				cout << "ERROR: No printer devices. " << endl;

			break;

		}

		case 'D' :
		{

			if(devCtrl.dSize() > 0)
			{

				unsigned int id = stoui(com.substr(1, com.length()-1));

				if( id > devCtrl.dSize())
					cout << "Disk " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;


				else if(!devCtrl.dEmpty(id) && id > 0) 	
				{

					PCB * PCB_ptr = devCtrl.dIntrp(com);
					PCB_ptr->setAct(0);
					PCB_ptr->setStat(1);
					cout << "Adding process " << PCB_ptr->getID() << " to the back of ready queue." << endl;
					addReady(PCB_ptr);
					
				}


				else if(devCtrl.dEmpty(id)) 	
				{
					
					cout << "ERROR: Disk " << com.substr(1, com.length()-1) << " is empty!" << endl;
					

				}
				else if(id <= 0) 	
				{
					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl;
					

				}

			}
			else if(devCtrl.cSize() == 0)
				cout << "ERROR: No disk devices. " << endl;

			break;



		}

		case 'C' :
		{


			if(devCtrl.cSize() > 0)
			{

				unsigned int id = stoui(com.substr(1, com.length()-1));

				if( id > devCtrl.cSize())
					cout << "CD/RW " << com.substr(1, com.length()-1) << " doesn't exist!" << endl;


				else if(!devCtrl.cEmpty(id) && id > 0) 	
				{
					PCB * PCB_ptr = devCtrl.cIntrp(com);
					PCB_ptr->setAct(0);
					PCB_ptr->setStat(1);
					cout << "Adding process " << PCB_ptr->getID() << " to the back of ready queue." << endl;
					addReady(PCB_ptr);
					
				}


				else if(devCtrl.dEmpty(id)) 	
				{
					
					cout << "ERROR: CD/RW " << com.substr(1, com.length()-1) << " is empty!" << endl;
					

				}

				else if(id <= 0) 	
				{
					
					cout << "ERROR: Invalid device id. Device ids start at 1." << endl;
					

				}

			}

			else if(devCtrl.cSize() == 0)
				cout << "ERROR: No CD/RW devices. " << endl;

			break;

		}
	}



}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																								SNAPSHOT
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mySystem::snapshotReady()
{
	queue<PCB*> temp = schedule.readyQ();

	if(!temp.empty())
	{
		
		cout << left << setw(5) << "PID" << setw(11) << "TotalTime" << setw(10) << "AvgTime" << setw(10) << "Seg(B, L)" << endl;
		for(unsigned int i = 0; temp.size() != 0; i++)
		{
			cout << left << setw(5) << temp.front()->getID() << setw(11) << temp.front()->getTotalExecTime() << setw(10) 
					 << temp.front()->getAvgCPUBurst();
		
	
			vector<Segment*> segmentTable = temp.front()->getSegTable();

			for(unsigned int i = 0; i<segmentTable.size();  ++i )
			{
				if(i!= 0 && i%2 == 0)
					cout << endl << setw(26) << "" ;

				cout << left << '(' << segmentTable[i]->base() << ", " << segmentTable[i]->limit() << ") ";


			}

			temp.pop();
			cout << endl;
			

		}
	
	}
	
	else cout << "Ready queue is empty." << endl; 


}


void mySystem::snapshotPrinter()
{

	vector< vector<PCB*> > ids;
	devCtrl.allPrinterQ(ids);
	vector<PCB*> temp;

	cout << left << setw(5) << "PID" << setw(7) <<"File" << setw(10) << "Memstart" << setw(5) << "R/W" 
			 << setw(9) << "FileLen" << setw(11) << "TotalTime" << setw(9) << "AvgTime" << setw(10) << "Seg(B, L)" << endl;



	for(unsigned int i = 1; i <= ids.size(); i++)
	{
		cout << endl << "----printer" << i << endl;
		//temp is queue of processes in device id i-1
		temp = ids[i-1];

		for(auto &p: temp)
		{

			cout << left << setw(5) << p->getID() << setw(7) << p->getFile() << setw(10) << p->getMem() << setw(5) << p->getAct() 
					 << setw(9) << p->getFileLen() << setw(11) << p->getTotalExecTime() << setw(9) << p->getAvgCPUBurst();

			vector<Segment*> segmentTable = p->getSegTable();

			for(unsigned int j = 0; j<segmentTable.size();  ++j )
			{
				if(j!= 0 && j%2 == 0)
					cout << endl << setw(56) << "" ;

				cout << left << '(' << segmentTable[j]->base() << ", " << segmentTable[j]->limit() << ") ";



			}

			cout << endl;

		}

	}



}

void mySystem::snapshotDisk()
{
	vector< list<PCB*>* > disk_lists;
	devCtrl.allDiskQ(disk_lists);
	list<PCB*>* temp;


	cout << left << setw(5) << "PID" << setw(7) <<"File" << setw(10) << "Memstart" << setw(5) << "R/W" 
			 << setw(9) << "FileLen" << setw(11) << "TotalTime" << setw(9) << "AvgTime" <<  setw(5) << "Cyl" << setw(10) << "Seg(B, L)" << endl;;



	for(unsigned int i = 1; i <= disk_lists.size(); i++)
	{
		cout << endl << "----disk" << i << "(disk head at " << devCtrl.getCurrentCylinder(i) <<')' << endl;
		temp = disk_lists[i-1]; //get the (i-1)th disk list.

		if(!temp->empty())
		{
			list<PCB*>::iterator headPosition = *(devCtrl.getHeadPosition(i));
			list<PCB*>::iterator it = headPosition;

			//cout << "In snapshot: process " << (*it)->getID() << " address: " << (*it) << endl;

			//iterate starting from current head position
			for(; it != temp->end(); ++it)
			{
				cout << left << setw(5) << (*it)->getID() << setw(7) << (*it)->getFile() << setw(10) << (*it)->getMem() << setw(5) 
						 << (*it)->getAct() << setw(9) << (*it)->getFileLen() << setw(11) << (*it)->getTotalExecTime() << setw(9) 
						 << (*it)->getAvgCPUBurst() << setw(5) << (*it)->getCylinder();

				vector<Segment*> segmentTable = (*it)->getSegTable();

				for(unsigned int j = 0; j<segmentTable.size();  ++j )
				{

					if(j!= 0 && j%2 == 0)
						cout << endl << setw(61) << "" ;

					cout << left << '(' << segmentTable[j]->base() << ", " << segmentTable[j]->limit() << ") ";



				}

				cout << endl;
			}

			it = temp->begin();

			//c-look wrap-around
			for(; it != headPosition; ++it)
			{
				cout << left << setw(5) << (*it)->getID() << setw(7) << (*it)->getFile() << setw(10) << (*it)->getMem() << setw(5) 
						 << (*it)->getAct() << setw(9) << (*it)->getFileLen() << setw(11) << (*it)->getTotalExecTime() << setw(9) 
						 << (*it)->getAvgCPUBurst() << setw(5) << (*it)->getCylinder();

				vector<Segment*> segmentTable = (*it)->getSegTable();

				for(unsigned int j = 0; j<segmentTable.size();  ++j )
				{
					if(j!= 0 && j%2 == 0)
						cout << endl << setw(61) << "" ;

					cout << left << '(' << segmentTable[j]->base() << ", " << segmentTable[j]->limit() << ") ";


				}

				cout << endl;
			}
		}
	}


}

void mySystem::snapshotCDRW()
{

	vector< vector<PCB*> > ids;
	devCtrl.allCDRWQ(ids);
	vector<PCB*> temp;


	cout << left << setw(5) << "PID" << setw(7) <<"File" << setw(10) << "Memstart" << setw(5) << "R/W" 
			 << setw(10) << "FileLen" << setw(11) << "TotalTime" << setw(9) << "AvgTime" << setw(9) << "seg(B, L)" << endl;



	for(unsigned int i = 1; i <= ids.size(); i++)
	{
		cout << endl << "----CD/RW" << i << endl;
		temp = ids[i-1];


		for(auto &p: temp)
		{

			cout << left << setw(5) << p->getID() << setw(7) << p->getFile() << setw(10) << p->getMem() << setw(5) << p->getAct() << setw(10) << p->getFileLen() 
					 << setw(11) << p->getTotalExecTime() << setw(9) << p->getAvgCPUBurst();

			vector<Segment*> segmentTable = p->getSegTable();

			for(unsigned int j = 0; j<segmentTable.size();  ++j )
			{
				if(j!= 0 && j%2 == 0)
					cout << endl << setw(57) << "" ;

				cout << left << '(' << segmentTable[j]->base() << ", " << segmentTable[j]->limit() << ") ";

			
					

			}

			cout << endl;
		}

	}




}
void mySystem::snapshot(string command)
{
	bool unknownComm = true;


	while(unknownComm || command.length() != 1)
	{
		cout << "Enter display command(r, p, c, d, m): ";
		cin >> command;
		cout << endl;
		
		if(command.length() == 1)
		switch(command[0])
		{
			case 'r': 
			{
				
				snapshotReady();
				unknownComm = false; break;
			}


			case 'p': 
			{

				snapshotPrinter();
				unknownComm = false; break;
			}



			case 'd': 
			{

				snapshotDisk();

				unknownComm = false; 
				break;
			}

			case 'c': 
			{
				snapshotCDRW();
				unknownComm = false;
				break;
			}
	
			case 'm':
			{

				cout << mem << endl;

				unknownComm = false;
				break;
			}

		
			default: cout << "Unknown command." << endl;

		}
	}

	cout << "\nTerminated processes: " << completedProcesses << endl;
	cout << "Total processing time of completed processes: " << totalProcessTime << endl;
	//cout << "\nTotal process time: " << totalProcessTime << endl;
	cout << "Average total CPU time of terminated processes: " << avgTotalProcessTime << endl;



}







//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																														RUN
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mySystem::comCheck(string& command)
{

	while(  (command.length() < 0 || isNumber(command[0]) )  )
		{
			cout << "Unknown command." << endl << endl

					 << "Enter command: ";
	
			cin >> command;

			

		}

}


void mySystem::allocate(PCB* p)
{
	string segAmount_str;
	//
	//BEGIN: receving input
	//
	cout << "Enter number of segments: ";
	cin >> segAmount_str;

	while(!isNumber(segAmount_str) || segAmount_str[0] == '-')
	{
		cout << "Entry must be a nonnegative number, Enter again: ";
		cin >> segAmount_str;
	}
	//
	//END: receving input
	//

	unsigned int segAmount = stoui(segAmount_str);
	unsigned int limit;
	string lim_str;
	unsigned int size=0;

	vector<unsigned int> limitsTable;

	//
	//BEGIN: receving input
	//
	for(unsigned int i = 0; i <segAmount; i++ )
	{
		cout << "Enter limit for segment entry " << i << ": ";
		cin >> lim_str;

		while(!isNumber(lim_str) || lim_str[0] == '-'  || stoui(lim_str) == 0)
		{
			cout << "Entry must be a positive number(excludes 0), Enter again: ";
			cin >> lim_str;
		}

		limit = stoui(lim_str);
		size += limit;

		if(size>mem.size())
		{	
			cout << "Error: process size greater than memory." << endl;
			return;
		}

		limitsTable.push_back(limit);

	}

	//
	//END: receving input
	//


	p->setSize(size);

	//recalculates available and used memory just in case
	mem.updateAccount();
	bool allocated = false;
	if(size <= mem.available())
	{
		for(unsigned int i=0; i<limitsTable.size(); i++)
		{

			allocated = mem.allocate(p, limitsTable[i]);

		}

		if(allocated)
			addReady(p);


		else //compact memory and try again
		{
			cout << "Memory too fragmented to fit Process " << p->getID() << '.' << endl;
			cout << "Memory is being compacted..." << endl;
			mem.moveSegmentsUp();

			for(unsigned int i=0; i<limitsTable.size(); i++)
			{

				allocated = mem.allocate(p, limitsTable[i]);

			}
			if(allocated)
				addReady(p);

			else
				cout << "ERROR: Could not allocate process " << p->getID() << endl; 
		}

	}

	else if(size > mem.size())
	{
		cout << "Not enough memory for process " << p->getID() << endl;
		return;

	}

	else if(size > mem.available())
	{
		*(p->getLimitsTable()) = limitsTable;
		cout << "Process size: " << size << endl;
		cout << "Memory available: " << mem.available() << endl;
		cout << "Not enough memory for process " << p->getID() << endl;
		cout << "Process " << p->getID() << " moved to job pool." << endl;
		putInPool(p);
		return;

	}

}


void mySystem::putInPool(PCB* p)
{

	list<PCB*>::iterator itr = devCtrl.jobPool.begin();

	if(devCtrl.jobPool.empty())
	{
		devCtrl.jobPool.push_front(p);

		return;
	}

	for(; itr != devCtrl.jobPool.end(); ++itr)
	{
		if(p->size() <= (*itr)->size())
		{
	
			devCtrl.jobPool.insert(itr, p);
			p->setStat(0);
			break;
		}
	}

}

//called after a process terminates
void mySystem::checkJobPool()
{
	list<PCB*>::iterator poolItr = devCtrl.getJobPool().begin();
	mem.updateAccount();
	unsigned int memAvailable = mem.available(); 
	bool allocated = false;

	if(devCtrl.jobPool.empty())
		return;

	for(; poolItr != devCtrl.jobPool.end(); ++poolItr)
	{
	
		if((*poolItr)->size() <= memAvailable)
		{
				cout << "Attempting to move process " << (*poolItr)->getID() << " to memory." << endl;
				//put in mem.
				vector<unsigned int> limitsTable = *((*poolItr)->getLimitsTable());

				for(unsigned int i=0; i<limitsTable.size(); i++)
				{

					allocated = mem.allocate(*poolItr, limitsTable[i]);

				}


				if(allocated)
				{

					addReady((*poolItr));

					poolItr = devCtrl.jobPool.erase(poolItr);

				}
				else
					cout << "ERROR: Could not allocate process " << (*poolItr)->getID() << endl; 
		}

	}


	if(!allocated)
	{
		cout << "Memory too fragmented to fit." << endl;
		cout << "Memory is being compacted." << endl;
		mem.moveSegmentsUp();

		poolItr = devCtrl.jobPool.begin();
	
		for(; poolItr != devCtrl.jobPool.end(); ++poolItr)
		{
	
			if((*poolItr)->size() <= memAvailable)
			{
					cout << "Attempting again to move process " << (*poolItr)->getID() << " to memory." << endl;
					//put in mem.
					vector<unsigned int> limitsTable = *((*poolItr)->getLimitsTable());

					for(unsigned int i=0; i<limitsTable.size(); i++)
					{

						allocated = mem.allocate(*poolItr, limitsTable[i]);

					}



					addReady((*poolItr));

					poolItr = devCtrl.jobPool.erase(poolItr);


			}

		}

	}




	
}
void mySystem::run()
{

	string command;


	while(command != "quit")
	{
		cout << "Enter command: ";
		cin >> command;

		comCheck(command);


		////////////////////////////////////////////
		//
		// ADDING NEW PROCESS
		//
		////////////////////////////////////////////
		if(command.length() == 1 && command[0] == 'A')
		{
			cout << "Adding new process..." << endl;

			PCB *p = new PCB();
			p->setPID();
			allocate(p);
		

			//cout << "PID: " << p.getID() << endl; 

		}


		////////////////////////////////////////////
		//
		// 		TERMINATION
		//
		////////////////////////////////////////////
		else if(command.length() == 1 && command[0] == 't')
		{
			cout << "Terminating..." << endl;
			unsigned processTotalTime;
			//requested pointer to memory stored inside CPU queue.
			PCB* cur_active_proc = schedule.activeProcess();
	

			if(cur_active_proc != nullptr)
			{

				setProcessTime(cur_active_proc);

			}

			//Pointer to memory location is invalidated when CPU.pop() is called.
			if(schedule.terminate(processTotalTime, mem))
			{

				//By now the only process in CPU has been popped, and the memory is freed since it wasn't dynamically allocated.
				totalProcessTime+=processTotalTime;
				
				completedProcesses++;
		
				
				double temp = totalProcessTime;

				avgTotalProcessTime = (temp/completedProcesses);	

				cout << "\nTerminated processes: " << completedProcesses << endl;
				cout << "Total processing time of completed processes: " << totalProcessTime << endl;
				cout << "Average total CPU time of terminated processes: " << avgTotalProcessTime << endl;
				
				//cout << "cur_active_proc: " << *cur_active_proc << endl;	
				//Therefore there is no reason to call the below delete.
				//delete cur_active_proc;
			
			
				checkJobPool();
			
			}

			//else cout << "ERROR: CPU is empty." << endl;
		}

		////////////////////////////////////////////
		//
		// 		TIMER INTERRUPT
		//
		////////////////////////////////////////////
		else if(command.length() == 1 && command[0] == 'T')
		{
			cout << "Timer Interrupt!" << endl;
			PCB* cur_active_proc = schedule.activeProcess();

			if(cur_active_proc != nullptr)
			{
				cur_active_proc->setTotalExecTime(( (cur_active_proc->getTotalExecTime()) + slice ));

				//Timer Interrupts are not system calls and don't count as end of CPU burst.
				//cur_active_proc->updateCPUBurstCount();

				schedule.cleanCPU();
				//cout << "Adding process " << cur_active_proc->getID() << endl;
				schedule.add(cur_active_proc);

			}

			
		}


		////////////////////////////////////////////
		//
		// 		SYSTEM CALLS
		//	(Device request)
		////////////////////////////////////////////
		else if(command.length() > 1 && (command[0] == 'p' || command[0] == 'd' || command[0] == 'c') && isNumber( command.substr(1, (command.length()-1))) && !isNegative( command.substr(1, (command.length()-1))) )
		{
			cout << "Requesting device..." << endl;
			devReq(command);


		}


		////////////////////////////////////////////
		//
		// 			INTERRUPT
		//	(Task completion)
		////////////////////////////////////////////
		else if(command.length() > 1 && (command[0] == 'P' || command[0] == 'D' || command[0] == 'C') && isNumber( command.substr(1, (command.length()-1))) && !isNegative( command.substr(1, (command.length()-1)))  )
		{

			cout << "Interrupting Device..." << endl;
			devInterrupt(command);

		}


		////////////////////////////////////////////
		//
		// 			SNAPSHOT
		//
		////////////////////////////////////////////
		else if(command.length() ==1 && command[0] == 'S')	
		{
			snapshot(command);

		}

		////////////////////////////////////////////
		//
		// 			DEBUGGER
		//
		////////////////////////////////////////////
		else if(command == "db")	
		{
			PCB* cur_process = schedule.activeProcess();

			if(cur_process != nullptr)
			{
				cout << "Current process in CPU: " << endl;
				cout << endl;
				cout << left << setw(12) << "PID" << setw(13) << "Total Time" << setw(13) << "Average Time" << endl;
				cout << endl << "----process" << endl;
				cout << left << setw(12) << cur_process->getID() << setw(13) << cur_process->getTotalExecTime() << setw(13) << cur_process->getAvgCPUBurst() << endl;
				cout << left << setw(5) << "PID" << setw(8) << "Hole?" << setw(10) << "seg(B, L)" << endl;
		
				for(auto &segPtr: cur_process->getSegTable())
				{
					
					cout << left << setw(5) << cur_process->getID() << setw(8) << segPtr->isHole() << *segPtr << endl;

				}



			}
			cout << "\n\nJob pool: " << endl;
			cout << left << setw(5) << "PID" << setw(8) << "Limits" << endl;
			for(auto &p: devCtrl.jobPool)
			{	
				cout << left << setw(5) << p->getID();
				
				vector<unsigned int> limitsTable = *(p->getLimitsTable());

				for(unsigned int i = 0; i<limitsTable.size();  ++i )
				{
					cout << limitsTable[i] <<  ' ';

				}
				cout << endl;
			}

		}


		////////////////////////////////////////////
		// 			COMMAND
		//			UNKNOWN
		//
		////////////////////////////////////////////
		else cout << "Unknown command. " << endl;


		cout << endl;


	}


}
















