#ifndef PID_H
#define PID_H


#include <iostream>


using namespace std;

/*
65 - 90 A-Z

97 - 122 a-z
*/

class PID
{
	private:

		static unsigned int next_PID;
		bool inactive;


		unsigned int id_ = 0;
		

	public:


		PID();
		PID(const PID& id);
		PID(unsigned int id);

		bool operator==(const PID & id) const;
	
		PID& operator=(const PID & id);	

		unsigned int getID() const;

		void generate();

		void print();
		friend ostream& operator<<(ostream& out_stream, const PID& id);

};




#include "../src/pid.cpp"

#endif
