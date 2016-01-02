#include "../include/segment.h"
Segment::Segment()
{

	valid_ = false;
	pid_= 0;
	base_ = 0;
	limit_ = 0; 

}

Segment::Segment(const Segment& s)
{
	
	valid_ = s.valid_;
	pid_ = s.pid_;
	base_ = s.base_;
	limit_ = s.limit_; 
	hole_ = s.hole_;

}

Segment::Segment(Segment&& s)
{

	valid_ = std::move(s.valid_);
	pid_ = std::move(s.pid_);
	base_ = std::move(s.base_);
	limit_ = std::move(s.limit_); 
	hole_ = std::move(s.hole_);

}
Segment::Segment(unsigned int b, unsigned int l)
{
	base_ = b;
	limit_ = l;

}
	
Segment::Segment(unsigned int pid, unsigned int b, unsigned int l)
{
	pid_ = pid;
	base_ = b;
	limit_ = l;



}
/*
Segment::Segment(PCB p, unsigned int b, unsigned int l)
{	
	process = p;
	pid_ = p.getID();
	base_ = b;
	limit_ = l;

}
*/
unsigned int Segment::base()
{

	return base_;

}

unsigned int Segment::limit()
{


	return limit_;

}
unsigned int Segment::pid()
{
	return pid_;
}
void Segment::setBase(unsigned int b)
{

	base_ = b;

}


void Segment::setLimit(unsigned int l)
{

	limit_ = l;


}
void Segment::fill()
{

	hole_ = false;

}
void Segment::free()
{
	pid_ = 0;
	hole_ = true;
}

bool Segment::isHole() const
{

	return hole_;

}
Segment Segment::merge(Segment s)
{
	//if *this == s, then s is returned.
	Segment retSeg = s;
	//cout << "s : " << s << endl;
	if(base_ < s.base_)
		retSeg.setBase(base_);

	else if(base_  > s.base_)
		retSeg.setBase(s.base_);

	if(limit_ < s.limit_)
		retSeg.setLimit(s.limit_);	

	else if(limit_ > s.limit_)
		retSeg.setLimit(limit_ );


	//limit is now the sum of the limits of two segments

	retSeg.setLimit(limit_ + s.limit());
	//cout << "IN MERGE FUNC: " << *this << endl;

	return retSeg;



}

Segment& Segment::operator=(const Segment& s)
{
	valid_ = s.valid_;
	pid_ = s.pid_;
	base_ = s.base_;
	limit_ = s.limit_;
	hole_ = s.hole_;
	return *this;

}
Segment& Segment::operator=(Segment&& s)
{
	valid_ = std::move(s.valid_);
	pid_ = std::move(s.pid_);
	base_ = std::move(s.base_);
	limit_ = std::move(s.limit_);
	hole_ = std::move(s.hole_);
	return *this;
}


ostream& operator<<(ostream& out_stream, const Segment& s)
{

	out_stream << '<' << s.base_ << ", " << s.limit_ << '>';

	return out_stream;
}





















