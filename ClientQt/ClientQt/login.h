#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QLineEdit>
#include"Client.h"

namespace Ui {
class LogIn;
}

class LogIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogIn(Client* mClient,QWidget *parent = 0);
    ~LogIn();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionExit_triggered();

    void on_actionSing_Up_triggered();


private:
	Client* myClient;
    Ui::LogIn *ui;

};

#endif // LOGIN_H
