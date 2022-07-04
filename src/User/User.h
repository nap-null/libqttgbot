#pragma once

#include <QString>
#include <QJsonObject>


namespace tgbot
{

struct User
{
    int64_t id;
    bool isBot;
    QString firstName;
    QString lastName;
    QString username;
    QString lang;

    static User fromJsonObject(const QJsonObject& object);
};

}
