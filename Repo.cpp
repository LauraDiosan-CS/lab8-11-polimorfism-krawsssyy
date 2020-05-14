#include "Repo.h"
Repo::Repo() {
	elems.reserve(MAX);
}

Repo::Repo(std::vector<IE*> elems) {
	int len = elems.size();
	for (int i = 0; i < len; i++)
		this->elems.push_back(elems[i]->clone());
}

Repo::~Repo() {
	elems.clear();
}

void Repo::clearRepo() {
	this->elems.clear();
}

void Repo::addElem(IE* elem) {
	elems.emplace_back(elem->clone());
}

int Repo::getElemPos(IE* elem) throw(MyExc){
	int len = this->elems.size();
	int i = 0;
	for (i = 0; i < len; i++)
		if (elems[i]->equals(elem))
			break;
	if (i == len)
		throw MyExc("Given element was not found!");
	return i;
}

IE* Repo::getElemByPos(int pos) throw(MyExc){
	if ((size_t)pos >= this->elems.size() or pos < 0)
		throw MyExc("Invalid position given!");
	int len = this->elems.size();
	int i = 0;
	for (i = 0; i < len; i++)
		if (i == pos)
			return elems[i]->clone();
}

void Repo::modifyElem(IE* oldElem, IE* newElem) {
	int pos = this->getElemPos(oldElem);
	int len = this->elems.size();
	for(int i = 0; i < len; i++)
		if (i == pos)
		{
			delete[] this->elems[i];
			this->elems[i] = newElem->clone();
			break;
		}
}

void Repo::deleteElem(IE* elem) {
	int pos = this->getElemPos(elem);
	int len = this->elems.size();
	delete this->elems[pos];
	this->elems[pos] = nullptr;
	std::vector<IE*> firstHalf;
	std::vector<IE*> secondHalf;
	for (int i = 0; i < pos; i++)
			firstHalf.emplace_back((this->elems[i])->clone());
	for (int i = pos + 1; i < len; i++)
		secondHalf.emplace_back((this->elems[i])->clone());
	firstHalf.insert(firstHalf.end(), secondHalf.begin(), secondHalf.end());
	this->elems.clear();
	std::copy(firstHalf.begin(), firstHalf.end(), back_inserter(this->elems));
	firstHalf.clear();
	secondHalf.clear();
}

int Repo::getSize() {
	return this->elems.size();
}

std::vector<IE*> Repo::getAll() {
	return this->elems;
}