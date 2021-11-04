#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
//#include <QPushButton>
//#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *lab;
    //QPushButton *b;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connexionBDD();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //QSqlDatabase db;
};
#endif // MAINWINDOW_H
