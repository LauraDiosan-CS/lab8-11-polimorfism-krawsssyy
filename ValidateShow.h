#pragma once
#include "Validator.h"
#include "Show.h"

class ValidatorShow : public Validator {
public:
	void validate(IE* e) throw(MyExc) {
		Show* s = dynamic_cast<Show*>(e);
		if (s == nullptr)
			throw MyExc("The given object is not a show!");
		else {
			std::string date = s->getDate();
			size_t pos = date.find("/");
			if (pos == std::string::npos)
				throw MyExc("The given show has a wrong date format!");
			if (std::stoi(date.substr(0, pos)) < 1 || std::stoi(date.substr(0, pos)) > 31)
				throw MyExc("The given show has a wrong day!");
			date.erase(0, pos + 1);
			pos = date.find("/");
			if (pos == std::string::npos)
				throw MyExc("The given show has a wrong date format!");
			if (std::stoi(date.substr(0, pos)) < 1 || std::stoi(date.substr(0, pos)) > 12)
				throw MyExc("The given show has a wrong month!");
			date.erase(0, pos + 1);
			if (date.length() != 4 || std::stoi(date) < 1900 || std::stoi(date) > 2200)
				throw MyExc("The given show has a wrong year!");
			date = s->getPlace();
			if (date == "")
				throw MyExc("The given show has no place!");
			int avl = s->getAvailablePlaces();
			int occ = s->getOccupiedPlaces();
			if (occ > avl)
				throw MyExc("The given show has more occupied places than available places!");

		}

	}
};