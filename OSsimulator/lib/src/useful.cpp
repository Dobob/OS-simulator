
#include <string>
#include "../include/useful.h"

bool isNumber(const string& target)
{

	char c;

	for(unsigned int i =0; i<target.length(); i++)
	{
		c = target[i];

		if(c < 48 || c > 57 )
			return false;


	}

	
	return true;

}

bool isNumber(const char& target)
{
	bool cond = true;

	if(target < 48 || target > 57 )
		cond = false;




	return cond;


}


bool isNegative(const string& target)
{
	if(target[0] == '-')
	{

		return true;


	}
	return false;


}

unsigned int stoui(const string& str)
{
	unsigned int val = 0;

	for(unsigned int i = 0; i< str.length(); i++)
	{
		val = val * 10;

		switch(str[i])
		{
			case '1': val = val + 1; break;

			case '2': val = val + 2; break;

			case '3': val = val + 3; break;

			case '4': val = val + 4; break;

			case '5': val = val + 5; break;

			case '6': val = val + 6; break;

			case '7': val = val + 7; break;

			case '8': val = val + 8; break;

			case '9': val = val + 9; break;


		}

	}

	return val;

}

unsigned int stoui(const char& ch)
{
	unsigned int val = 0;

	switch(ch)
	{
		case '1': return 1;

		case '2': return 2;

		case '3': return 3;

		case '4': return 4; 

		case '5': return 5; 

		case '6': return 6;

		case '7': return 7; 

		case '8': return 8;

		case '9': return 9; 


	}


	return val;

}
string reverseStr(string str)
{
	string rev_str(str.length(), '0');

	for(unsigned int i = 1; i <= str.length(); i++)
	{

		rev_str[str.length() - i] = str[i-1];

	}

	return rev_str;

}

string uitos(const unsigned int& ui)
{
	string str;
	unsigned int cur_value = ui;
	unsigned int cur_digit;


	while(cur_value != 0)
	{
		cur_digit = cur_value%10;
		cur_value = cur_value/10;
		//cout << "cur_digit: " << cur_digit << endl; 
		//cout << "cur_value: " << cur_value << endl; 
		switch(cur_digit)
		{
			case 1: str = str + "1"; break;

			case 2: str = str + "2"; break;

			case 3: str = str + "3"; break;

			case 4: str = str + "4"; break;

			case 5: str = str + "5"; break;

			case 6: str = str + "6"; break;

			case 7: str = str + "7"; break;

			case 8: str = str + "8"; break;

			case 9: str = str + "9"; break;


		}

	}

	return reverseStr(str);

}



template<typename type, unsigned int N>
size_t sizeArray(type (&a)[N])
{

	return N;

}


bool detectedSpace(string s)
{

	for(unsigned int i=0; i<s.length(); i++)
	{
		if(s[i] == ' ')
			return true;

	}

	return false;
}












