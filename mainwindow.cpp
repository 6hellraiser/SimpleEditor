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
        FileOperator fo;
        QString errorString;
        if (!fo.loadObjFile(":/obj_files/cube.obj", errorString)) {
            QMessageBox messageBox;
            messageBox.critical(0,"Error", errorString);
            messageBox.setFixedSize(500,200);
            ui->comboBox->setCurrentIndex(0);
            //fl.parseobjfile()
        }
    }
}
