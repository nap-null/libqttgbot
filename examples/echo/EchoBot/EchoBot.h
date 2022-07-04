#pragma once

#include <Bot.h>


class EchoBot : public tgbot::Bot
{
    Q_OBJECT

public:
    EchoBot(const QString& token, QObject* parent);
    virtual ~EchoBot();

public slots:
    void start();
    void getUpdatesRecursively();

private:
    quint64 lastReceivedUpdateId;
};
