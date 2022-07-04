#pragma once

#include <QString>
#include <QJsonObject>

#include <Chat/Chat.h>
#include "User/User.h"


namespace tgbot
{

struct Message
{
    enum Type {
        MESSAGE,
        POST,
    };

    Type type;
    qint64 id;
    QString text;
    qint64 timestamp;

    User sentBy;
    Chat chat;
    Chat chatFrom; // E.g. for auto posting from channel to the linked discussion group.
    User forwardedFrom;
    qint64 forwardedAt;

    QString signature;

    bool isAutomaticForward;

    static Message fromMessageJsonObject(const QJsonObject& object);
    static Message fromPostJsonObject(const QJsonObject& object);
};

}
