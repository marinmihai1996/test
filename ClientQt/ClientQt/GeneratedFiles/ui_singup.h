/********************************************************************************
** Form generated from reading UI file 'singup.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGUP_H
#define UI_SINGUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SingUp
{
public:
    QLabel *imagine;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *SingUp)
    {
        if (SingUp->objectName().isEmpty())
            SingUp->setObjectName(QStringLiteral("SingUp"));
        SingUp->resize(800, 375);
        SingUp->setCursor(QCursor(Qt::ArrowCursor));
        imagine = new QLabel(SingUp);
        imagine->setObjectName(QStringLiteral("imagine"));
        imagine->setGeometry(QRect(0, 0, 400, 375));
        label_2 = new QLabel(SingUp);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 120, 261, 21));
        pushButton = new QPushButton(SingUp);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(550, 300, 130, 40));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QStringLiteral("font: 12pt \"MS Shell Dlg 2\";"));
        QIcon icon;
        icon.addFile(QStringLiteral("3D-Upload.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(16, 16));
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);
        label = new QLabel(SingUp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(480, 30, 261, 23));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::AutoText);
        lineEdit = new QLineEdit(SingUp);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(480, 60, 261, 41));
        lineEdit->setStyleSheet(QStringLiteral("font: 14pt \"Times New Roman\";"));
        lineEdit_3 = new QLineEdit(SingUp);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(480, 240, 261, 41));
        lineEdit_3->setStyleSheet(QStringLiteral("font: 14pt \"Times New Roman\";"));
        lineEdit_3->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(SingUp);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(480, 210, 171, 21));
        lineEdit_2 = new QLineEdit(SingUp);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(480, 150, 261, 41));
        lineEdit_2->setStyleSheet(QStringLiteral("font: 14pt \"Times New Roman\";"));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, pushButton);

        retranslateUi(SingUp);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(SingUp);
    } // setupUi

    void retranslateUi(QDialog *SingUp)
    {
        SingUp->setWindowTitle(QApplication::translate("SingUp", "Sing Up", Q_NULLPTR));
        imagine->setText(QString());
        label_2->setText(QApplication::translate("SingUp", "<html><head/><body><p><span style=\" font-size:14pt;\">Choose a Password:</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("SingUp", "Sing Up", Q_NULLPTR));
        label->setText(QApplication::translate("SingUp", "<html><head/><body><p><span style=\" font-size:14pt;\">Choose an Username:</span></p></body></html>", Q_NULLPTR));
        label_3->setText(QApplication::translate("SingUp", "<html><head/><body><p><span style=\" font-size:14pt;\">Repeat Password:</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SingUp: public Ui_SingUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGUP_H
