#ifndef ADMINOPTIONS_H
#define ADMINOPTIONS_H

#include <QDialog>
#include"Client.h"
namespace Ui {
class AdminOptions;
}

class AdminOptions : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOptions(Client* mClient, QString numeGrup, QWidget *parent = 0);
    ~AdminOptions();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_2_activated(const QString &arg1);
	void on_comboBox_3_activated(const QString &arg1);
	void on_comboBox_activated(int index);
	void on_comboBox_3_activated(int index);
	void on_pushButton_2_clicked();
	void on_pushButton_clicked();
private:
	Client* myClient;
    Ui::AdminOptions *ui;
	QString mGroupName;
};

#endif // ADMINOPTIONS_H
