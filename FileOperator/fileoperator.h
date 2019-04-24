#ifndef FileOperator_H
#define FileOperator_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QTextStream>

#include "fileloadertests.h"
#include "3DObject/objectmodel.h"

namespace ObjReader {

class FileOperator {
private:
    bool parseV(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber = 0);
    bool parseVT(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber = 0);
    bool parseF(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber = 0);

public:
    bool parseObjStream(QTextStream& textStream, QString& errorString, ObjectModel::Object& obj);
    bool loadObjFile(const QString& fileName, QString& errorString, ObjectModel::Object& obj);
};

}

#endif // FileOperator_H
