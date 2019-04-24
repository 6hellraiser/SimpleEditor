#include "fileoperator.h"
#include <QFile>
#include <QRegularExpression>
#include <QVector3D>


bool ObjReader::FileOperator::loadObjFile(const QString& fileName, QString& errorString, ObjectModel::Object& obj) {
    //QFile f(":/obj_files/cube.obj");
    QFile file(fileName);
    if (file.exists() && (file.open(QFile::ReadOnly | QFile::Text))) {
        QTextStream textStream(&file);
        QString es;
        if (!parseObjStream(textStream, es, obj)) {
            errorString = es;
            return false;
        }
    } else {
        errorString = "The file " + fileName + " does not exist or not a text file";
        return false;
    }
    return true;
}

bool ObjReader::FileOperator::parseV(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber) {
    bool ok1, ok2, ok3;
    float first = lineParts.at(1).toFloat(&ok1);
    float second = lineParts.at(2).toFloat(&ok2);
    float third = lineParts.at(3).toFloat(&ok3);
    if (ok1 && ok2 && ok3)
        obj.v.append(QVector3D(first, second, third));
    else {
        QString output = QString::number(lineNumber);
        errorString = "Could not convert line " + output + " to float.";
        return false;
    }
    return true;
}

bool ObjReader::FileOperator::parseF(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber) {

    if (obj.fv.size() == 0) obj.fvIndices.push_back(0);
    if (obj.fvt.size() == 0) obj.fvtIndices.push_back(0);
    if (lineParts.size() == 1) {
        QString output = QString::number(lineNumber);
        errorString = "An empty f line with number " + output + " occured.";
        return false;
    }
    for (auto partIt = lineParts.begin() + 1; partIt != lineParts.end(); partIt++) {
        QStringList coords = partIt->split("/");
        bool ok1, ok2 = false;
        int first, second;
        if (coords.size() == 3 && coords[0] != "") {
            first = coords.at(0).toInt(&ok1);
            if (coords[1] != "") second = coords.at(1).toInt(&ok2);
        } else {
            QString output = QString::number(lineNumber);
            errorString = "Inapropriate line structure in the line " + output + ".";
            return false;
        }

        QString output = QString::number(lineNumber);
        errorString = "Could not convert line " + output + " to int.";
        if (ok2) {
            if (obj.fvt.size() == 0 && obj.fv.size() != 0) return false;
            else obj.fvt.push_back(second);
        } else {
            if (obj.fvt.size() != 0) return false;
        }
        if (ok1) obj.fv.push_back(first);
        else return false;
    }
    obj.fvIndices.push_back(obj.fv.size());
    obj.fvtIndices.push_back(obj.fvt.size()); //any point in having that vector?

    return true;
}

bool ObjReader::FileOperator::parseVT(QStringList lineParts, QString& errorString, ObjectModel::Object& obj, int lineNumber){
    bool ok1, ok2;
    float first = lineParts.at(1).toFloat(&ok1);
    float second = lineParts.at(2).toFloat(&ok2);
    if (ok1 && ok2)
        obj.vt.append(QVector2D(first, second));
    else {
        QString output = QString::number(lineNumber);
        errorString = "Could not convert line " + output + " to float.";
        return false;
    }
    return true;
}

bool ObjReader::FileOperator::parseObjStream(QTextStream& textStream, QString& errorString, ObjectModel::Object& obj) {
    //not sure if there is a need in alert if the file is empty
    int lineNumber = 0;
    while (!textStream.atEnd()) {
        QString line = textStream.readLine().simplified();
        lineNumber++;
        if(line.compare("") == 0) continue;
        QStringList lineParts = line.split(QRegExp("\\s+"));
        QString firstchar = lineParts.at(0);
        if(firstchar.compare("v", Qt::CaseInsensitive) == 0) {
            //bool success = succsess && parseV(lineParts, errorString, lineNumber) == false
            if (!parseV(lineParts, errorString, obj, lineNumber))
                return false;
        } else if (firstchar.compare("vt", Qt::CaseInsensitive) == 0) {
            if (!parseVT(lineParts, errorString, obj, lineNumber))
                return false;
        } else if (firstchar.compare("f", Qt::CaseInsensitive) == 0 ) {
            if (!parseF(lineParts, errorString, obj, lineNumber))
                return false;
        } else {
            //errorString = "The first symbol in the line " + (QString)lineNumber + " is not identified";
            //return false;
            continue; //in case we have an appropriate symbol for an obj file, but cannot recognize it.
        }
    }
    return true;
}
