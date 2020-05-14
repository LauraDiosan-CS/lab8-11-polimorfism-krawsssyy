#include <iostream>
#include "Tests.h"
#include "ValidateShow.h"
#include "ValidateFilm.h"
#include "ValidateArtist.h"
#include "UI.h"

int main()
{
    Test test;
    test.runAll();
    std::cout << "TXT / CSV" << '\n';
    std::string opt;
    std::cin >> opt;
    try {
        Repo* r;
        char FILE_PATH[30];
        cout << "Give file path and name : "; cin >> FILE_PATH; cout << '\n';
        if (opt == "TXT")
            r = new RepoFileTXT(FILE_PATH);
        else if (opt == "CSV")
            r = new RepoFileCSV(FILE_PATH);
        else
            throw MyExc("Invalid extension chosen!");
        r->loadFromFile();
        Validator* showVal = new ValidatorShow;
        Validator* artistVal = new ValidatorArtist;
        Validator* filmVal = new ValidatorFilm;
        Service* s = new Service(r, showVal, artistVal, filmVal);
        UI* ui = new UI(s);
        ui->run();


        r->saveToFile();
        delete ui;
        ui = nullptr;
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
    }
    catch (MyExc& exc) {
        cout << exc.what() << "\nExiting..."<< '\n';
    }
    catch (...) {
        cout << " Unhandled exception!\n Exiting..." << '\n';
    }
    return 0;
}

