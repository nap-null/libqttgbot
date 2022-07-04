#pragma once

#include <QObject>


class QCoreApplication;
class EchoBot;

class Main : public QObject
{
    Q_OBJECT

public:
    explicit Main(QCoreApplication* pApp);

    void quit();
    void init();

signals:
    void finished();

public slots:
    void run();

    void aboutToQuitApp();

private:
    QCoreApplication* pApp;
    EchoBot* pEchoBot;
};
