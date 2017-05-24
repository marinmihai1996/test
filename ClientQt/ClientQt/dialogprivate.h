#ifndef DIALOGPRIVATE_H
#define DIALOGPRIVATE_H

#include <QDialog>
#include <QLineEdit>
#include"Client.h"
#include<QTgui>
namespace Ui {
class DialogPrivate;
}

class DialogPrivate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPrivate(Client* mClient, QString ClientName, QWidget *parent = 0);
    ~DialogPrivate();

private slots:
    void repeat();
    void on_pushButton_clicked();

private:
    Ui::DialogPrivate *ui;
	Client* myClient;
	QTimer* timer;
	QString OutChat;
	QString mUsername;
};

#endif // DIALOGPRIVATE_H
