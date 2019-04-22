#include "mainwindow.h"
#include <QApplication>
//#include "fileoperator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // FileOperator fl;
    //QFile f(":/obj_files/cube.obj");
   // fl.parseobjfile(":/obj_files/cube.obj");


    MainWindow w;
    w.show();

    return a.exec();
}
