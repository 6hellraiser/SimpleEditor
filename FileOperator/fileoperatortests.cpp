#include "fileoperatortests.h"
#include "fileoperator.h"

using namespace fileOperator;

void FileOperatorTests::textStreamTest()
{
    FileOperator expectedLoader;

    QTextStream stream("v 1 2 3\n"    \
                       "v 2.0 -1 4\n" \
                      "vt 1 0.0\n");

    expectedLoader.v.push_back(QVector3D(1, 2, 3));
    expectedLoader.v.push_back(QVector3D(2.0, -1, 4));
    expectedLoader.vt.push_back(QVector2D(1, 0.0));

    FileOperator loader;
    QString erSt;
    loader.parseObjFile(stream, erSt);

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
}

void FileOperatorTests::irregularFileTest()
{
    FileOperator loader;
    QString erSt;
    loader.loadObjFile(":/UnitTests/irregular.obj", erSt);

    FileOperator expectedLoader;

    expectedLoader.v.push_back(QVector3D(2.0, -1.0, 0.0));
    expectedLoader.v.push_back(QVector3D(1.0, -1.0, 2.0));
    expectedLoader.v.push_back(QVector3D(0.0, -1.0, 0.0));
    expectedLoader.v.push_back(QVector3D(1.0, 2.0, 0.0));

    expectedLoader.vt.push_back(QVector2D(0, -1.0));
    expectedLoader.vt.push_back(QVector2D(1.0, 0.0));

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
}

void FileOperatorTests::emptyStreamTest()
{
    QTextStream stream("");

    FileOperator loader;
    QString erSt;
    loader.parseObjFile(stream, erSt);

    FileOperator expectedLoader;

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
}

void FileOperatorTests::incorrectStreamTest()
{
    QTextStream stream("v 1 hi 3\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjFile(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Could not convert line 1 to float.", erSt);
}
