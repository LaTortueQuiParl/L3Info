#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->db = new GestionBDD();

    this->setupModel("Contact",
                     QStringList() << "Id"
                                   << "Nom"
                                   << "Prenom"
                                   << "Entreprise"
                                   << "Telephone"
                                   << "Photo"
                                   << "Mail",
                     this->modelContact
                     );
    this->setupModel("Interaction",
                     QStringList() << "Id"
                                   << "Contenu"
                                   << "DateCreation"
                                   << "idContact",
                     modelInteraction
                     );
    this->setupModel("Todo",
                     QStringList() << "Id"
                                   << "Contenu"
                                   << "Deadline"
                                   << "idInteraction",
                     modelTodo
                     );
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

GestionBDD *MainWindow::getDb() const
{
    return db;
}

void MainWindow::setupModel(const QString table, QStringList attributs, QSqlTableModel *(&model)){
    model = new QSqlTableModel(this);
    model->setTable(table);
    for (int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i, Qt::Horizontal, attributs[j]);
    }
}

void MainWindow::createUI()
{
    ui->tableViewContact->setModel(modelContact);
    //ui->tableViewContact->setColumnHidden(0, true);
    ui->tableViewContact->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewContact->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableViewInteraction->setModel(modelInteraction);
    ui->tableViewInteraction->setColumnHidden(0, true);
    ui->tableViewInteraction->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewInteraction->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableViewTodo->setModel(modelTodo);
    ui->tableViewTodo->setColumnHidden(0, true);
    ui->tableViewTodo->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewTodo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    modelContact->select();
    modelInteraction->select();
    modelTodo->select();
}
