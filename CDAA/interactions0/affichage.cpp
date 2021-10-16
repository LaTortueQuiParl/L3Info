#include "affichage.h"
#include <QDebug>

Affichage::Affichage(QWidget *parent)
    : QWidget(parent)
{
    //on donne une taille par défaut à notre widget (en pixels) (largeur, hauteur)
    setFixedSize(300,300);

    nbEvents = 0;
    zoneTexte = new QTextEdit();
    LCDnbEvents = new QLCDNumber();
    Hlayout = new QHBoxLayout(this);
    LCDnbEvents->setMode (QLCDNumber::Dec);

    Hlayout->addWidget(zoneTexte);
    Hlayout -> addWidget(LCDnbEvents);
    LCDnbEvents->setMinimumWidth(10);
    LCDnbEvents->setMaximumHeight(30);
    QObject::connect(this, SIGNAL(textAppend(QString)), zoneTexte, SLOT(append(QString)));
}

void Affichage::recvData(QString s){
    this->nbEvents++;
    emit textAppend(s);
    qDebug() << "Number of events :" << nbEvents;
    LCDnbEvents->display(nbEvents);
}
