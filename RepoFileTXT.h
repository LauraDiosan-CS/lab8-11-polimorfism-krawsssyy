#pragma once
#include "Repo.h"
#include <fstream>
#include "Artist.h"
#include "Film.h"
class RepoFileTXT : public Repo {
private:
	char* FILE_PATH;
public:
	RepoFileTXT() : Repo() {
		this->FILE_PATH = nullptr;
	}
	RepoFileTXT(const char* FILE_PATH) {
		this->FILE_PATH = new char[strlen(FILE_PATH) + 1];
		strcpy_s(this->FILE_PATH, strlen(FILE_PATH) + 1, FILE_PATH);
	}

	~RepoFileTXT() {
		if (this->FILE_PATH)
			delete[] this->FILE_PATH, this->FILE_PATH = nullptr;
	}

	void loadFromFile() {
		if (this->FILE_PATH)
		{
			std::string str(this->FILE_PATH);
			if (str.find(".txt") == std::string::npos && str.find(".TXT") == std::string::npos)
				throw MyExc("Invalid file extension!");
			std::ifstream f(FILE_PATH);
			if (!f.is_open())
				throw MyExc("Wrong path to the file or filename!");
			this->clearRepo();
			std::string line;
			while (getline(f, line)) {
				if (line == "Film")
				{
					getline(f, line);
					char* title = new char[30];
					strcpy_s(title, line.length() + 1, line.c_str());
					getline(f, line);
					std::vector<std::string> actors;
					std::vector<Show> shows;
					while (getline(f, line) && line != "Spectacole : ")
					{
						actors.emplace_back(line);
					}
					while (getline(f, line) && line != " " && line != "")
					{
						size_t res = line.find(',');
						std::string date = line.substr(0, res);
						line.erase(0, res + 1);
						res = line.find(',');
						std::string place = line.substr(0, res);
						line.erase(0, res + 1);
						res = line.find(',');
						std::string availablePlaces = line.substr(0, res);
						line.erase(0, res + 1);
						std::string occupiedPlaces = line;
						int avP = std::stoi(availablePlaces);
						int ocP = std::stoi(occupiedPlaces);
						Show s = Show(date, place, avP, ocP);
						shows.emplace_back(s);

					}
					Film* f = new Film(title, actors, shows);
					this->addElem(f);
				}
				else if (line == "Artist")
				{
					getline(f, line);
					char* name = new char[30];
					strcpy_s(name, line.length() + 1, line.c_str());
					std::vector<Show> shows;
					while (getline(f, line) && line != " " && line != "")
					{
						size_t res = line.find(',');
						std::string date = line.substr(0, res);
						line.erase(0, res + 1);
						res = line.find(',');
						std::string place = line.substr(0, res);
						line.erase(0, res + 1);
						res = line.find(',');
						std::string availablePlaces = line.substr(0, res);
						line.erase(0, res + 1);
						std::string occupiedPlaces = line;
						int avP = std::stoi(availablePlaces);
						int ocP = std::stoi(occupiedPlaces);
						Show s = Show(date, place, avP, ocP);
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
			if (str.find(".txt") == std::string::npos && str.find(".TXT") == std::string::npos)
				throw MyExc("Invalid file extension!");
			std::ofstream f(FILE_PATH);
			if (!f.is_open())
				throw MyExc("Wrong path to the file or filename!");
			int len = this->getSize();
			std::vector<IE*> elems = this->getAll();
			for (int i = 0; i < len; i++)
				f << elems[i]->toStringTXT() << '\n';
			f << '\0';
			f.close();
		}
	}

};