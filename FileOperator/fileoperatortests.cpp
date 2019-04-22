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


