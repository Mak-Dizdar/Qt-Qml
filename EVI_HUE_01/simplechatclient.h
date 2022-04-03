#ifndef SIMPLECHATCLIENT_H
#define SIMPLECHATCLIENT_H

#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include "chatclientwebconnect.h"

class SimpleChatClient : public QMainWindow
{
    Q_OBJECT

public:
    SimpleChatClient(QWidget *parent = nullptr);
    ~SimpleChatClient();
public slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSendButtonClicked();
    void onStateButtonClicked();

private:
    chatclientwebconnect *m_chatClient;
    QLabel* headerLabel;
    QLabel* hostLabel;
    QLineEdit* serverAddressLineEdit;
    QTextEdit* chatWindowTextEdit;
    QLineEdit* usernameLineEdit;
    QLineEdit* messageLineEdit;
    QPushButton* connectPushButton;
    QPushButton* disconnectPushButton;
    QPushButton* statePushButton;
    QPushButton* sendPushButton;

    void handleConnect();
    void handleDisconnect();
    void handleMessageReceived(QString message);


};
#endif // SIMPLECHATCLIENT_H
