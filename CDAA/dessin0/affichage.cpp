#include <QDebug>
#include "affichage.h"

Affichage::Affichage(QWidget *parent) : QWidget(parent)
{
	nbEvents = 0;

	Hlayout = new QHBoxLayout(this);

	zoneTexte = new QTextEdit(this);
	zoneTexte->setText ("");

	LCDnbEvents = new QLCDNumber(this);
	LCDnbEvents->setMinimumWidth (10);
	LCDnbEvents->setMaximumHeight(30);
	LCDnbEvents->setMode (QLCDNumber::Dec);

	LCDnbEvents->display (nbEvents);

	Hlayout->addWidget (zoneTexte);
	Hlayout->addWidget (LCDnbEvents);

	setLayout (Hlayout);

	QObject::connect (this, SIGNAL(textAppend(QString)), zoneTexte, SLOT(append(QString)));
}

void Affichage::recvData (QString s)
{
	nbEvents++;
	LCDnbEvents->display (nbEvents);
	emit textAppend(s);
}


