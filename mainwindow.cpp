#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

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

void MainWindow::on_actionEditer_triggered()
{
    QString nomFichier=QFileDialog::getOpenFileName(this,"gestion des Fichiers","/home/prostain","*.cpp");
    qDebug()<<nomFichier;
    QFile monFichier(nomFichier);
    if(monFichier.open(QFile::ReadOnly | QIODevice::Text ))
    {
        qDebug()<<"fichier ouvert";
        QTextStream in(&monFichier);
        while(!in.atEnd())
        {
            qDebug()<<"coucou";
            QString ligneLue=in.readLine();
            ui->textEdit->append(ligneLue);
        }
        monFichier.close();
    }
    else
    {
        statusBar()->showMessage("désolé, impossible d'ouvrir ce fichier");
    }

}

void MainWindow::on_actionSauvegarder_triggered()
{
    QFile monFichier(QFileDialog::getSaveFileName(this,"gestion des fichier","/home/prostain",".cpp"));
    monFichier.open(QFile::WriteOnly);
    QTextStream out(&monFichier);
    QStringList listeDesLiges=ui->textEdit->toPlainText().split("\n");
    for(int noLigne=0;noLigne<listeDesLiges.size();noLigne++)
    {
        out<<listeDesLiges[noLigne]<<endl;
    }
    monFichier.close();
}
