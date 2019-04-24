#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //qDebug() << arg1;
    if (QString::compare(arg1, "Open...") == 0) {
        ObjReader::FileOperator fo;
        ObjectModel::Object obj;
        QString errorString;
        if (!fo.loadObjFile(":/obj_files/cube.obj", errorString, obj)) {
            QMessageBox messageBox;
            messageBox.critical(this, "Error", errorString);
            messageBox.setFixedSize(500,200);
            //fl.parseobjfile()
        }
        ui->comboBox->setCurrentIndex(0);
    }
}
