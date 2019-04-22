#ifndef FILEOPERATORTESTS_H
#define FILEOPERATORTESTS_H

#include <QTest>

namespace fileOperator {

class FileOperatorTests : public QObject
{
    Q_OBJECT

private slots:
    void textStreamTest();
    void irregularFileTest();
    void emptyStreamTest();
    void incorrectStreamTest();
};

}


#endif // FILELOADERTESTS_H
