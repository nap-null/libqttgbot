#include "Update.h"


namespace tgbot
{

Update Update::fromJsonObject(const QJsonObject& object)
{
    Update update = {
        .id = object["update_id"].toInteger(),
    };

    if (object.contains("message"))
        update.message = Message::fromMessageJsonObject(object["message"].toObject());
    else if (object.contains("channel_post"))
        update.message = Message::fromPostJsonObject(object["channel_post"].toObject());

    return update;
}

}
