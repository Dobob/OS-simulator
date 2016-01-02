#include <iostream>
#include "../include/system.h"
#include "../include/pcb.h"

using namespace std;



int main()
{

	PCB p;
	cout << "Time: " << p.getTotalExecTime() << endl;
	cout << "Avg.Time: " << p.getAvgCPUBurst() << endl;

	cout << endl;
	p.setTotalExecTime(1);
	p.addTime(1);
	cout << "Time: " << p.getTotalExecTime() << endl;
	cout << "Avg.Time: " << p.getAvgCPUBurst() << endl;

	cout << endl;
	p.updateCPUBurstCount();
	cout << "Time: " << p.getTotalExecTime() << endl;
	cout << "Avg.Time: " << p.getAvgCPUBurst() << endl;

	return 0;



}














