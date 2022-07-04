#include "User.h"


namespace tgbot
{

User User::fromJsonObject(const QJsonObject& object)
{
    User user = {
        .id = object["id"].toInteger(),
        .isBot = object["is_bot"].toBool(),
        .firstName = object["first_name"].toString(),
        .lastName = object["last_name"].toString(),
        .username = object["username"].toString(),
        .lang = object["language_code"].toString()
    };

    return user;
}

}
