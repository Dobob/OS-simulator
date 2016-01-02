#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "../lib/include/useful.h"
#include "../include/system.h"


using namespace std;




int main()
{
	try
	{
		cout << "IMPORTANT: Process and device IDs start at 1!\n";
		cout << "\t   Cylinders start at 0!\n";
		cout << "\t   Uninitialized processes have PID 0!\n";
		cout << "\t   Used IDs are not recycled!\n\n";

		mySystem sys = mySystem();


		sys.run();

	}


	catch(exception & e)
	{

		cout << e.what() << endl;
	}

	return 0;
}








