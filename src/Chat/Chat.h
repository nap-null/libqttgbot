#pragma once

#include <QString>
#include <QJsonObject>


namespace tgbot
{

struct Chat
{
    enum Type {
        PRIVATE,
        SUPERGROUP
    };

    int64_t id;
    Type type;

    static Chat fromJsonObject(const QJsonObject& object);
};

}
