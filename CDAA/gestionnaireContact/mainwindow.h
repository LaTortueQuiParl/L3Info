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
    QSqlTableModel *modelInteraction;
    QSqlTableModel *modelTodo;
    // Voir QSqlTableModel pour afficher la bdd dans qt

public:
    /**
     * @brief MainWindow le constructeur de MainWindow qui initialize l'ui
     * @param parent le parent de mainwindow qui est nullptr
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * Le destructeur de mainwindow qui détruit aussi l'ui
     */
    ~MainWindow();
    /**
     * @brief setupModel permet paramétrer correctement les QSqlTableModel
     * @param table La table que l'on veut visualiser
     * @param attributs Les attributs de la table que l'on veut visualiser
     */
    void setupModel(const QString table, QStringList attributs, QSqlTableModel *(&model));
    /**
     * @brief createUI création des tables dans la mainwindow
     */
    void createUI();
    GestionBDD *getDb() const;
};
#endif // MAINWINDOW_H
