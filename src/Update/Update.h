#pragma once

#include <QString>
#include <QJsonObject>

#include <Message/Message.h>


namespace tgbot
{

struct Update
{
    int64_t id;
    Message message;

    static Update fromJsonObject(const QJsonObject& object);
};

}
