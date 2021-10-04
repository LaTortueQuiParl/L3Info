#ifndef HORLOGESEULE_H
#define HORLOGESEULE_H

#include <QWidget>

#include <QLabel>
#include <QLabel>
#include <QPushButton>

#include <QTimer>

class HorlogeSeule : public QWidget
{
	Q_OBJECT
private:
	unsigned compteur;

	QLabel * texte;
	QLabel * valeur;

	QPushButton *start, *stop;

	QTimer * timer;

public:
	HorlogeSeule(QWidget *parent = 0);
	~HorlogeSeule();

signals:
	void finDecompte();

public slots:
	void updatingTimer();
	void demarrer();
	void arreter();

};

#endif // HORLOGESEULE_H
