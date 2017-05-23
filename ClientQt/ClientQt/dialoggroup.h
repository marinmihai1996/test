#pragma once
#ifndef DIALOGGROUP_H
#define DIALOGGROUP_H

#include <QDialog>
#include <QLineEdit>
#include "dialogprivate.h"
#include "adminoptions.h"
#include "Client.h"
namespace Ui {
class DialogGroup;
}


class DialogGroup : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGroup(Client* mClient,const QString &arg1,QWidget *parent = 0);
    ~DialogGroup();
private slots:
     void repeat();


    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_sendButton_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_comboBox_3_activated(const QString &arg1);

    void on_adminButton_clicked();

    void on_adminButton_2_clicked();



private:
	Client *myClient;
     DialogPrivate* mDialogPrivate;
     QString OutChat;
	 QString mGroupName;
	 AdminOptions *mAdmin;
    Ui::DialogGroup *ui;
	QTimer* timer;
public: void afiseazaText(std::string text);
};

#endif // DIALOGGROUP_H
