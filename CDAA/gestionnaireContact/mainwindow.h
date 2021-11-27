#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "gestionbdd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    GestionBDD *db;
    QSqlTableModel *modelContact;
    // Voir QSqlTableModel pour afficher la bdd dans qt

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupModel(const QString table, QStringList attributs);
    void createUI();
    GestionBDD *getDb() const;
};
#endif // MAINWINDOW_H
