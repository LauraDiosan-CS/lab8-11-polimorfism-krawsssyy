#pragma once
#include "MyException.h"
#include "IE.h"

class Validator {
public:
	virtual void validate(IE* e) throw(MyExc) = 0;
};