#pragma once
#include <vector>
#include "IE.h"
#define MAX 1000
class Repo{
private:
	std::vector<IE*> elems;
protected:
	void clearRepo();
public:
	Repo();
	Repo(std::vector<IE*> elems);
	~Repo();
	void addElem(IE* elem);
	int getElemPos(IE* elem);
	IE* getElemByPos(int pos);
	void modifyElem(IE* oldElem, IE* newElem);
	void deleteElem(IE* elem);
	int getSize();
	std::vector<IE*> getAll();

};

