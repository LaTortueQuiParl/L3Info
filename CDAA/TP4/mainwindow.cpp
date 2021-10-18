#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p = new Personne();
    ui->menubar->addAction(ui->actionA_Propos);
    t = new QTimer(this);
    t->setInterval(10);
    t->start();
    connect(ui->actionA_Propos, SIGNAL(triggered(bool)), this, SLOT(slot_aPropos()));
    connect(ui->actionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(t,SIGNAL(timeout()),this,SLOT(Texto()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete p;
}


void MainWindow::on_validButton_clicked()
{
    p->setNom(ui->nomLineEdit->text().toStdString());
    p->setPrenom(ui->prNomLineEdit->text().toStdString());
    p->setVille(ui->villeLineEdit->text().toStdString());
    p->setDateNaissance(ui->dateDateTimeEdit->text().toStdString());

    ui->texteResultat->setText(QString::fromStdString(p->Affiche()));
}

void MainWindow::slot_aPropos()
{
    QMessageBox *messageAbout = new QMessageBox();
    messageAbout->about(this,"A Propos", "Cette magnifique application a été créée\navec QtDesigner.");
    delete messageAbout;
}

void MainWindow::Texto(){
    QTime timeValue;
    timeValue=QTime::currentTime ();
    QString format="H:m:s.z";
    ui->lab->setText (timeValue.toString (format));
    ui->statusbar->showMessage(timeValue.toString(format));
}
