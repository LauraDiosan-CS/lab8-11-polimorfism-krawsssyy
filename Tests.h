#pragma once
#include "RepoFileCSV.h"
#include "RepoFileTXT.h"
class Test {
private:
	void testShow();
	void testFilm();
	void testArtist();
	void testRepo();
	void testRepoFileTXT();
	void testRepoFileCSV();
public:
	void runAll();
	Test() {}
	~Test() {}
};