#pragma once
#include "RepoFileCSV.h"
#include "RepoFileTXT.h"
class Test {
private:
	void testShow();
	void testFilm();
	void testArtist();
	//void testRepo();
	void testRepoFileTXT();
	void testRepoFileCSV();
	void testService();
public:
	void runAll();
	Test() {}
	~Test() {}
};