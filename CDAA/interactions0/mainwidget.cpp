#include <QDebug>
#include "mainwidget.h"

void mainWidget::keyPressEvent(QKeyEvent * event)
{
//liste des touches possibles, avec le type QT
//https://doc.qt.io/qt-5/qt.html#Key-enum

	if( event->key() == Qt::Key_A )
	{
		qDebug() << "clavier -> touche A" ;
	}
	else
		qDebug() << "clavier -> autre ->" << event->text();

	//permet de ne pas faire remonter ce message clavier aux classes parentes
	event->setAccepted(true);
}

void mainWidget::mouseMoveEvent(QMouseEvent *event)
{
	//(0,0) en haut à gauche du widget
	qDebug() << "souris -> déplacement (position locale) ->" << event->localPos();
}

void mainWidget::mousePressEvent(QMouseEvent *event)
{
	qDebug() << "souris -> bouton pressé -> " << event->button();

}
mainWidget::mainWidget(QWidget *parent)
	: QWidget(parent)
{
	//on donne une taille par défaut à notre widget (en pixels) (largeur, hauteur)
	setFixedSize(300,300);
    ok = false;
    activDesac = new QPushButton("Activer le suivi de la souris",this);
    activDesac->setFixedSize(300,100);
    activDesac->setDisabled(false);
	//pour pouvoir suivre "en temps-réel" le déplacement de la souris
	//sinon nous n'aurons l'information que si un bouton est enfoncé
    setMouseTracking(false);

    QObject::connect(activDesac,SIGNAL(clicked()),this,SLOT(Pushed()));
    QObject::connect(this,SIGNAL(Change()),this,SLOT(Eradication()));
}

void mainWidget::Pushed(){
    ok = !ok;
    this->setMouseTracking(ok);
    emit Change();
}

void mainWidget::Eradication()
{
    if(ok)
        activDesac->setText("Tracking activated ! MWAHAHAH ! ^^");
    else
        activDesac->setText("Z'etes pas drôle :'(");
}
mainWidget::~mainWidget()
{

}
