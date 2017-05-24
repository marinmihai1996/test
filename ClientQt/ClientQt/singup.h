#ifndef SINGUP_H
#define SINGUP_H
#include"Client.h"
#include <QDialog>

namespace Ui {
class SingUp;
}

class SingUp : public QDialog
{
    Q_OBJECT

public:
    explicit SingUp(Client* mClient,QWidget *parent = 0);
    ~SingUp();

private slots:
    void on_pushButton_clicked();

private:
	Client *myClient;
    Ui::SingUp *ui;
};

#endif // SINGUP_H
