#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QListWidgetItem>

#include "gestionbdd.h"
#include "gestioncontacts.h"
#include "gestioninteractions.h"
#include "gestiontodos.h"

#include "ajoutcontactdialog.h"
#include "ajoutinteractiondialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    GestionBDD *db;
    GestionContacts* gestCont;
    GestionInteractions* gestInter;
    GestionTodos* gestTodos;
    Contact* contactCourant;
    Interaction* interactionCourant;
    QString imgContact;

    AjoutContactDialog* acd;
    ajoutInteractionDialog* aid;

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
     * @brief getDb retroune la base de donnée active
     * @return db
     */
    GestionBDD *getDb() const;

    /**
     * @brief remplissageListContact affiche tout les contacts dans la liste de contact
     */
    void remplissageListContact();
    /**
     * @brief remplissageListInteraction affiche Toutes les interactions dans la liste d'interaction
     */
    void remplissageListInteraction();

public slots:
    void modifPPButton();
    void recherchContactButton();
    void retourWidgetContact();
    void saveModif();
    void suppContact();
    void ouvrirajoutContactDialog();
    void ouvrirajoutInteractionDialog();
    void suppInteraction();

private slots:
    void on_contactListWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_contactListWidget_itemClicked(QListWidgetItem* item);
    void on_InteractionListWidget_itemClicked(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
