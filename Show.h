#pragma once
#include "IE.h"
class Show : public IE {
private:
	std::string date;
	std::string place;
	int availablePlaces;
	int occupiedPlaces;
public:
	Show() {
		this->date = "";
		this->place = "";
		this->availablePlaces = 0;
		this->occupiedPlaces = 0;
	}
	Show(std::string date, std::string place, int availablePlaces, int occupiedPlaces) {
		this->date = date;
		this->place = place;
		this->availablePlaces = availablePlaces;
		this->occupiedPlaces = occupiedPlaces;
	}
	Show(const Show& s) {
		this->date = s.date;
		this->place = s.place;
		this->availablePlaces = s.availablePlaces;
		this->occupiedPlaces = s.occupiedPlaces;
	}
	~Show() {
	}
	Show& operator=(const Show& s) {
		this->date = s.date;
		this->place = s.place;
		this->availablePlaces = s.availablePlaces;
		this->occupiedPlaces = s.occupiedPlaces;
		return *this;
	}
	bool operator==(const Show& s) const {
		return (this->date == s.date) && (this->place == s.place) && (this->availablePlaces == s.availablePlaces) && 
			(this->occupiedPlaces == s.occupiedPlaces);
	}
	std::string getDate() {
		return this->date;
	}
	std::string getPlace() {
		return this->place;
	}
	int getAvailablePlaces() {
		return this->availablePlaces;
	}
	int getOccupiedPlaces() {
		return this->occupiedPlaces;
	}
	void setDate(std::string date) {
		this->date = date;
	}
	void setPlace(std::string place) {
		this->place = place;
	}
	void setAvaiablePlaces(int availablePlaces) {
		this->availablePlaces = availablePlaces;
	}
	void setOccupiedPlaces(int occupiedPlaces) {
		this->occupiedPlaces = occupiedPlaces;
	}
	void copy(IE* e) {
		Show* s = (Show*)e;
		this->date = s->date;
		this->place = s->place;
		this->availablePlaces = s->availablePlaces;
		this->occupiedPlaces = s->occupiedPlaces;
	}
	IE* clone() {
		return new Show(this->date, this->place, this->availablePlaces, this->occupiedPlaces);
	}
	bool equals(IE* e) {
		return this->date == ((Show*)e)->date && this->place == ((Show*)e)->place && this->availablePlaces == ((Show*)e)->availablePlaces && this->occupiedPlaces == ((Show*)e)->occupiedPlaces;
	}
	std::string toStringTXT() {
		std::string toShow;
		toShow = this->date + ',' + this->place + ',' + std::to_string(this->availablePlaces) + ',' + std::to_string(this->occupiedPlaces);
		return toShow;
	}
	std::string toStringCSV() {
		std::string toShow;
		toShow = this->date + ' ' + this->place + ' ' + std::to_string(this->availablePlaces) + ' ' + std::to_string(this->occupiedPlaces);
		return toShow;
	}
};