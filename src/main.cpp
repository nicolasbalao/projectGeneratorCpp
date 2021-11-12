/*
TODO: 
//// add argument path
////- add Tab

- Group for option to create class In the project



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

    window.show();

    return app.exec();
}