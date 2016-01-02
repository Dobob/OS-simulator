#include "devControl.h"


devControl::devControl() 
{



}
void devControl::destroy()
{
	for(auto &printer: pv)
	{
		printer.destroy();

	}

	for(auto &disk: dv)
	{
		disk.destroy();

	}
	for(auto &CDRW: cv)
	{
		CDRW.destroy();

	}
	for(auto &p: jobPool)
	{
		delete p;
		p = nullptr;

	

	}

	pv.clear();
	dv.clear();
	cv.clear();
	jobPool.clear();
}
devControl::devControl(unsigned int p, unsigned int d, unsigned int c)
{


	for(unsigned int i = 1; i <= p; i++)
	{
		
		pv.push_back( printer(i) );
	
	}
	for(unsigned int i = 1; i <= d; i++)
	{
		
		dv.push_back( disk(i) );
	
	}
	for(unsigned int i = 1; i <= c; i++)
	{

		cv.push_back( CDRW(i) );
	
	}

	cout << "Created: " << endl
			 << pv.size() << " printer(s)" << endl
			 << dv.size() << " disk(s)" << endl
			 << cv.size() << " CD/RW(s)" << endl;


}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																									 	QUEUING
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void devControl::comCheck(string& command)
{

	while(  (command.length() < 0 || isNumber(command[0]) )  )
	{
		cout << "\nUnknown command." << endl

				 << "Enter command: ";

		cin >> command;

		
	}

}
void devControl::read(PCB& p, unsigned int id)
{
	string fileName;

	cout << "Enter file name: ";
	cin >> fileName;

	
	p.setFile(fileName);

}
void devControl::write(PCB& p, unsigned int id)
{
	string fileName;
	string fileLength;
	//printers can only write.

	cout << "Enter file name: ";
	cin >> fileName;

	cout << "Enter file length: ";
	cin >> fileLength;

	while(!isNumber(fileLength))
	{
		cout << "File location must be positive integer, enter again: ";
		cin >> fileLength;
	}

	
	p.setFile(fileName);
	p.setFileLen(stoui(fileLength));

}

void devControl::pushPrinter(PCB* p, unsigned int id)
{

	//cout << "Process status:" << p->getStat() << endl;
		//cout << "Process: " << p->getID() << " queued in printer " << id << endl;

	if( p->getStat() == 2)
	{

		write(*p, id);
		
		pv[id-1].push(p);
		p->setStat(3);

	}
	else if(p->getStat() == 4)
	{
		cout << "ERROR: Process was terminated!" << endl;

	}
	else if(p->getStat() == 3)
	{
		cout << "ERROR: Process busy queuing for something else!" << endl;

	}
	else if(p->getStat() != 2)
	{
		cout << "ERROR: Process not running in CPU!" << endl;

	}


}
void devControl::pushDisk(PCB* p, unsigned int id)
{

		//cout << "Process status:" << p->getStat() << endl;
		//cout << "Process: " << p->getID() << " queued in printer " << id << endl;

	if( p->getStat() == 2)
	{

		if(p->getAct() == 'r')
			read(*p, id);

		else if(p->getAct() == 'w')
			write(*p, id);

		dv[id-1].push(p);
		p->setStat(3);

	}
	else if(p->getStat() == 4)
	{
		cout << "ERROR: Process was terminated!" << endl;

	}
	else if(p->getStat() == 3)
	{
		cout << "ERROR: Process busy queuing for something else!" << endl;

	}
	else if(p->getStat() != 2)
	{
		cout << "ERROR: Process not running in CPU!" << endl;

	}
}
void devControl::pushCDRW(PCB* p, unsigned int id)
{

		//cout << "Process status:" << p->getStat() << endl;
		//cout << "Process: " << p->getID() << " queued in printer " << id << endl;

	if( p->getStat() == 2)
	{

		if(p->getAct() == 'r')
			read(*p, id);

		else if(p->getAct() == 'w')
			write(*p, id);

		cv[id-1].push(p);
		p->setStat(3);

	}
	else if(p->getStat() == 4)
	{
		cout << "ERROR: Process was terminated!" << endl;

	}
	else if(p->getStat() == 3)
	{
		cout << "ERROR: Process busy queuing for something else!" << endl;

	}
	else if(p->getStat() != 2)
	{
		cout << "ERROR: Process not running in CPU!" << endl;

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																									 	QUEUE SIZE
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int devControl::pSize()
{
	return pv.size();

}
unsigned int devControl::dSize()
{
	return dv.size();
}
unsigned int devControl::cSize()
{

	return cv.size();
}



bool devControl::pEmpty(unsigned int id)
{


	return pv[id-1].empty();
}

bool devControl::dEmpty(unsigned int id)
{
	return dv[id-1].empty();
}

bool devControl::cEmpty(unsigned int id)
{


	return cv[id-1].empty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																										INTERRUPT
//	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PCB* devControl::pIntrp(string pname)
{
	
	string id = pname.substr(1, pname.length()-1);

	unsigned int id_num = stoui(id);

	PCB* PCB_ptr = pv[id_num-1].intrp();

	//cout << "Process " << process_syn.getID() << " is now " << process_syn.getActString() << endl;

	return PCB_ptr ;

	

}

PCB* devControl::dIntrp(string dname)
{

	string id = dname.substr(1, dname.length()-1);

	unsigned int id_num = stoui(id);

	PCB* PCB_ptr  = dv[id_num-1].intrp();

	return PCB_ptr ;

}

PCB* devControl::cIntrp(string cname)
{

	string id = cname.substr(1, cname.length()-1);

	unsigned int id_num = stoui(id);

	PCB* PCB_ptr  = cv[id_num-1].intrp();

	return PCB_ptr ;
}


list<PCB*>& devControl::getJobPool()
{

	return jobPool;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																							RETURNING ALL QUEUE IDS IN DEVICES
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void devControl::allPrinterQ(vector< vector<PCB*> >& v)
{


	for(unsigned int i = 0; i < pv.size(); i++)
		v.push_back( pv[i].queue_vector() );


}


void devControl::allDiskQ(vector< list<PCB*>* >& v)
{


	for(unsigned int i = 0; i <dv.size(); i++)
		v.push_back( &dv[i].queue_list());



}


void devControl::allCDRWQ(vector< vector<PCB*> >& v)
{

	for(unsigned int i = 0; i <cv.size(); i++)
		v.push_back( cv[i].queue_vector() );

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																							etc
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int devControl::getCurrentCylinder(unsigned int diskNumber)
{
	return dv[diskNumber-1].diskHeadLocation();
	



}

list<PCB*>::iterator* devControl::getHeadPosition(unsigned int diskNumber)
{

	return dv[diskNumber-1].getHeadPosition();

}


















