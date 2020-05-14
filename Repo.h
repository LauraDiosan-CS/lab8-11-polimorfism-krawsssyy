#pragma once
#include <vector>
#include "IE.h"
#include "MyException.h"
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
	int getElemPos(IE* elem) throw(MyExc);
	IE* getElemByPos(int pos) throw(MyExc);
	void modifyElem(IE* oldElem, IE* newElem);
	void deleteElem(IE* elem);
	int getSize();
	std::vector<IE*> getAll();
	virtual void loadFromFile() = 0;
	virtual void saveToFile() = 0;

};

