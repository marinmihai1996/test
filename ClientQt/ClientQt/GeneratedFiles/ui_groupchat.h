/********************************************************************************
** Form generated from reading UI file 'groupchat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPCHAT_H
#define UI_GROUPCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupChat
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *GroupChat)
    {
        if (GroupChat->objectName().isEmpty())
            GroupChat->setObjectName(QStringLiteral("GroupChat"));
        GroupChat->resize(400, 300);
        pushButton = new QPushButton(GroupChat);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 40, 261, 91));

        retranslateUi(GroupChat);

        QMetaObject::connectSlotsByName(GroupChat);
    } // setupUi

    void retranslateUi(QWidget *GroupChat)
    {
        GroupChat->setWindowTitle(QApplication::translate("GroupChat", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("GroupChat", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GroupChat: public Ui_GroupChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPCHAT_H
