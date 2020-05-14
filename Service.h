#pragma once
#include "Repo.h"
#include "Validator.h"
#include "Show.h"



class Service {
private:
	Repo* r;
	Validator* showVal;
	Validator* artistVal;
	Validator* filmVal;
	std::string uName = "admin";
	std::string passwd = "\x41\x42\x42\x41";
	unsigned hash(const char* s);
	int access = 0;
	
public:
	Service(Repo* repo, Validator* sV, Validator* aV, Validator* fV) : r(repo), showVal(sV), artistVal(aV), filmVal(fV) {}
	~Service() {}
	void login(std::string uName, std::string passw);
	void addArtistShow(char* name, std::string date, std::string place, int availablePlaces, int occupiedPlaces);
	void addArtistShows(char* name, std::vector<Show> shows);
	void addFilmShow(char* title, std::vector<std::string> actors, std::string date, std::string place, int availablePlaces, int occupiedPlaces);
	void addFilmShows(char* title, std::vector<std::string> actors, std::vector<Show> shows);
	IE* getArtistByName(char* name);
	IE* getFilmByTitle(char* title);
	void modifyArtist(char* name, char* newName, std::vector<Show> shows);
	void modifyFilm(char* title, char* newTitle, std::vector<std::string> actors, std::vector<Show> shows);
	void deleteElem(IE* e);
	std::vector<IE*> getAll();
};