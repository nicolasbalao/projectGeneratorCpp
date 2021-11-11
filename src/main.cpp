#include <iostream>
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