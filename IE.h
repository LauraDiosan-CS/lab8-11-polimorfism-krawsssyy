#pragma once
#include <string>

class IE {
public:
	virtual IE* clone() = 0;
	virtual void copy(IE*) = 0;
	virtual bool equals(IE*) = 0;
	virtual std::string toStringCSV() = 0;
	virtual std::string toStringTXT() = 0;
	virtual ~IE() {};
};