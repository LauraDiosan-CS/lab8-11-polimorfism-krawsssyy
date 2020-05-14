#pragma once
#include "Artist.h"
#include "Validator.h"

class ValidatorArtist : public Validator {
public :
	void validate(IE* e) throw(MyExc) {
		Artist* a = dynamic_cast<Artist*>(e);
		if (a == nullptr)
			throw MyExc("The given object is not an artist!");
		else {
			char* name = a->getName();
			if (name = nullptr)
				throw MyExc("The given artist has a null name!");
		}
	}
};