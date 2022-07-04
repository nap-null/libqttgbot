#include "Message.h"


namespace tgbot
{

Message Message::fromMessageJsonObject(const QJsonObject& object) {
    Message message = {
        .type = MESSAGE,
        .id = object["message_id"].toInteger(),
        .text = object["text"].toString(),
        .timestamp = object["date"].toInteger(),
        .sentBy = User::fromJsonObject(object["from"].toObject()),
        .chat = Chat::fromJsonObject(object["chat"].toObject()),
    };

    if (object.contains("forward_from"))
        message.forwardedFrom = User::fromJsonObject(object["forward_from"].toObject());
    message.forwardedAt = object["forward_date"].toInteger();

    return message;
}

Message Message::fromPostJsonObject(const QJsonObject& object) {
    Message message = {
        .type = POST,
        .id = object["message_id"].toInteger(),
        .text = object["text"].toString(),
        .timestamp = object["date"].toInteger(),
        .chat = Chat::fromJsonObject(object["chat"].toObject()),
        .chatFrom = Chat::fromJsonObject(object["sender_chat"].toObject()),
        .signature = object["author_signature"].toString(),
    };

    if (object.contains("forward_from"))
        message.forwardedFrom = User::fromJsonObject(object["forward_from"].toObject());
    message.forwardedAt = object["forward_date"].toInteger();
    message.isAutomaticForward = object["is_automatic_forward"].toBool();

    return message;
}

}
