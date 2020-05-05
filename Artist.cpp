#include "Artist.h"

Artist::Artist() {
	this->name = nullptr;
	this->shows.reserve(100);
}

Artist::Artist(char* name, std::string date, std::string place, int availablePlaces, int occupiedPlaces) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	Show s(date, place, availablePlaces, occupiedPlaces);
	shows.emplace_back(s);
}

Artist::Artist(char* name, std::vector<Show> shows) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	std::copy(shows.begin(), shows.end(), back_inserter(this->shows));
}

Artist::Artist(const Artist& a) {
	this->name = new char[strlen(a.name) + 1];
	strcpy_s(this->name, strlen(a.name) + 1, a.name);
	std::copy(a.shows.begin(), a.shows.end(), back_inserter(this->shows));
}

Artist::~Artist() {
	if (this->name)
		delete[] this->name, this->name = nullptr;
	this->shows.clear();
}

char* Artist::getName()
{
	return this->name;
}
 
void Artist::setName(char* name) {
	if (this->name)
		delete[] this->name, this->name = nullptr;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

std::vector<Show> Artist::getShows() {
	return this->shows;
}

void Artist::setShows(std::vector<Show> shows) {
	this->shows.clear();
	std::copy(shows.begin(), shows.end(), back_inserter(this->shows));
}

Artist& Artist::operator=(const Artist& a) {
    this->setName(a.name);
	std::copy(a.shows.begin(), a.shows.end(), back_inserter(this->shows));
	return *this;
}

bool Artist::operator==(const Artist& a) const {
	bool ok = true;
	std::vector<Show> showz;
	std::copy(a.shows.begin(), a.shows.end(), back_inserter(showz));
	for (Show& s : showz)
		if (std::find(this->shows.begin(), this->shows.end(), s) == this->shows.end())
			ok = false;
	showz.clear();
	if (ok)
		return !strcmp(this->name, a.name);
	else
		return false;
}

IE* Artist::clone() {
	return new Artist(this->name, this->shows);
}

void Artist::copy(IE* e) {
	Artist* a = (Artist*)e;
	this->setName(a->name);
	std::copy(a->shows.begin(), a->shows.end(), back_inserter(this->shows));
}

bool Artist::equals(IE* e) {
	Artist* a = (Artist*)e;
	bool ok = true;
	std::vector<Show> showz;
	std::copy(a->shows.begin(), a->shows.end(), back_inserter(showz));
	for (Show& s : showz)
		if (std::find(this->shows.begin(), this->shows.end(), s) == this->shows.end())
			ok = false;
	if (ok)
		return !strcmp(this->name, a->name);
	else
		return false;
}

std::string Artist::toStringCSV() {
	std::string toShow;
	toShow = (std::string)"Artist" + ',' + this->name + ',';
	for (Show& s : this->shows) {
		toShow += s.toStringCSV();
		toShow += ',';
	}
	toShow.pop_back();
	return toShow;
}

std::string Artist::toStringTXT() {
	std::string toShow;
	toShow = (std::string)"Artist" + '\n' + this->name + '\n';
	for (Show& s : this->shows) {
		toShow += s.toStringTXT();
		toShow += '\n';
	}
	return toShow;
}