#pragma once
#include "Show.h"
#include <vector>
class Film : public IE {
private:
	char* title;
	std::vector<Show> shows;
	std::vector<std::string> actors;
public:
	Film();
	Film(char* title, std::vector<std::string> actors, std::string date, std::string place, int availablePlaces, int occupiedPlaces);
	Film(char* title, std::vector<std::string> actors, std::vector<Show> shows);
	Film(const Film& f);
	~Film();
	char* getTitle();
	void setTitle(char* name);
	std::vector<std::string> getActors();
	void setActors(std::vector<std::string> actors);
	std::vector<Show> getShows();
	void setShows(std::vector<Show> shows);
	Film& operator=(const Film& f);
	bool operator==(const Film& f) const;
	IE* clone();
	void copy(IE* e);
	bool equals(IE* e);
	std::string toStringCSV();
	std::string toStringTXT();

};

