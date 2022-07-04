#include <QCoreApplication>
#include <QTimer>

#include "EchoBot/EchoBot.h"
#include "Main.h"


using namespace tgbot;


Main::Main(QCoreApplication* pApp)
  : QObject(pApp),
    pApp(pApp)
{}

void Main::run() {
    init();

    const QString maxToken = "1643258724:AAEyA9EaUlDff49MfLmS-WBZfoRRyOCP-Gg";
    const QString bestBelayerToken = "5489545751:AAGShL2OzuCGhvfoR4j15jNvzqeNEkAzvtw";
    const QString cragsRuToken = "1680426216:AAGw2KMJTydGpKMm94YfKxuTRk_-FDGs6rk";

    pEchoBot = new EchoBot(cragsRuToken, this);

    connect(pEchoBot, &tgbot::Bot::finished, this, &Main::quit);

    pEchoBot->start();
}

void Main::quit() {
    emit finished();
}

void Main::init() {
    connect(this, &Main::finished, pApp, &QCoreApplication::quit);
    connect(pApp, &QCoreApplication::aboutToQuit, this, &Main::aboutToQuitApp);
}

void Main::aboutToQuitApp() {
    // stop threads
    // sleep(1);   // wait for threads to stop.

    delete pEchoBot;
}
