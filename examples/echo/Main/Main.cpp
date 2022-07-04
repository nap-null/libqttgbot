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

    const QString token = "TOKEN";

    pEchoBot = new EchoBot(token, this);

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
