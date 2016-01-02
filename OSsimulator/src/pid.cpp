
#include "../include/pid.h"

PID::PID(): inactive{true}
{

}

PID::PID(const PID& id): id_{id.id_}
{


}

PID::PID(unsigned int id): id_{id}
{


}

bool PID::operator==(const PID & id) const	
{
	return (id_ == id.getID());


}
unsigned int PID::getID() const
{

	return id_;

}

void PID::generate()
{
	id_ = next_PID;
	next_PID++;
}

void PID::print()
{
	cout << "next_PID: " << next_PID << endl;

	cout << "id_: " << id_ << endl;
}

PID& PID::operator=(const PID & id)
{

	id_ = id.id_;

	return *this;
}

ostream& operator<<(ostream& out_stream, const PID& id)
{

	out_stream << id.getID();

	return out_stream;
}
