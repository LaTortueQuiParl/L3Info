#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QPushButton>
#include <string>
#include <QDebug>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStateMachine *qsm;
    std::vector<QState*> ls;
    std::vector<std::function<void()>> lf;
    QPushButton* bValider;
    unsigned compteur;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void fonction0();
     void fonction1();
     void fonction2();
     void fonction3();
     void fonction4();

public slots:
    void inc();
    void appelFonction();
    void raz();
};


#endif // MAINWINDOW_H
