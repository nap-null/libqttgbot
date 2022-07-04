#include "Chat.h"


namespace tgbot
{

Chat Chat::fromJsonObject(const QJsonObject& object)
{
    Chat chat = {
        .id = object["id"].toInteger(),
    };

    auto type = object["type"].toString();

    if (type == "private")
        chat.type = PRIVATE;
    else if (type == "supergroup")
        chat.type = SUPERGROUP;

    return chat;
}

}
