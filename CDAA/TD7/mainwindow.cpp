#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ls.reserve(6);
    lf.reserve(6);
    compteur = 0;
    qsm = new QStateMachine(this);
    bValider = new QPushButton("bouton", this);

    for (int i = 0; i < 6; i++){
        ls.push_back(new QState());
    }

    lf.push_back(fonction0);
    lf.push_back(fonction1);
    lf.push_back(fonction2);
    lf.push_back(fonction3);
    lf.push_back(fonction4);


    for (auto it : ls){
        qsm->addState(it);
    }

    for (int i = 0; i < 6; i++){
        if (i != 0 && i != 5){
            ls.at(i)->addTransition(bValider, SIGNAL(clicked()), ls.at(i+1));
            QObject::connect(ls.at(i), SIGNAL(entered()), this, SLOT(inc()));
            QObject::connect(ls.at(i), SIGNAL(exited()), this, SLOT(appelFonction()));
        } else {
            ls.at(i)->addTransition(ls.at(i), SIGNAL(entered()), ls.at(1));
            QObject::connect(ls.at(i), SIGNAL(entered()), this, SLOT(raz()));
        }
    }

    qsm->setInitialState(ls.front());
    qsm->start();


}

MainWindow::~MainWindow()
{
}

void MainWindow::fonction0(){
    qDebug() << "fct0";
}

void MainWindow::fonction1(){
    qDebug() << "fct1";
}

void MainWindow::fonction2(){
    qDebug() << "fct2";
}

void MainWindow::fonction3(){
    qDebug() << "fct3";
}

void MainWindow::fonction4(){
    qDebug() << "fct4";
}

void MainWindow::inc(){
    compteur++;
}

void MainWindow::appelFonction(){
    lf.at(compteur)();
}

void MainWindow::raz(){
    compteur=0;
}
