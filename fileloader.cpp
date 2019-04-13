#include "fileloader.h"
#include <QFile>
#include <QRegularExpression>
#include <QVector3D>

FileLoader::FileLoader() {}

void FileLoader::parseobjfile(const QString& filename) {
    //QFile f(":/obj_files/cube.obj");
    QFile file(filename);
    if (file.exists() && (file.open(QFile::ReadOnly | QFile::Text))) {
        while (!file.atEnd()) {
            QString line = file.readLine().simplified();
            QStringList lineParts = line.split(QRegExp("\\s+"));
            if(lineParts.count() > 0) {
                QString firstchar = lineParts.at(0);
                if(firstchar.compare("v", Qt::CaseInsensitive) == 0) {
                    v.append(QVector3D(lineParts.at(1).toFloat(),
                    lineParts.at(2).toFloat(),
                    lineParts.at(3).toFloat()));
                } else if (firstchar.compare("vt", Qt::CaseInsensitive) == 0) {
                    vt.append(QVector2D(lineParts.at(1).toFloat(),
                    lineParts.at(2).toFloat()));
                } else if (firstchar.compare("f", Qt::CaseInsensitive) == 0) {
                    QStringList first = lineParts.at(1).split("/");
                    QStringList second = lineParts.at(2).split("/");
                    QStringList third = lineParts.at(3).split("/");
                    f_v.append(QVector3D(first.at(0).toFloat(),
                                         second.at(0).toFloat(),
                                         third.at(0).toFloat()));
                    f_vt.append(QVector3D(first.at(1).toFloat(),
                                         second.at(1).toFloat(),
                                         third.at(1).toFloat()));

                }
            }
        }
    }
}
