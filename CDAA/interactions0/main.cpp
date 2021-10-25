#include <QApplication>

#include "mainwidget.h"
#include "affichage.h"
#include <QObject>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//un widget tout simple (vide)
	mainWidget w;
    Affichage affichage;
	w.show();
    affichage.show();

    QObject::connect(&w,SIGNAL(Text(QString)),&affichage,SLOT(recvData(QString)));

	return a.exec();
}
