#include "Film.h"

Film::Film() {
	this->title = nullptr;
	this->shows.reserve(100);
	this->actors.reserve(100);
}

Film::Film(char* title, std::vector<std::string> actors, std::string date, std::string place, int availablePlaces, int occupiedPlaces) {
	if (title)
	{
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
	else
		this->title = nullptr;
	std::copy(actors.begin(), actors.end(), back_inserter(this->actors));
	Show s(date, place, availablePlaces, occupiedPlaces);
	this->shows.emplace_back(s);
}

Film::Film(char* title, std::vector<std::string> actors, const Show& s) {
	if (title)
	{
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
	else
		this->title = nullptr;
	std::copy(actors.begin(), actors.end(), back_inserter(this->actors));
	this->shows.emplace_back(s);
}

Film::Film(char* title, std::vector<std::string> actors, std::vector<Show> shows) {
	if (title)
	{
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
	else
		this->title = nullptr;
	std::copy(actors.begin(), actors.end(), back_inserter(this->actors));
	std::copy(shows.begin(), shows.end(), back_inserter(this->shows));
}

Film::Film(const Film& f) {
	if (f.title)
	{
		this->title = new char[strlen(f.title) + 1];
		strcpy_s(this->title, strlen(f.title) + 1, f.title);
	}
	else
		this->title = nullptr;
	std::copy(f.actors.begin(), f.actors.end(), back_inserter(this->actors));
	std::copy(f.shows.begin(), f.shows.end(), back_inserter(this->shows));
}

Film::~Film() {
	if (this->title)
	{
		delete[] this->title;
		this->title = nullptr;
	}
	this->actors.clear();
	this->shows.clear();
}

char* Film::getTitle() {
	return this->title;
}

void Film::setTitle(char* title) {
	if (title)
	{
		if (this->title)
		{
			delete[] this->title;
			this->title = nullptr;
		}
		this->title = new char[strlen(title) + 1];
		strcpy_s(this->title, strlen(title) + 1, title);
	}
	else
		this->title = nullptr;
	
}

std::vector<std::string> Film::getActors() {
	return this->actors;
}

void Film::setActors(std::vector<std::string> actors) {
	this->actors.clear();
	std::copy(actors.begin(), actors.end(), back_inserter(this->actors));
}

std::vector<Show> Film::getShows() {
	return this->shows;
}

void Film::setShows(std::vector<Show> shows) {
	this->shows.clear();
	std::copy(shows.begin(), shows.end(), back_inserter(this->shows));
}


Film& Film::operator=(const Film& f) {
	this->setTitle(f.title);
	this->setActors(f.actors);
	this->setShows(f.shows);
	return *this;
}

bool Film::operator==(const Film& f) const {
	std::vector<Show> showz;
	std::vector<std::string> actorz;
	bool ok = true;
	std::copy(f.shows.begin(), f.shows.end(), back_inserter(showz));
	std::copy(f.actors.begin(), f.actors.end(), back_inserter(actorz));
	for (std::string& s : actorz)
		if (std::find(this->actors.begin(), this->actors.end(), s) == this->actors.end())
			ok = false;
	for (Show& s : showz)
		if (std::find(this->shows.begin(), this->shows.end(), s) == this->shows.end())
			ok = false;
	showz.clear();
	actorz.clear();
	if (ok)
		if ((!this->title && f.title) || (this->title && !f.title))
			return false;
		else if (!this->title && !f.title)
			return true;
		else
			return !strcmp(this->title, f.title);
	else
		return false;
}

IE* Film::clone() {
	return new Film(this->title, this->actors, this->shows);
}

void Film::copy(IE* e) {
	Film* f = dynamic_cast<Film*>(e);
	if (f == nullptr)
		return;
	this->setTitle(f->title);
	this->setActors(f->actors);
	this->setShows(f->shows);
}

bool Film::equals(IE* e) {
	Film* f = dynamic_cast<Film*>(e);
	if (f == nullptr)
		return false;
	return this->operator==(*f);
	
}

std::string Film::toStringCSV() {
	std::string toShow;
	toShow = (std::string)"Film" + ',' + title + ',' + std::to_string(this->actors.size()) + ',';
	for (std::string& s : this->actors)
		toShow += (s + ',');
	for (Show& s : this->shows)
		toShow += (s.toStringCSV() + ',');
	toShow.pop_back();
	return toShow;
}

std::string Film::toStringTXT() {
	std::string toShow;
	toShow = (std::string)"Film" + '\n' + title + '\n' + (std::string)"Actori : \n";
	for (std::string& s : this->actors)
		toShow += (s + '\n');
	toShow += ((std::string)"Spectacole : \n");
	for (Show& s : this->shows)
		toShow += (s.toStringTXT() + '\n');
	return toShow;
}