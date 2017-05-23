#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Client.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
	explicit Dialog(QString NumeGrup, Client* mClient, QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
	Client *myClient;
	QString qs;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
