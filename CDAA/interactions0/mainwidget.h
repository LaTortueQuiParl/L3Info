#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPushButton>

class mainWidget : public QWidget
{
	Q_OBJECT
private:
    QPushButton * activDesac;
    bool ok;
public:
	mainWidget(QWidget *parent = 0);
	~mainWidget();

	//on surcharge les fonctions d'un widget (cf doc QT)
	void keyPressEvent(QKeyEvent *);
	void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

public slots:
    void Pushed();
    void Eradication();
signals:
    void Change();
};

#endif // MAINWIDGET_H
