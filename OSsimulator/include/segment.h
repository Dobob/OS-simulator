#ifndef MY_SEGMENT_H
#define MY_SEGMENT_H


#include <iostream>
#include <string>
#include "system.h"
#include "../lib/include/useful.h"


class Segment
{
	private:	

	bool valid_ = false;
	bool hole_ = true;

	unsigned int pid_;
	unsigned int base_;
	unsigned int limit_;

	public:
	Segment();
	Segment(const Segment& s);
	Segment(Segment&& s);

	Segment(unsigned int b, unsigned int l);
	Segment(unsigned int pid, unsigned int b, unsigned int l);
	//Segment(PCB p, unsigned int b, unsigned int l);

	unsigned int base();
	unsigned int limit();
	unsigned int pid();

	bool isHole() const;


	void fill();
	void free();
	void setBase(unsigned int b);
	void setLimit(unsigned int l);
	Segment merge(Segment s);

	Segment& operator=(const Segment& s);
	Segment& operator=(Segment&& s);


	//friend class mySystem;
	friend ostream& operator<<(ostream& out_stream, const Segment& s);

};


#include "../src/segment.cpp"


#endif
