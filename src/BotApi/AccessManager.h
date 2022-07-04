#pragma once

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QNetworkRequest>


namespace tgbot
{

class Reply;

namespace api
{

class AccessManagerPrivate;

class AccessManager : public QObject
{
    Q_OBJECT

public:
    AccessManager(const QString& token, QObject* parent = nullptr);
    virtual ~AccessManager();

    QNetworkRequest get(const QString& path, const QVariantList &args, Reply** reply);

    QNetworkRequest get(const QString& path, Reply** reply) {
        return get(path, QVariantList(), reply);
    }

    QNetworkRequest get(
        const QString& path,
        const QMap<QString, QString>& parameters,
        Reply** reply
    );

    template<typename... Args>
    QNetworkRequest get(const QString &path, Args... args, Reply** reply) {
        auto argsList = variantArgs(args..., &reply);
        return get(path, argsList, reply);
    }

    QNetworkRequest post(const QString& path, const QMap<QString, QString>& args, Reply** reply);

private:
    AccessManagerPrivate *m_pPrivate;

private:
    template<typename Arg, typename... Args>
    QVariantList variantArgs(Arg arg, Args... args, Reply*** reply) {
        QVariantList list;
        parseArgsToVariantList(list, arg, reply, args...);
        return list;
    }

    void parseArgsToVariantList(QVariantList &list, Reply** replyArg, Reply*** reply) {
        *reply = replyArg;
    }

    template<typename... Args, typename Arg>
    void parseArgsToVariantList(QVariantList &list, Arg arg, Reply*** reply, Args... args) {
        list.prepend(QVariant::fromValue(arg));
        parseArgsToVariantList(list, reply, args...);
    }
};

}

}
