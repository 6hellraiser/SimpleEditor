#include "fileoperatortests.h"
#include "fileoperator.h"
#include "3DObject/objectmodel.h"

using namespace FileReaderTests;
using namespace ObjReader;
using namespace ObjectModel;

void FileOperatorTests::textStreamTest()
{
    Object expectedObject;

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

    expectedObject.v.push_back(QVector3D(1, 2, 3));
    expectedObject.v.push_back(QVector3D(2.0, -1, 4));
    expectedObject.v.push_back(QVector3D(4, 6, 7));
    expectedObject.vt.push_back(QVector2D(1, 0.0));
    expectedObject.vt.push_back(QVector2D(0, 1.0));
    expectedObject.vt.push_back(QVector2D(1, 1.0));
    expectedObject.fv = {1,2,3,1,2,3,2};
    expectedObject.fvIndices = {0, 3, 7};
    expectedObject.fvt = {1,2,3,2,1,3,1};
    expectedObject.fvtIndices = {0, 3, 7};

    FileOperator loader;
    Object actualObject;
    QString erSt;
    loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(actualObject.v, expectedObject.v);
    QCOMPARE(actualObject.vt, expectedObject.vt);
    QCOMPARE(actualObject.fv, expectedObject.fv);
    QCOMPARE(actualObject.fvIndices, expectedObject.fvIndices);
    QCOMPARE(actualObject.fvt, expectedObject.fvt);
    QCOMPARE(actualObject.fvtIndices, expectedObject.fvtIndices);
}

void FileOperatorTests::irregularFileTest()
{
    FileOperator loader;
    Object actualObject;
    QString erSt;
    loader.loadObjFile(":/UnitTests/irregular.obj", erSt, actualObject);

    Object expectedObject;

    expectedObject.v.push_back(QVector3D(2.0, -1.0, 0.0));
    expectedObject.v.push_back(QVector3D(1.0, -1.0, 2.0));
    expectedObject.v.push_back(QVector3D(0.0, -1.0, 0.0));
    expectedObject.v.push_back(QVector3D(1.0, 2.0, 0.0));

    expectedObject.vt.push_back(QVector2D(0, -1.0));
    expectedObject.vt.push_back(QVector2D(1.0, 0.0));

    expectedObject.fv = {1,2,3,2,4};
    expectedObject.fvIndices = {0,3,5};

    expectedObject.fvt = {1,1,2,2,1};
    expectedObject.fvtIndices = {0,3,5};

    QCOMPARE(actualObject.v, expectedObject.v);
    QCOMPARE(actualObject.vt, expectedObject.vt);
    QCOMPARE(actualObject.fv, expectedObject.fv);
    QCOMPARE(actualObject.fvIndices, expectedObject.fvIndices);
    QCOMPARE(actualObject.fvt, expectedObject.fvt);
    QCOMPARE(actualObject.fvtIndices, expectedObject.fvtIndices);
}

void FileOperatorTests::emptyStreamTest()
{
    QTextStream stream("");

    FileOperator loader;
    Object actualObject;
    QString erSt;
    loader.parseObjStream(stream, erSt, actualObject);

    Object expectedObject;

    QCOMPARE(actualObject.v, expectedObject.v);
    QCOMPARE(actualObject.vt, expectedObject.vt);
}

void FileOperatorTests::incorrectVStreamTest()
{
    QTextStream stream("v 1 hi 3\n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("Could not convert line 1 to float.", erSt);
}

void FileOperatorTests::incorrectVTStreamTest()
{
    QTextStream stream("vt 1 wrong 3\n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("Could not convert line 1 to float.", erSt);
}

void FileOperatorTests::incorrectFStreamTest()
{
    QTextStream stream("f 1/2/ 3 3\n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}

void FileOperatorTests::incorrectFStreamTest2()
{
    QTextStream stream("f 1 3 3/1/\n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}

void FileOperatorTests::incorrectFStreamTest3()
{
    QTextStream stream("f \n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("An empty f line with number 1 occured.", erSt);
}

void FileOperatorTests::incorrectFStreamTest4()
{
    QTextStream stream("f 1/2/ 3/2 3/1/\n");
    FileOperator loader;
    Object actualObject;
    QString erSt;
    bool success = loader.parseObjStream(stream, erSt, actualObject);

    QCOMPARE(false, success);
    QCOMPARE("Inapropriate line structure in the line 1.", erSt);
}
