#include "fileoperator.h"
#include <QFile>
#include <QRegularExpression>
#include <QVector3D>


FileOperator::FileOperator() {}

bool FileOperator::loadObjFile(const QString& fileName, QString& errorString) {
    //QFile f(":/obj_files/cube.obj");
    QFile file(fileName);
    if (file.exists() && (file.open(QFile::ReadOnly | QFile::Text))) {
        QTextStream textStream(&file);
        QString es;
        if (!parseObjFile(textStream, es)) {
            errorString = es;
            return false;
        }
    } else {
        errorString = "The file " + fileName + " does not exist or not a text file";
        return false;
    }
    return true;
}

bool FileOperator::parseV(QStringList lineParts, QString& errorString, int lineNumber) {
    bool ok1, ok2, ok3;
    float first = lineParts.at(1).toFloat(&ok1);
    float second = lineParts.at(2).toFloat(&ok2);
    float third = lineParts.at(3).toFloat(&ok3);
    if (ok1 && ok2 && ok3)
        v.append(QVector3D(first, second, third));
    else {
        QString output = QString::number(lineNumber);
        errorString = "Could not convert line " + output + " to float.";
        return false;
    }
    return true;
}

bool FileOperator::parseF(QStringList lineParts, QString& errorString, int lineNumber) {
    QStringList first = lineParts.at(1).split("/");
    QStringList second = lineParts.at(2).split("/");
    QStringList third = lineParts.at(3).split("/");
    f_v.append(QVector3D(first.at(0).toFloat(),
                         second.at(0).toFloat(),
                         third.at(0).toFloat()));
    f_vt.append(QVector3D(first.at(1).toFloat(),
                         second.at(1).toFloat(),
                         third.at(1).toFloat()));

    return true;
}

bool FileOperator::parseVT(QStringList lineParts, QString& errorString, int lineNumber){
    bool ok1, ok2;
    float first = lineParts.at(1).toFloat(&ok1);
    float second = lineParts.at(2).toFloat(&ok2);
    if (ok1 && ok2)
        vt.append(QVector2D(first, second));
    else {
        QString output = QString::number(lineNumber);
        errorString = "Could not convert line " + output + " to float.";
        return false;
    }
    return true;
}

bool FileOperator::parseObjFile(QTextStream& textStream, QString& errorString) {
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
            if (!parseV(lineParts, errorString, lineNumber))
                return false;
        } else if (firstchar.compare("vt", Qt::CaseInsensitive) == 0) {
            if (!parseVT(lineParts, errorString, lineNumber))
                return false;
        } else if (firstchar.compare("f", Qt::CaseInsensitive) == 0 ) {
            if (!parseF(lineParts, errorString, lineNumber))
                return false;
        } else {
            errorString = "The first symbol in the line " + (QString)lineNumber + " is not identified";
            return false;
        }
    }
    return true;
}
