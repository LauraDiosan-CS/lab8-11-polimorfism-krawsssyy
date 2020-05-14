#include <iostream>
#include "Tests.h"
#include "ValidateShow.h"
#include "ValidateFilm.h"
#include "ValidateArtist.h"
#include "Service.h"

int main()
{
    Test test;
    test.runAll();
    char* name = new char[20];
    strcpy_s(name, 7, "Andrei");
    IE* artist = new Artist(name, "11/11/2019", "Bucuresti", 100, 50);
    IE* artist2 = new Artist(name, "12/12/2020", "Cluj", 200, 100);
    std::cout << "TXT / CSV" << '\n';
    std::string opt;
    std::cin >> opt;
    Repo* r;
    if (opt == "TXT")
        r = new RepoFileTXT("test.txt");
    else
        r = new RepoFileCSV("test.csv");
    r->addElem(artist);
    r->addElem(artist2);
    r->saveToFile();
    std::string uName, passwd;
    std::cout << "Username : ";
    std::cin >> uName;
    std::cout << "\n" << "Password : ";
    std::cin >> passwd;
    std::cout << '\n';
    Validator* showVal = new ValidatorShow;
    Validator* artistVal = new ValidatorArtist;
    Validator* filmVal = new ValidatorFilm;
    Service* s = new Service(r, showVal, artistVal, filmVal);
    try {
        s->login(uName, passwd);
        std::vector<IE*> v= s->getAll();
        for (IE* e : v)
            std::cout << e->toStringTXT() << '\n';
    }
    catch (MyExc& exc) {
        std::cout << exc.what() << '\n';
    }
    delete s;
    s = nullptr;
    delete filmVal;
    filmVal = nullptr;
    delete artistVal;
    artistVal = nullptr;
    delete showVal;
    showVal = nullptr;
    delete r;
    r = nullptr;
    delete[] name;
    name = nullptr;

    return 0;
}

