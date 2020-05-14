#pragma once
#include "Show.h"
#include <vector>
class Artist : public IE {
private:
	char* name;
	std::vector<Show> shows;
public:
	Artist();
	Artist(char* name, std::string date, std::string place, int availablePlaces, int occupiedPlaces);
	Artist(char* name, const Show& s);
	Artist(char* name, std::vector<Show> shows);
	Artist(const Artist& a);
	~Artist();
	char* getName();
	void setName(char* name);
	std::vector<Show> getShows();
	void addShow(const Show& s);
	void setShows(std::vector<Show> shows);
	Artist& operator=(const Artist& a);
	bool operator==(const Artist& a) const;
	IE* clone();
	void copy(IE* e);
	bool equals(IE* e);
	std::string toStringCSV();
	std::string toStringTXT();
};

