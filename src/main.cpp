/*
Amélioration Possible:

- pouvoir ouvrire les fichier depuis l'app
- design
- popUP qui confirme la création du projet



*/
#include <iostream>
#include <filesystem>
#include <QWidget>
#include <QApplication>

#include "../includes/MainWindow.h"

using namespace std;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    MainWindow window;

    window.resize(700, 700);
    window.show();

    return app.exec();
}