#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include "dialoggroup.h"
#include "Client.h"
#include <QDialog>
namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(Client* mClient, QWidget *parent = 0);
    ~MainDialog();

private slots:
    void on_Groups_activated(const QString &arg1);


    void on_NumeGrup_returnPressed();
	void on_pushButton_clicked();

    void on_Messages_activated(const QString &arg1);

    void on_Invitations_activated(const QString &arg1);
	void on_Invitations_activated(int index);
private:
	Client* myClient;
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
