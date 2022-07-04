#include <QTimer>
#include <QNetworkReply>

#include <Reply/Reply.h>

#include "EchoBot.h"


using namespace tgbot;


EchoBot::EchoBot(const QString& token, QObject* parent)
  : Bot(token, parent),
    lastReceivedUpdateId(0)
{}

EchoBot::~EchoBot() {}

void EchoBot::start() {
    QTimer::singleShot(0, this, &EchoBot::getUpdatesRecursively);
}

void EchoBot::getUpdatesRecursively() {
    getUpdates(lastReceivedUpdateId+1, 10, [=](const QList<Update>& updates) {
        qDebug() << "New messages count: " << updates.count();

        if (!updates.isEmpty())
            lastReceivedUpdateId = updates.last().id;

        for (auto update : updates) {
            qDebug() << "Message with text: " << update.message.text
                << " from chat: " << update.message.chat.id
                << " with type: " << update.message.type;

            const auto chatWithAlev = 535224657;

            if (update.message.type == Message::POST)
                sendMessage(chatWithAlev, update.message.text);
            else
                sendMessage(update.message.chat.id, update.message.text);
        }

        QTimer::singleShot(0, this, &EchoBot::getUpdatesRecursively);
    });
}
