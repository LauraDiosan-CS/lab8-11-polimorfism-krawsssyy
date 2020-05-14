#pragma once
#include "Film.h"
#include "Validator.h"

class ValidatorFilm : public Validator {
public:
	void validate(IE* e) throw(MyExc) {
		Film* f = dynamic_cast<Film*>(e);
		if (f == nullptr)
			throw MyExc("The given object is not a film!");
		else
		{
			char* title = f->getTitle();
			if (title == nullptr)
				throw MyExc("The given film has a null title!");
			std::vector<std::string> actorz = f->getActors();
			if (actorz.size() == 0)
				throw MyExc("The given film has no actors!");
			for(std::string& s : actorz)
				if (s == "")
				{
					break;
					throw MyExc("The given film has one or more actors with null names!");
				}

		}
	}
};