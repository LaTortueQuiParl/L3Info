#include <QDebug>
#include <QPainter>

#include "mainwidget.h"

void mainWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	QPen pen;
	  pen.setWidth(5);
	  pen.setBrush(Qt::blue);

    QVector<QLineF> segments;
    QPointF A, B;

    for (QVector<QPointF>::iterator i = mousePoint.begin(); i < mousePoint.end() - 1; ++i) {
        A = *i;
        B = *(i+1);

        QLineF l;
        l.setPoints(A, B);
        segments.append(l);
    }

	painter.setPen(pen);
    painter.drawPoints (mousePoint.data(), mousePoint.size());
    painter.drawLines(segments);
    //qDebug() << "paint";
}

void mainWidget::keyPressEvent(QKeyEvent * event)
{
//liste des touches possibles, avec le type QT
//https://doc.qt.io/qt-5/qt.html#Key-enum
QString s = "clavier -> ";

	if ( event->key() == Qt::Key_A )
	{
		//qDebug() << "clavier -> touche A" ;
		s.append("touche A");
	}
	else if (event->key() == Qt::Key_F1 )
	{
		//qDebug() << "clavier -> touche A" ;
		s.append("touche F1");
	}
	else
	{
		//qDebug() << "clavier -> autre ->" << event->text();
		s.append("autre -> ");
		s.append(event->text ());
	}

	emit newEvent(s);
}

void mainWidget::mouseMoveEvent(QMouseEvent *event)
{
	QString s = "souris -> ";

	//(0,0) en haut à gauche du widget
	//qDebug() << "souris -> déplacement (position locale) ->" << event->localPos();

	s.append("déplacement -> (localPos)");
	s += "[";
	QString n;
	n.setNum (event->x ());
	s += n;
	s += " ";
	n.setNum (event->y ());
	s += n;
	s += "]";
	emit newEvent(s);
}

void mainWidget::mousePressEvent(QMouseEvent *event)
{
	QString s = "souris ->";

	//qDebug() << "souris -> bouton pressé -> " << event->buttons();
	s.append ("bouton pressé -> ");
	switch (event->button())
	{
		case Qt::LeftButton:
			s += "gauche";
			break;
		case Qt::RightButton:
			s += "droite";
			break;
		case Qt::MiddleButton:
			s +="milieu";
			break;
		default:
			s +="non identifié";
	}

	emit newEvent(s);
    mousePoint.append(event->localPos ());
	update ();
}

void mainWidget::modifyTrackingMode(const bool &v)
{
	setMouseTracking(v);
	emit b_MouseTracking_update(v);
}

void mainWidget::toggleMouseTracking()
{
	mouseTracking = !mouseTracking;
	modifyTrackingMode(mouseTracking);
}

void mainWidget::update_BMouseTracking(bool b)
{
	if (b == true)
		b_toggleMouseTracking -> setText("Désactiver le suivi de la souris");
	else
		b_toggleMouseTracking -> setText("Activer le suivi de la souris");
}

mainWidget::mainWidget(QWidget *parent)
	: QWidget(parent)
{
	//pour pouvoir suivre "en temps-réel" le déplacement de la souris
	//sinon nous n'aurons l'information que si un bouton est enfoncé
	//setMouseTracking(true);

	setFixedSize(300,300);
	b_toggleMouseTracking = new QPushButton("", this);

	QObject::connect(b_toggleMouseTracking, SIGNAL(clicked()), this, SLOT(toggleMouseTracking()));
	QObject::connect(this, SIGNAL(b_MouseTracking_update(bool)), this, SLOT(update_BMouseTracking(bool)));

	b_toggleMouseTracking->setFixedSize(300,100);
	b_toggleMouseTracking->setDisabled(true);

	mouseTracking = false; //pas de suivi en temps-réel par défaut de la souris
	modifyTrackingMode(mouseTracking);

	b_toggleMouseTracking->setDisabled(false);
}

mainWidget::~mainWidget()
{

}
