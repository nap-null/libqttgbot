#pragma once

#include <QObject>
#include <QString>
#include <QNetworkRequest>

#include <Update/Update.h>


namespace tgbot
{

class BotPrivate;
class Reply;

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(const QString& token, QObject* parent = nullptr);
    virtual ~Bot();

public:
    QPair<QNetworkRequest, Reply*> sendMessage(qint64 chatId, const QString& msgText);
    QPair<QNetworkRequest, Reply*> sendMessage(const Message& message);

    QNetworkRequest getUpdates(
        quint64 offset,
        quint64 timeout,
        // TODO: limit argument
        // TODO: allowed_updates
        const std::function<void(const QList<Update>& updates)>& resultCallback
    );

signals:
    void finished();

private:
    BotPrivate* m_pPrivate;
};

}