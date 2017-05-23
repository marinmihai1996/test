#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QWidget>
#include "Client.h"
namespace Ui {
class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChat(Client *mClient,QWidget *parent = 0);
    ~GroupChat();

private:
    Ui::GroupChat *ui;
	Client *myClient;

};

#endif // GROUPCHAT_H
