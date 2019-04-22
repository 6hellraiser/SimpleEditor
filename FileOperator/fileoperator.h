#ifndef FileLoader_H
#define FileLoader_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QTextStream>



namespace ObjReader {
    class FileLoader;
}

class FileOperator {
private:
    QVector<QVector3D> v;
    QVector<QVector2D> vt; //can be QVector3D
    QVector<QVector3D> f_v;
    QVector<QVector3D> f_vt;
    bool parseObjFile(QTextStream& textStream, QString& errorString);
    bool parseV(QStringList lineParts, QString& errorString, int lineNumber);
    bool parseVT(QStringList lineParts, QString& errorString, int lineNumber);
    bool parseF(QStringList lineParts, QString& errorString, int lineNumber);
public:
    FileOperator();
    bool loadObjFile(const QString& fileName, QString& errorString);
};

#endif // FileLoader_H
