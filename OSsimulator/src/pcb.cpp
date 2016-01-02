#include "../include/pcb.h"

PCB::PCB(): fileLen{0}
{
	s = JOB_POOL;
	act = IDLE;
}

PCB::PCB(const PCB& p) : id_{p.id_}
{
	limitsTable = p.limitsTable;
	segTable = p.segTable;
	id_ = p.id_;
	s = p.s;
	act = p.act;
	totalExecTime = p.totalExecTime;
	cylinder = p.cylinder;
	avgCPUBurst = p.avgCPUBurst;
	CPUBurstCount = p.CPUBurstCount;

	if(act != IDLE)
	{
		physicalMemLoca = p.physicalMemLoca;
		file = p.file;
		fileLen = p.fileLen;
	}

}
PCB::PCB(PCB&& p)
{
	limitsTable = std::move(p.limitsTable);
	segTable = std::move(p.segTable);
	id_ = std::move(p.id_);
	s = std::move(p.s);
	act = std::move(p.act);
	totalExecTime = std::move(p.totalExecTime);
	cylinder = std::move(p.cylinder);
	avgCPUBurst = std::move(p.avgCPUBurst);
	CPUBurstCount = std::move(p.CPUBurstCount);
	if(act != IDLE)
	{
		physicalMemLoca = std::move(p.physicalMemLoca);
		file = std::move(p.file);
		fileLen = std::move(p.fileLen);
	}

}
PCB::PCB(unsigned int stat)
{
	status stat_copy = (status) stat;

	s = stat_copy;

}

PCB::~PCB()
{

	segTable.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																														GET
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int PCB::getID() const
{
	return id_.getID();

}

unsigned int PCB::getStat() const
{
	return s;

}
unsigned int PCB::getCylinder() const
{
	//OPTIONAL: error check whether current process intends R/W to disk
	//if not, then return string or int, which allows for error checking.

	return cylinder;

}
char PCB::getAct()
{
	if(act == 1)
	{
		return 'r';

	}
	else if(act == 2)
	{
		return 'w';

	}

	return 'i';

}
string PCB::getActString()
{
	if(act == 1)
	{
		return "reading";

	}
	else if(act == 2)
	{
		return "writing";

	}

	return "idle";

}
string PCB::getFile()
{

	//cout << "file name: " << file << endl;
	return file;

}


unsigned int PCB::getFileLen()
{

	//cout << "filelen: " << fileLen << endl;
	return fileLen;


}
unsigned int PCB::getTotalExecTime()
{
	return totalExecTime;

}

double PCB::getAvgCPUBurst()
{

	return avgCPUBurst;
}
unsigned int PCB::size() const
{
	return size_;


}

vector<Segment*>& PCB::getSegTable()
{
	return segTable;

}

void PCB::printSegTable()
{
	cout << "segTable size: " << segTable.size() << endl;

	for(unsigned int i=0; i<segTable.size(); i++)
	{
		cout << *(segTable[i]) << endl;

	}

}

unsigned int PCB::getMem()
{

	return physicalMemLoca;

}
vector<unsigned int>*  PCB::getLimitsTable()
{
	return (&limitsTable);

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																														SET
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PCB::setPID()
{

	id_.generate();

	
}
void PCB::setStat(unsigned int stat)
{
	s = (status) stat;

}
/*
void PCB::setAct(char c)
{

	if(c == 'r' || c == 'R')
		act = READ;

	else if(c == 'w' || c == 'W')
		act = WRITE;
}
*/
void PCB::setAct(unsigned int a)
{

	//cout << "BEFORE act: " << act << endl;
	act = (action) a;
	//cout << "AFTER act: " << act << endl;

	if(a == 0)
	{
		file = "";
		fileLen = 0;

	}
	else if(a == 1)
	{
		fileLen = 0;
	}

}

void PCB::setFile(string f)
{


	file = f;
	//cout << "file name: " << file << endl;

}

void PCB::setFileLen(unsigned int fl)
{


	fileLen = fl;
	//cout << "fileLen: " << fileLen << endl;
}
void PCB::setTotalExecTime(unsigned int t)
{

	totalExecTime = t;
	//cout << "setting execTime: " << totalExecTime << endl;

}
void PCB::addTime(unsigned int t)
{

	totalExecTime += t;
	//cout << "setting execTime: " << totalExecTime << endl;

}

void PCB::updateAvgCPUBurst()
{
	double execTime = totalExecTime;
	double burstCount = CPUBurstCount;
	avgCPUBurst = execTime / burstCount;

}


void PCB::updateCPUBurstCount()
{
	CPUBurstCount++;

	updateAvgCPUBurst();

}
void PCB::setCylinder(unsigned int c)
{

	cylinder = c;

}

void PCB::setSize(unsigned int s)
{
	size_ = s;

}

void PCB::insertSegTable(Segment*& s)
{

	segTable.push_back(s);



}
void PCB::setMem(unsigned int mem)
{

	physicalMemLoca = mem;



}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 																										OPERATORS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PCB& PCB::operator=(const PCB& p)
{
	limitsTable = p.limitsTable;
	segTable = p.segTable;
	id_ = p.id_;
	s = p.s;
	act = p.act;
	totalExecTime = p.totalExecTime;
	cylinder = p.cylinder;
	avgCPUBurst = p.avgCPUBurst;
	CPUBurstCount = p.CPUBurstCount;
	if(act != IDLE)
	{
		physicalMemLoca = p.physicalMemLoca;
		file = p.file;
		fileLen = p.fileLen;
	}

	return *this;
}

PCB& PCB::operator=(PCB&& p)
{
	limitsTable = std::move(p.limitsTable);
	segTable = std::move(p.segTable);
	id_ = std::move(p.id_);
	s = std::move(p.s);
	act = std::move(p.act);
	totalExecTime = std::move(p.totalExecTime);
	cylinder = std::move(p.cylinder);
	avgCPUBurst = std::move(p.avgCPUBurst);
	CPUBurstCount = std::move(p.CPUBurstCount);
	if(act != IDLE)
	{
		physicalMemLoca = std::move(p.physicalMemLoca);
		file = std::move(p.file);
		fileLen = std::move(p.fileLen);
	}

	return *this;
}



ostream& operator<<(ostream& out_stream, const PCB& p)
{

	out_stream << "P" << p.getID();

	return out_stream;
}













