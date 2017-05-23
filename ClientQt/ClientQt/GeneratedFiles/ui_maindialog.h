/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

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

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *Invitations;
    QComboBox *Groups;
    QLabel *label_3;
    QLineEdit *NumeGrup;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QStringLiteral("MainDialog"));
        MainDialog->resize(532, 270);
        pushButton = new QPushButton(MainDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 40, 181, 41));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QStringLiteral("font: 14pt \"MS Shell Dlg 2\";"));
        QIcon icon;
        icon.addFile(QStringLiteral("Group.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(16, 16));
        pushButton->setAutoDefault(false);
        label = new QLabel(MainDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 180, 171, 41));
        label->setStyleSheet(QStringLiteral("font: 14pt \"MS Shell Dlg 2\";"));
        Invitations = new QComboBox(MainDialog);
        Invitations->setObjectName(QStringLiteral("Invitations"));
        Invitations->setGeometry(QRect(230, 180, 281, 41));
        Invitations->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        Groups = new QComboBox(MainDialog);
        Groups->setObjectName(QStringLiteral("Groups"));
        Groups->setGeometry(QRect(230, 110, 281, 41));
        Groups->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        label_3 = new QLabel(MainDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 110, 171, 41));
        label_3->setStyleSheet(QStringLiteral("font: 14pt \"MS Shell Dlg 2\";"));
        NumeGrup = new QLineEdit(MainDialog);
        NumeGrup->setObjectName(QStringLiteral("NumeGrup"));
        NumeGrup->setGeometry(QRect(230, 40, 281, 41));
        NumeGrup->setStyleSheet(QStringLiteral("font: 14pt \"MS Shell Dlg 2\";"));
        QWidget::setTabOrder(Invitations, pushButton);

        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainDialog", "Create Group", Q_NULLPTR));
        label->setText(QApplication::translate("MainDialog", "Your Invitations:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainDialog", "Your Groups:", Q_NULLPTR));
        NumeGrup->setText(QApplication::translate("MainDialog", "Choose a name for your group", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
