#pragma once

#include <QNetworkReply>
#include <QVariant>


namespace tgbot
{

class Reply : public QNetworkReply
{
    Q_OBJECT

public:
    inline QVariant statusCode() const {
        return attribute(QNetworkRequest::HttpStatusCodeAttribute);
    }
};

}
