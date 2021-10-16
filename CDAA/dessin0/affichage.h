#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QLCDNumber>
#include <QHBoxLayout>


class Affichage : public QWidget
{
	Q_OBJECT
public:
	explicit Affichage(QWidget *parent = nullptr);
	QTextEdit * zoneTexte;
	QLCDNumber * LCDnbEvents;
	QHBoxLayout * Hlayout;
	int nbEvents;

signals:
	void LCDupdate(int);
	void textAppend(QString);

public slots:
	void recvData(QString);
};

#endif // AFFICHAGE_H
