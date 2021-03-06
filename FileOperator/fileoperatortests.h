#ifndef FILEOPERATORTESTS_H
#define FILEOPERATORTESTS_H

#include <QTest>

namespace FileReaderTests {

class FileOperatorTests : public QObject
{
    Q_OBJECT

private slots:
    void textStreamTest();
    void irregularFileTest();
    void emptyStreamTest();
    void incorrectVStreamTest();
    void incorrectVTStreamTest();
    void incorrectFStreamTest();
    void incorrectFStreamTest2();
    void incorrectFStreamTest3();
    void incorrectFStreamTest4();
};

}


#endif // FILELOADERTESTS_H
