#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QRegularExpression>
#include <QUrlQuery>
#include <utility>

#include "AccessManager.h"


namespace
{

const QString apiUrl("https://api.telegram.org/");

}


namespace tgbot
{

namespace api
{

class AccessManagerPrivate
{
public:
    AccessManagerPrivate(AccessManager *pPublic, QString token)
      : pPublic(pPublic),
        token(std::move(token)),
        pAccessManager(new QNetworkAccessManager(pPublic))
    {
    }
    virtual ~AccessManagerPrivate() {
        delete pAccessManager;
    }

    QString processPathWithArgs(const QString &path, const QVariantList &args) {
        QVariantList argsQueue(args);
        QStringList resultPathComponents;
        auto pathComponents = path.split('/');

        for (QString component: pathComponents) {
            auto substituteRE = QRegularExpression(QRegularExpression::fromWildcard(QString(":*")));
            if (substituteRE.match(component).hasMatch()) {
                auto arg = argsQueue.last().toString();
                argsQueue.pop_back();

                resultPathComponents << arg;
            } else {
                resultPathComponents << component;
            }
        }

        return resultPathComponents.join('/');
    }

    AccessManager *pPublic;
    QString token;
    QNetworkAccessManager *pAccessManager;
};


#define P (this->m_pPrivate)

AccessManager::AccessManager(const QString& token, QObject* parent)
  : QObject(parent),
    m_pPrivate(new AccessManagerPrivate(this, token))
{
}

AccessManager::~AccessManager() {
    delete m_pPrivate;
}

QNetworkRequest AccessManager::get(const QString &path, const QVariantList &args, Reply** reply) {
    const QUrl url(apiUrl + "bot" + P->token + P->processPathWithArgs(path, args));

    auto request = QNetworkRequest(url);

    *reply = (Reply*)P->pAccessManager->get(request);

    return request;
}

QNetworkRequest AccessManager::get(
    const QString& path,
    const QMap<QString, QString>& parameters,
    Reply** reply
)
{
    QUrl url(apiUrl + "bot" + P->token + path);
    QUrlQuery query;

    for (auto key : parameters.keys()) {
        query.addQueryItem(key, parameters[key]);
    }

    url.setQuery(query);

    auto request = QNetworkRequest(url);

    *reply = (Reply*)P->pAccessManager->get(request);

    return request;
}

QNetworkRequest AccessManager::post(
    const QString& path,
    const QMap<QString, QString>& args,
    Reply** reply
)
{
    const QUrl url(apiUrl + "bot" + P->token + path);
    auto multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, P->pAccessManager);

    auto request = QNetworkRequest(url);

    for (const auto& argName : args.keys()) {
        auto argValue = args[argName];
        QHttpPart textPart;
        textPart.setHeader(
            QNetworkRequest::ContentDispositionHeader,
            QVariant(QString("form-data; name=\"%1\"").arg(argName))
        );
        textPart.setBody(argValue.toUtf8());

        multiPart->append(textPart);
    }

    *reply = (Reply*)P->pAccessManager->post(request, multiPart);

    return request;
}

}

}
