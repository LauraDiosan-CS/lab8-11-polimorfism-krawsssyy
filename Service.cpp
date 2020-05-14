#define A 54059 
#define B 76963 
#define C 86969 
#define FIRSTH 37
#include "Service.h"
#include "Artist.h"
#include "Film.h"

void Service::login(std::string uName, std::string passw)
{
	if (this->uName == uName) {
		if (hash(this->passwd.c_str()) == hash(passw.c_str()))
		{
			this->access = 1;
			return;
		}
		else
			throw MyExc("Wrong username or password!");
	}
	else
		throw MyExc("Wrong username or password!");
}

unsigned Service::hash(const char* s)
{
	unsigned h = FIRSTH;
	while (*s) {
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h % C;
}
void Service::addArtistShow(char* name, std::string date, std::string place, int availablePlaces, int occupiedPlaces)
{
	if (this->access == 1) {
		Show s(date, place, availablePlaces, occupiedPlaces);
		showVal->validate(&s);
		IE* artist = new Artist(name, s);
		artistVal->validate(artist);
		this->r->addElem(artist);
	}
	else
		throw MyExc("Access denied!");
	
}

void Service::addArtistShows(char* name, std::vector<Show> shows)
{
	if (this->access == 1) {
		for (Show& s : shows)
			showVal->validate(&s);
		IE* artist = new Artist(name, shows);
		artistVal->validate(artist);
		this->r->addElem(artist);
	}
	else
		throw MyExc("Access denied!");

}

void Service::addFilmShow(char* title, std::vector<std::string> actors, std::string date, std::string place, int availablePlaces, int occupiedPlaces)
{
	if (this->access == 1) {
		Show s(date, place, availablePlaces, occupiedPlaces);
		showVal->validate(&s);
		IE* film = new Film(title, actors, s);
		filmVal->validate(film);
		this->r->addElem(film);
	}
	else
		throw MyExc("Access denied!");

}

void Service::addFilmShows(char* title, std::vector<std::string> actors, std::vector<Show> shows)
{
	if (this->access == 1) {
		for (Show& s : shows)
			showVal->validate(&s);
		IE* film = new Film(title, actors, shows);
		filmVal->validate(film);
		this->r->addElem(film);
	}
	else
		throw MyExc("Access denied!");
}

IE* Service::getArtistByName(char* name)
{
	if (this->access == 1) {
		std::vector<IE*> result = this->r->getAll();
		for(IE* e : result)
			if (dynamic_cast<Artist*>(e) != nullptr)
				if (strcmp(dynamic_cast<Artist*>(e)->getName(), name) == 0)
					return dynamic_cast<Artist*>(e)->clone();
		return nullptr;
	}
	else
	throw MyExc("Access denied!");
}

IE* Service::getFilmByTitle(char* title)
{
	if (this->access == 1) {
		std::vector<IE*> result = this->r->getAll();
		for (IE* e : result)
			if (dynamic_cast<Film*>(e) != nullptr)
				if (strcmp(dynamic_cast<Film*>(e)->getTitle(), title) == 0)
					return dynamic_cast<Film*>(e)->clone();
		return nullptr;
	}
	else
		throw MyExc("Access denied!");

}


void Service::modifyArtist(char* name, char* newName, std::vector<Show> shows)
{
	if (this->access == 1) {
		IE* result = this->getArtistByName(name);
		if (result == nullptr){
			delete result;
			result = nullptr;
			return;
		}
		for (Show& s : shows)
			showVal->validate(&s);
		IE* artist = new Artist(newName, shows);
		artistVal->validate(artist);
		this->r->modifyElem(result, artist);
	}
	else
		throw MyExc("Access denied!");
}

void Service::modifyFilm(char* title, char* newTitle, std::vector<std::string> actors, std::vector<Show> shows)
{
	if (this->access == 1) {
		IE* result = this->getArtistByName(title);
		if (result == nullptr) {
			delete result;
			result = nullptr;
			return;
		}
		for (Show& s : shows)
			showVal->validate(&s);
		IE* film = new Film(newTitle, actors, shows);
		filmVal->validate(film);
		this->r->modifyElem(result, film);
	}
	else
		throw MyExc("Access denied!");

}

void Service::deleteElem(IE* e)
{
	if (this->access == 1) 
		this->r->deleteElem(e);
	else
		throw MyExc("Access denied!");
}

std::vector<IE*> Service::getAll()
{
	return this->r->getAll();
}
