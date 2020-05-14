#include "UI.h"
#include <Windows.h>

void UI::handleOpenApp() {
	string uName;
	cout << "Username : "; cin >> uName; cout << '\n';
	string passwd;
	cout << "Password : "; 
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	cin >> passwd; 
	SetConsoleMode(hStdin, mode);
	cout << '\n';
	try {
		s->login(uName, passwd);
		for (IE* e : s->getAll())
			cout << e->toStringTXT() << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleAddArtist() {
	try {
		char name[20];
		string date, place, avl, occ;
		cout << " Enter artist's name : "; cin >> name; cout << '\n';
		cout << " Enter show's date : "; cin >> date; cout << '\n';
		cout << " Enter show's place : "; cin >> place; cout << '\n';
		cout << " Enter show's available places : "; cin >> avl; cout << '\n';
		cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
		int avlP = stoi(avl), occP = stoi(occ);
		this->s->addArtistShow(name, date, place, avlP, occP);
		cout << " Artist added successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleAddArtistShows() {
	try {
		char name[20];
		int noShows;
		string date, place, avl, occ;
		int avlP, occP;
		cout << " Enter artist's name : "; cin >> name; cout << '\n';
		cout << " Enter the number of shows : "; cin >> noShows; cout << '\n';
		vector<Show> shows;
		for (int i = 0; i < noShows; i++) {
			cout << " Enter show's date : "; cin >> date; cout << '\n';
			cout << " Enter show's place : "; cin >> place; cout << '\n';
			cout << " Enter show's available places : "; cin >> avl; cout << '\n';
			cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
			avlP = stoi(avl);
			occP = stoi(occ);
			Show s(date, place, avlP, occP);
			shows.emplace_back(s);
		}
		
		this->s->addArtistShows(name, shows);
		cout << " Artist added successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleAddFilmShows() {
	try {
		char title[20];
		vector<string> actors;
		string date, place, avl, occ;
		int avlP, occP, noActors, noShows;
		cout << " Enter film's title : "; cin >> title; cout << '\n';
		cout << " Enter the amount of actors : "; cin >> noActors; cout << '\n';
		for (int i = 0; i < noActors; i++) {
			string actor;
			cout << " Enter actor's name : "; cin >> actor; cout << '\n';
			actors.emplace_back(actor);
		}
		cout << " Enter the number of shows : "; cin >> noShows; cout << '\n';
		vector<Show> shows;
		for (int i = 0; i < noShows; i++) {
			cout << " Enter show's date : "; cin >> date; cout << '\n';
			cout << " Enter show's place : "; cin >> place; cout << '\n';
			cout << " Enter show's available places : "; cin >> avl; cout << '\n';
			cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
			avlP = stoi(avl);
			occP = stoi(occ);
			Show s(date, place, avlP, occP);
			shows.emplace_back(s);
		}
		this->s->addFilmShows(title, actors, shows);
		cout << " Film added successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleAddFilm() {
	try {
		char title[20];
		vector<string> actors;
		string date, place, avl, occ;
		int avlP, occP, noActors;
		cout << " Enter film's title : "; cin >> title; cout << '\n';
		cout << " Enter the amount of actors : "; cin >> noActors; cout << '\n';
		for (int i = 0; i < noActors; i++) {
			string actor;
			cout << " Enter actor's name : "; cin >> actor; cout << '\n';
			actors.emplace_back(actor);
		}
		cout << " Enter show's date : "; cin >> date; cout << '\n';
		cout << " Enter show's place : "; cin >> place; cout << '\n';
		cout << " Enter show's available places : "; cin >> avl; cout << '\n';
		cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
		avlP = stoi(avl);
		occP = stoi(occ);
		this->s->addFilmShow(title, actors, date, place, avlP, occP);
		cout << " Film added successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleModifyArtist() {
	try {
		char name[20], oldName[20];
		cout << "Enter artist's name : "; cin >> oldName; cout << '\n';
		int noShows;
		string date, place, avl, occ;
		int avlP, occP;
		cout << " Enter artist's new name : "; cin >> name; cout << '\n';
		cout << " Enter the number of shows : "; cin >> noShows; cout << '\n';
		vector<Show> shows;
		for (int i = 0; i < noShows; i++) {
			cout << " Enter show's date : "; cin >> date; cout << '\n';
			cout << " Enter show's place : "; cin >> place; cout << '\n';
			cout << " Enter show's available places : "; cin >> avl; cout << '\n';
			cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
			avlP = stoi(avl);
			occP = stoi(occ);
			Show s(date, place, avlP, occP);
			shows.emplace_back(s);
		}

		this->s->modifyArtist(oldName, name, shows);
		cout << " Artist modified successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleModifyFilm() {
	try {
		char title[20], oldTitle[20];
		cout << " Enter film's old title : "; cin >> oldTitle; cout << '\n';
		vector<string> actors;
		string date, place, avl, occ;
		int avlP, occP, noActors, noShows;
		cout << " Enter film's new title : "; cin >> title; cout << '\n';
		cout << " Enter the amount of actors : "; cin >> noActors; cout << '\n';
		for (int i = 0; i < noActors; i++) {
			string actor;
			cout << " Enter actor's name : "; cin >> actor; cout << '\n';
			actors.emplace_back(actor);
		}
		cout << " Enter the number of shows : "; cin >> noShows; cout << '\n';
		vector<Show> shows;
		for (int i = 0; i < noShows; i++) {
			cout << " Enter show's date : "; cin >> date; cout << '\n';
			cout << " Enter show's place : "; cin >> place; cout << '\n';
			cout << " Enter show's available places : "; cin >> avl; cout << '\n';
			cout << " Enter show's occupied places : "; cin >> occ; cout << '\n';
			avlP = stoi(avl);
			occP = stoi(occ);
			Show s(date, place, avlP, occP);
			shows.emplace_back(s);
		}
		this->s->modifyFilm(oldTitle, title, actors, shows);
		cout << " Film modified successfully! " << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleDeleteArtist() {
	try {
		char name[20];
		cout << " Enter artist's name : ";
		cin >> name; cout << '\n';
		this->s->deleteElem(name);
		cout << " Artist deleted successfully! " << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleDeleteFilm() {
	try {
		char title[20];
		cout << " Enter film's title : ";
		cin >> title; cout << '\n';
		this->s->deleteElem(title);
		cout << " Film deleted successfully! " << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleShowAll() {
	try {
		string repoType = this->s->getRepoType();
		if (repoType == "TXT") {
			for (IE* e : this->s->getAll())
				cout << e->toStringTXT() << '\n';
		}
		if (repoType == "CSV") {
			for (IE* e : this->s->getAll())
				cout << e->toStringCSV() << '\n';
		}
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::showMenu() {
	cout << "1. Login" << '\n';
	cout << "2. Add artist with a show" << '\n';
	cout << "3. Add artist with shows" << '\n';
	cout << "4. Add film with a show" << '\n';
	cout << "5. Add film with shows" << '\n';
	cout << "6. Modify an artist" << '\n';
	cout << "7. Modify a film" << '\n';
	cout << "8. Delete an artist" << '\n';
	cout << "9. Delete a film" << '\n';
	cout << "10. Show all" << '\n';
	cout << "11. Get artists and films that are happening on a given date" << '\n';
	cout << "12. Buy tickets" << '\n';
	cout << "13. Logout" << '\n';
	cout << "x. Exit" << '\n';
}

void UI::handleCloseApp() {
	try {
		this->s->revertAccess();
		cout << " Successful logout!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}

void UI::handleGetShowsByDate() {
	try {
		string date;
		cout << " Enter the date : "; cin >> date; cout << '\n';
		vector<IE*> result = this->s->givenDate(date);
		string repoType = this->s->getRepoType();
		if (repoType == "TXT") {
			for (IE* e : result)
				cout << e->toStringTXT() << '\n';
		}
		if (repoType == "CSV") {
			for (IE* e : result)
				cout << e->toStringCSV() << '\n';
		}
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
	
}

void UI::handleBuyTickets() {
	try {
		string date, place, amount, name;
		cout << " Enter your name : "; cin >> name; cout << '\n';
		cout << " Enter the show's date : "; cin >> date; cout << '\n';
		cout << " Enter the show's place : "; cin >> place; cout << '\n';
		cout << " Enter how many tickets you'd like to buy : "; cin >> amount; cout << '\n';
		int amnt = stoi(amount);
		bool res = this->s->buyTickets(date, place, amnt);
		if (res)
			cout << "Tickets bought successfully!" << '\n';
		else
			cout << "Show not found!" << '\n';
	}
	catch (std::invalid_argument&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (std::out_of_range&) {
		cout << "Invalid integer value!" << '\n';
	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}
	


void UI::run() {
	try {
		string opt = "0";
		while (opt != "x") {
			this->showMenu();
			cin >> opt;
			if (opt == "1")
				this->handleOpenApp();
			if (opt == "2")
				this->handleAddArtist();
			if (opt == "3")
				this->handleAddArtistShows();
			if (opt == "4")
				this->handleAddFilm();
			if (opt == "5")
				this->handleAddFilmShows();
			if (opt == "6")
				this->handleModifyArtist();
			if (opt == "7")
				this->handleModifyFilm();
			if (opt == "8")
				this->handleDeleteArtist();
			if (opt == "9")
				this->handleDeleteFilm();
			if (opt == "10")
				this->handleShowAll();
			if (opt == "11")
				this->handleGetShowsByDate();
			if (opt == "12")
				this->handleBuyTickets();
			if (opt == "13")
				this->handleCloseApp();

		}

	}
	catch (MyExc& exc) {
		cout << exc.what() << '\n';
	}
	catch (...) {
		cout << " Unhandled exception!" << '\n';
	}
}