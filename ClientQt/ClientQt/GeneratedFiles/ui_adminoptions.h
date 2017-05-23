/********************************************************************************
** Form generated from reading UI file 'adminoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINOPTIONS_H
#define UI_ADMINOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminOptions
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QWidget *tab_2;
    QComboBox *comboBox_3;
    QLabel *label_4;
    QPushButton *pushButton;

    void setupUi(QDialog *AdminOptions)
    {
        if (AdminOptions->objectName().isEmpty())
            AdminOptions->setObjectName(QStringLiteral("AdminOptions"));
        AdminOptions->resize(300, 400);
        tabWidget = new QTabWidget(AdminOptions);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(-1, -1, 302, 402));
        tabWidget->setStyleSheet(QLatin1String("font: 12pt \"MS Shell Dlg 2\";\n"
"background-color: rgb(238, 238, 238);"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(30, 140, 231, 31));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 110, 231, 21));
        comboBox_2 = new QComboBox(tab);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(30, 230, 231, 31));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 200, 231, 21));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 10, 251, 31));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(50, 50, 171, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        comboBox_3 = new QComboBox(tab_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(30, 60, 231, 31));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 30, 231, 21));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 210, 241, 101));
        pushButton->setStyleSheet(QLatin1String("font: 26pt \"Microsoft JhengHei UI\";\n"
"background-color: rgb(255, 0, 0);"));
        pushButton->setAutoDefault(false);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(AdminOptions);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AdminOptions);
    } // setupUi

    void retranslateUi(QDialog *AdminOptions)
    {
        AdminOptions->setWindowTitle(QApplication::translate("AdminOptions", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("AdminOptions", "Remove Member", Q_NULLPTR));
        label_2->setText(QApplication::translate("AdminOptions", "Promote Member To Admin", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("AdminOptions", "Send Invite", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AdminOptions", "Admin", Q_NULLPTR));
        label_4->setText(QApplication::translate("AdminOptions", "Remove Admin Rights", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AdminOptions", "Delete Group", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AdminOptions", "Owner", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AdminOptions: public Ui_AdminOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINOPTIONS_H
