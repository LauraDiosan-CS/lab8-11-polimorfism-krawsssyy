#pragma once
#include "Service.h"
#include <iostream>
using namespace std;

class UI {
private:
	Service* s;
	void handleOpenApp();
	void handleAddArtist();
	void handleAddArtistShows();
	void handleAddFilm();
	void handleAddFilmShows();
	void handleModifyArtist();
	void handleModifyFilm();
	void handleDeleteArtist();
	void handleDeleteFilm();
	void handleShowAll();
	void handleCloseApp();
	void handleGetShowsByDate();
	void handleBuyTickets();
	void showMenu();
public:
	UI(Service* serv) : s(serv) { }
	~UI() { }
	void run();
};