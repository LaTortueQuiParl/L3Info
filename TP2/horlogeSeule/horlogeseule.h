#ifndef HORLOGESEULE_H
#define HORLOGESEULE_H

#include <QWidget>

#include <QLabel>
#include <QLabel>
#include <QPushButton>


class HorlogeSeule : public QWidget
{
	Q_OBJECT
private:
	unsigned compteur;

public:
	HorlogeSeule(QWidget *parent = 0);
	~HorlogeSeule();

	QLabel * texte;
	QLabel * valeur;

	QPushButton *start, *stop;
};

#endif // HORLOGESEULE_H
