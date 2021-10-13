/********************************************************************************
** Form generated from reading UI file 'CreationContact.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATIONCONTACT_H
#define UI_CREATIONCONTACT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *nomLabel;
    QLineEdit *nomLineEdit;
    QLabel *prNomLabel;
    QLineEdit *prNomLineEdit;
    QLabel *entrepriseLabel;
    QLineEdit *entrepriseLineEdit;
    QLabel *mailLabel;
    QLineEdit *mailLineEdit;
    QLabel *tLPhoneLabel;
    QLineEdit *tLPhoneLineEdit;
    QLabel *dateCrAtionLabel;
    QDateTimeEdit *dateCrAtionDateTimeEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->setEnabled(true);
        Dialog->resize(306, 296);
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 230, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        formLayoutWidget = new QWidget(Dialog);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 281, 211));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nomLabel = new QLabel(formLayoutWidget);
        nomLabel->setObjectName(QString::fromUtf8("nomLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nomLabel);

        nomLineEdit = new QLineEdit(formLayoutWidget);
        nomLineEdit->setObjectName(QString::fromUtf8("nomLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nomLineEdit);

        prNomLabel = new QLabel(formLayoutWidget);
        prNomLabel->setObjectName(QString::fromUtf8("prNomLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, prNomLabel);

        prNomLineEdit = new QLineEdit(formLayoutWidget);
        prNomLineEdit->setObjectName(QString::fromUtf8("prNomLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, prNomLineEdit);

        entrepriseLabel = new QLabel(formLayoutWidget);
        entrepriseLabel->setObjectName(QString::fromUtf8("entrepriseLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, entrepriseLabel);

        entrepriseLineEdit = new QLineEdit(formLayoutWidget);
        entrepriseLineEdit->setObjectName(QString::fromUtf8("entrepriseLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, entrepriseLineEdit);

        mailLabel = new QLabel(formLayoutWidget);
        mailLabel->setObjectName(QString::fromUtf8("mailLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, mailLabel);

        mailLineEdit = new QLineEdit(formLayoutWidget);
        mailLineEdit->setObjectName(QString::fromUtf8("mailLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, mailLineEdit);

        tLPhoneLabel = new QLabel(formLayoutWidget);
        tLPhoneLabel->setObjectName(QString::fromUtf8("tLPhoneLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, tLPhoneLabel);

        tLPhoneLineEdit = new QLineEdit(formLayoutWidget);
        tLPhoneLineEdit->setObjectName(QString::fromUtf8("tLPhoneLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, tLPhoneLineEdit);

        dateCrAtionLabel = new QLabel(formLayoutWidget);
        dateCrAtionLabel->setObjectName(QString::fromUtf8("dateCrAtionLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, dateCrAtionLabel);

        dateCrAtionDateTimeEdit = new QDateTimeEdit(formLayoutWidget);
        dateCrAtionDateTimeEdit->setObjectName(QString::fromUtf8("dateCrAtionDateTimeEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, dateCrAtionDateTimeEdit);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        nomLabel->setText(QApplication::translate("Dialog", "Nom", nullptr));
        prNomLabel->setText(QApplication::translate("Dialog", "Pr\303\251nom", nullptr));
        entrepriseLabel->setText(QApplication::translate("Dialog", "Entreprise", nullptr));
        mailLabel->setText(QApplication::translate("Dialog", "Mail", nullptr));
        tLPhoneLabel->setText(QApplication::translate("Dialog", "T\303\251l\303\251phone", nullptr));
        dateCrAtionLabel->setText(QApplication::translate("Dialog", "DateCr\303\251ation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATIONCONTACT_H
