#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QTextStream>

namespace ObjectModel {

class Object {

public:
    QVector<QVector3D> v;
    QVector<QVector2D> vt;
    QVector<int> fv;
    QVector<int> fvIndices;
    QVector<int> fvt;
    QVector<int> fvtIndices;
};

}

#endif // OBJECTMODEL_H
