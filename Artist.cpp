#include "Artist.h"

Artist::Artist() {
	this->name = nullptr;
	this->shows.reserve(100);
}

Artist::Artist(char* name, std::string date, std::string place, int availablePlaces, int occupiedPlaces) {
	if (name) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}
	else
		this->name = nullptr;
	Show s(date, place, availablePlaces, occupiedPlaces);
	shows.emplace_back(s);
}

Artist::Artist(char* name, std::vector<Show> shows) {
	if (name) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}
	else
		this->name = nullptr;
	std::copy(shows.begin(), shows.end(), back_inserter(this->shows));
}

Artist::Artist(const Artist& a) {
	if (a.name) {
		this->name = new char[strlen(a.name) + 1];
		strcpy_s(this->name, strlen(a.name) + 1, a.name);
	}
	else
		this->name = nullptr;
	std::copy(a.shows.begin(), a.shows.end(), back_inserter(this->shows));
}

Artist::~Artist() {
	if (this->name)
	{
		delete[] this->name;
		this->name = nullptr;
	}
	this->shows.clear();
}

char* Artist::getName()
{
	return this->name;
}
 
void Artist::setName(char* name) {
	if (name) {
		if (this->name)
		{
			delete[] this->name;
			this->name = nullptr;
		}
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}
	else
		this->name = nullptr;
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
	this->setShows(a.shows);
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
		if ((!this->name && a.name) || (this->name && !a.name))
			return false;
		else if (!this->name && !a.name)
			return true;
		else
			return !strcmp(this->name, a.name);
	else
		return false;
}

IE* Artist::clone() {
	return new Artist(this->name, this->shows);
}

void Artist::copy(IE* e) {
	Artist* a = dynamic_cast<Artist*>(e);
	if (a == nullptr)
		return;
	this->setName(a->name);
	this->setShows(a->shows);
}

bool Artist::equals(IE* e) {
	Artist* a = dynamic_cast<Artist*>(e);
	if (a == nullptr)
		return false;
	return this->operator==(*a);
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