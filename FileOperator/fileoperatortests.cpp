#include "fileoperatortests.h"
#include "fileoperator.h"

using namespace fileOperator;

void FileOperatorTests::textStreamTest()
{
    FileOperator expectedLoader;

    QTextStream stream("v 1 2 3\n"  \
                       "v 2.0 -1 4\n"\
                       "v 4 6 7\n"    \
                       "vt 1 0.0\n"    \
                       "vt 0 1.0\n"     \
                       "vt 1 1.0\n"      \
                       "vn 1.0 0 0\n"     \
                       "vn 1.0 1.0 0\n"    \
                       "f 1/1/1 2/2/2 3/3/1\n" \
                       "f 1/2/ 2/1/ 3/3/ 2/1/\n"\
                       );

    expectedLoader.v.push_back(QVector3D(1, 2, 3));
    expectedLoader.v.push_back(QVector3D(2.0, -1, 4));
    expectedLoader.v.push_back(QVector3D(4, 6, 7));
    expectedLoader.vt.push_back(QVector2D(1, 0.0));
    expectedLoader.vt.push_back(QVector2D(0, 1.0));
    expectedLoader.vt.push_back(QVector2D(1, 1.0));
    expectedLoader.fv = {1,2,3,1,2,3,2};
    expectedLoader.fvIndices = {0, 3, 7};
    expectedLoader.fvt = {1,2,3,2,1,3,1};
    expectedLoader.fvtIndices = {0, 3, 7};

    FileOperator loader;
    QString erSt;
    loader.parseObjStream(stream, erSt);

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
    QCOMPARE(loader.fv, expectedLoader.fv);
    QCOMPARE(loader.fvIndices, expectedLoader.fvIndices);
    QCOMPARE(loader.fvt, expectedLoader.fvt);
    QCOMPARE(loader.fvtIndices, expectedLoader.fvtIndices);
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

    expectedLoader.fv = {1,2,3,2,4};
    expectedLoader.fvIndices = {0,3,5};

    expectedLoader.fvt = {1,1,2,2,1};
    expectedLoader.fvtIndices = {0,3,5};

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
    QCOMPARE(loader.fv, expectedLoader.fv);
    QCOMPARE(loader.fvIndices, expectedLoader.fvIndices);
    QCOMPARE(loader.fvt, expectedLoader.fvt);
    QCOMPARE(loader.fvtIndices, expectedLoader.fvtIndices);
}

void FileOperatorTests::emptyStreamTest()
{
    QTextStream stream("");

    FileOperator loader;
    QString erSt;
    loader.parseObjStream(stream, erSt);

    FileOperator expectedLoader;

    QCOMPARE(loader.v, expectedLoader.v);
    QCOMPARE(loader.vt, expectedLoader.vt);
}

void FileOperatorTests::incorrectVStreamTest()
{
    QTextStream stream("v 1 hi 3\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Could not convert line 1 to float.", erSt);
}

void FileOperatorTests::incorrectVTStreamTest()
{
    QTextStream stream("vt 1 wrong 3\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Could not convert line 1 to float.", erSt);
}

void FileOperatorTests::incorrectFStreamTest()
{
    QTextStream stream("f 1/2/ 3 3\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}

void FileOperatorTests::incorrectFStreamTest2()
{
    QTextStream stream("f 1 3 3/1/\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}

void FileOperatorTests::incorrectFStreamTest3()
{
    QTextStream stream("f \n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("An empty f line with number 1 occured.", erSt);
}

void FileOperatorTests::incorrectFStreamTest4()
{
    QTextStream stream("f 1/2/ 3/2 3/1/\n");
    FileOperator expectedLoader;
    QString erSt;
    bool success = expectedLoader.parseObjStream(stream, erSt);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}
