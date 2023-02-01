#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPair>

#include <BotApi/AccessManager.h>
#include <Reply/Reply.h>

#include "Bot.h"


namespace tgbot
{

class BotPrivate
{
public:
    BotPrivate(Bot* bot, const QString& token)
      : pAC(new api::AccessManager(token, bot))
    {
    }

    virtual ~BotPrivate() {
        delete pAC;
    }

    QNetworkRequest get(const QString& url, Reply** reply) {
        return pAC->get(url, reply);
    }

    QNetworkRequest get(const QString& url, const QMap<QString, QString>& args, Reply** reply) {
        return pAC->get(url, args, reply);
    }

    QNetworkRequest post(
        const QString& url,
        const QMap<QString, QString>& args,
        Reply** reply
    )
    {
        return pAC->post(url, args, reply);
    }

    api::AccessManager* pAC;
};

#define P (this->m_pPrivate)

Bot::Bot(const QString &token, QObject* parent)
  : QObject(parent),
    m_pPrivate(new BotPrivate(this, token))
{
}

Bot::~Bot() {
    delete m_pPrivate;
}

QPair<QNetworkRequest, Reply*> Bot::sendMessage(qint64 chatId, const QString& msgText) {
    Message message {
        .text = msgText,
        .chat = Chat { .id = chatId },
    };

    return sendMessage(message);
}

QPair<QNetworkRequest, Reply*> Bot::sendMessage(const Message& message) {
    Reply* reply = nullptr;

    auto requestUrl = QString("/sendMessage");

    QMap<QString, QString> args {
        { "text", message.text },
        { "chat_id", QString::number(message.chat.id) },
    };

    auto request = P->post(requestUrl, args, &reply);

    return QPair<QNetworkRequest, Reply*> { request, reply };
}

QNetworkRequest Bot::getUpdates(
    quint64 offset,
    quint64 timeout,
    const std::function<void(const QList<Update>& updates)>& resultCallback
)
{
    Reply* reply = nullptr;
    // TODO: Compose requestUrl the right way.
    auto requestUrl = QString("/getUpdates");
    QStringList requestUrlArgs;
    if (offset != 0)
        requestUrlArgs.append(QString("offset=%1").arg(offset));
    if (timeout != 0)
        requestUrlArgs.append(QString("timeout=%1").arg(timeout));
    if (!requestUrlArgs.isEmpty())
        requestUrl += "?" + requestUrlArgs.join('&');
    auto request = P->get(requestUrl, &reply);

    connect(reply, &Reply::finished, [=]() {
        QVariant statusCode = reply->statusCode();

        if (statusCode.isValid()) {
            if (statusCode.toInt() == 200) {
                auto jsonReply = QJsonDocument::fromJson(reply->readAll()).object();

                qDebug() << jsonReply;

                if (jsonReply["ok"].toBool()) {
                    auto jsonMsgArray = jsonReply["result"].toArray();

                    QList<Update> updates;

                    for (auto jsonMsgValue : jsonMsgArray) {
                        auto jsonMsg = jsonMsgValue.toObject();
                        Update update = Update::fromJsonObject(jsonMsg);

                        updates.push_back(update);
                    }

                    resultCallback(updates);
                }
            }
        }

        reply->deleteLater();
    });

    return request;
}

}
