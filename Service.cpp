#define A 54059 
#define B 76963 
#define C 86969 
#define FIRSTH 37
#include "Service.h"
#include "Artist.h"
#include "Film.h"
#include "RepoFileTXT.h"
#include "RepoFileCSV.h"

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
			throw MyExc("Artist not found!");
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
		IE* result = this->getFilmByTitle(title);
		if (result == nullptr) {
			delete result;
			result = nullptr;
			throw MyExc("Film not found!");
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

void Service::deleteElem(char* arg)
{
	if (this->access == 1) {
		if (this->getArtistByName(arg) != nullptr)
			this->r->deleteElem(this->getArtistByName(arg));
		else if (this->getFilmByTitle(arg) != nullptr)
			this->r->deleteElem(this->getFilmByTitle(arg));
		else
			throw MyExc("Element not found!");
	}
	else
		throw MyExc("Access denied!");
}

std::vector<IE*> Service::getAll()
{
	if (this->access == 1) 
		return this->r->getAll();
	else
		throw MyExc("Access denied!");
}

std::string Service::getRepoType() {
	if (this->access == 1) {
		if (dynamic_cast<RepoFileTXT*>(this->r) != nullptr)
			return "TXT";
		else if (dynamic_cast<RepoFileCSV*>(this->r) != nullptr)
			return "CSV";
		else
			throw MyExc("Unknown repository!");
	}
	else
		throw MyExc("Access denied!");
}

void Service::revertAccess() {
	if (this->access == 1)
		this->access = 0;
	else
		throw MyExc("You weren't able to logout since you haven't even logged in !");
}

std::vector<IE*> Service::givenDate(std::string date) {
	if (this->access == 1) {
		std::vector<IE*> all = this->getAll();
		std::vector<IE*> result;
		for (IE* e : all) {
			if (dynamic_cast<Artist*>(e) != nullptr) {
				for (Show& s : dynamic_cast<Artist*>(e)->getShows())
					if (s.getDate() == date)
					{
						result.emplace_back(e->clone());
						break;
					}
			}
			if (dynamic_cast<Film*>(e) != nullptr) {
				for (Show& s : dynamic_cast<Film*>(e)->getShows())
					if (s.getDate() == date)
					{
						result.emplace_back(e->clone());
						break;
					}
			}
		}
		return result;
	}
	else
		throw MyExc("Access denied!");
}

bool Service::buyTickets(std::string date, std::string place, int amount) {
	if (this->access == 1) {
		std::vector<IE*> all = this->getAll();
		bool ok = 0;
		for (IE* e : all) {
			if (dynamic_cast<Artist*>(e) != nullptr) {
				std::vector<Show> shows = dynamic_cast<Artist*>(e)->getShows();
				for (int i = 0; i < shows.size(); i++)
					if (shows[i].getDate() == date && shows[i].getPlace() == place)
					{
						if (shows[i].getOccupiedPlaces() + amount > shows[i].getAvailablePlaces())
							throw MyExc("You can't buy this many tickets!");
						else
						{
							int occ = shows[i].getOccupiedPlaces();
							shows[i].setOccupiedPlaces(occ + amount);
							this->modifyArtist(dynamic_cast<Artist*>(e)->getName(), dynamic_cast<Artist*>(e)->getName(), shows);
							ok = 1;
							break;
						}
					}
			}
			if (ok)
				break;
			if (dynamic_cast<Film*>(e) != nullptr) {
				std::vector<Show> shows = dynamic_cast<Film*>(e)->getShows();
				for (int i = 0; i < shows.size(); i++)
					if (shows[i].getDate() == date && shows[i].getPlace() == place)
					{
						if (shows[i].getOccupiedPlaces() + amount > shows[i].getAvailablePlaces())
							throw MyExc("You can't buy this many tickets!");
						else
						{
							int occ = shows[i].getOccupiedPlaces();
							shows[i].setOccupiedPlaces(occ + amount);
							this->modifyFilm(dynamic_cast<Film*>(e)->getTitle(), dynamic_cast<Film*>(e)->getTitle(), dynamic_cast<Film*>(e)->getActors(), shows);
							ok = 1;
							break;
						}
					}
			}
		}
		return ok;
	}
	else
		throw MyExc("Access denied!");
}