#include "mainwindow.h"
#include <QApplication>
#include <FileOperator/fileoperatortests.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    FileReaderTests::FileOperatorTests fot;
    QTest::qExec(&fot);

    return a.exec();
}
