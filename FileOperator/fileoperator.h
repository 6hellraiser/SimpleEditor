#ifndef FileLoader_H
#define FileLoader_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QTextStream>

#include "FileOperator/fileoperatortests.h"

namespace ObjReader {
    class FileLoader;
}

class FileOperator {
private:
    bool parseV(QStringList lineParts, QString& errorString, int lineNumber);
    bool parseVT(QStringList lineParts, QString& errorString, int lineNumber);
    bool parseF(QStringList lineParts, QString& errorString, int lineNumber);

    QVector<QVector3D> v;
    QVector<QVector2D> vt; //can be QVector3D
    QVector<int> fv;
    QVector<int> fvIndices;
    QVector<int> fvt;
    QVector<int> fvtIndices;

    friend class fileOperator::FileOperatorTests;

public:
    FileOperator();
    bool parseObjStream(QTextStream& textStream, QString& errorString);
    bool loadObjFile(const QString& fileName, QString& errorString);
};

#endif // FileLoader_H
