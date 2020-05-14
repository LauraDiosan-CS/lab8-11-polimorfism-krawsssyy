#pragma once
#include "Repo.h"
#include <fstream>
#include "Film.h"
#include "Artist.h"
class RepoFileCSV : public Repo {
private:
	 char* FILE_PATH;
public:
	RepoFileCSV() : Repo() {
		this->FILE_PATH = nullptr;
	}

	RepoFileCSV(const char* FILE_PATH) {
		this->FILE_PATH = new char[strlen(FILE_PATH) + 1];
		strcpy_s(this->FILE_PATH, strlen(FILE_PATH) + 1, FILE_PATH);
	}


	~RepoFileCSV() {
		if (this->FILE_PATH)
			delete[] this->FILE_PATH, this->FILE_PATH = nullptr;
	}
	void loadFromFile() {
		if (this->FILE_PATH)
		{
			std::string str(this->FILE_PATH);
			if (str.find(".csv") == std::string::npos && str.find(".CSV") == std::string::npos)
				throw MyExc("Invalid file extension!");
			std::ifstream f(FILE_PATH);
			if (!f.is_open())
				throw MyExc("Wrong path to the file or filename!");
			this->clearRepo();
			std::string line;
			while (getline(f, line))
			{
				size_t firstRes = line.find(',');
				std::string type = line.substr(0, firstRes);
				line.erase(0, firstRes + 1);
				if (type == "Film")
				{
					size_t res = line.find(',');
					char* title = new char[line.substr(0, res).length() + 1];
					strcpy_s(title, line.substr(0, res).length() + 1, line.substr(0, res).c_str());
					line.erase(0, res + 1);
					res = line.find(',');
					int noOfActors = std::stoi(line.substr(0, res));
					line.erase(0, res + 1);
					std::vector<std::string> actors;
					std::vector<Show> shows;
					for (int i = 0; i < noOfActors; i++)
					{
						res = line.find(',');
						actors.emplace_back(line.substr(0, res));
						line.erase(0, res + 1);
					}
					while (line.find(',') != std::string::npos || line != "")
					{
						res = line.find(',');
						std::string currShow = line.substr(0, res);
						if (res == std::string::npos)
							line = "";
						else
							line.erase(0, res + 1);
						line.erase(0, res + 1);
						res = currShow.find(' ');
						std::string date = currShow.substr(0, res);
						currShow.erase(0, res + 1);
						res = currShow.find(' ');
						std::string place = currShow.substr(0, res);
						currShow.erase(0, res + 1);
						res = currShow.find(' ');
						int availablePlaces = std::stoi(currShow.substr(0, res));
						currShow.erase(0, res + 1);
						int occupiedPlaces = std::stoi(currShow);
						Show s(date, place, availablePlaces, occupiedPlaces);
						shows.emplace_back(s);
						
					}
					Film* f = new Film(title, actors, shows);
					this->addElem(f);
				}
				else if (type == "Artist")
				{
					size_t res = line.find(',');
					char* name = new char[line.substr(0, res).length() + 1];
					strcpy_s(name, line.substr(0, res).length() + 1, line.substr(0, res).c_str());
					line.erase(0, res + 1);
					std::vector<Show> shows;
					while (line.find(',') != std::string::npos || line != "")
					{
						res = line.find(',');
						std::string currShow = line.substr(0, res);
						if (res == std::string::npos)
							line = "";
						else
							line.erase(0, res + 1);
						res = currShow.find(' ');
						std::string date = currShow.substr(0, res);
						currShow.erase(0, res + 1);
						res = currShow.find(' ');
						std::string place = currShow.substr(0, res);
						currShow.erase(0, res + 1);
						res = currShow.find(' ');
						int availablePlaces = std::stoi(currShow.substr(0, res));
						currShow.erase(0, res + 1);
						int occupiedPlaces = std::stoi(currShow);
						Show s(date, place, availablePlaces, occupiedPlaces);
						shows.emplace_back(s);

					}
					Artist* a = new Artist(name, shows);
					this->addElem(a);
				}
			}
			f.close();
		} 

	}
	
	void saveToFile() {
		if (this->FILE_PATH)
		{
			std::string str(this->FILE_PATH);
			if (str.find(".csv") == std::string::npos && str.find(".CSV") == std::string::npos)
				throw MyExc("Invalid file extension!");
			std::ofstream f(FILE_PATH);
			if (!f.is_open())
				throw MyExc("Wrong path to the file or filename!");
			int len = this->getSize();
			std::vector<IE*> elems = this->getAll();
			for (int i = 0; i < len; i++)
				f << elems[i]->toStringCSV() << '\n';
			f << '\0';
			f.close();
		}
	}

};