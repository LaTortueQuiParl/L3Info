#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QStatusBar>
#include "personne.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_validButton_clicked();

    void slot_aPropos();

    void Texto();

private:
    Ui::MainWindow *ui;
    Personne *p;
    QLabel *l;
    QTimer *t;
};
#endif // MAINWINDOW_H
