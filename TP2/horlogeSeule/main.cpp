#include "horlogeseule.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HorlogeSeule w;
	w.show();

	return a.exec();
}
