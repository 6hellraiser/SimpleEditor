#include "MainWindow.h"
#include <QApplication>
#include "fileloader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileLoader fl;
    //QFile f(":/obj_files/cube.obj");
    fl.parseobjfile(":/obj_files/cube.obj");


    MainWindow w;
    w.show();

    return a.exec();
}
