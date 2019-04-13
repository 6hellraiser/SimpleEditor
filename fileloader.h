#ifndef FileLoader_H
#define FileLoader_H

#include <QString>
#include <QVector>
#include <QVector3D>
#include <QVector2D>


namespace ObjReader {
    class FileLoader;
}

class FileLoader {
private:
    QVector<QVector3D> v;
    QVector<QVector2D> vt; //can be QVector3D
    QVector<QVector3D> f_v;
    QVector<QVector3D> f_vt;
public:
    FileLoader();
    void parseobjfile(const QString &filename);
};

#endif // FileLoader_H
