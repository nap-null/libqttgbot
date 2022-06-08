#include <QtCore/QtCore>


using namespace tgbot;


class EchoBot : public Bot
{
public:
    EchoBot(const QString& name, const QString& credetials)
      : Bot(name, credetials)
    {
    }

    virtual ~EchoBot() { }

    virtual void onMessageReceived(const Message& msg) {
        if (msg.type != Message::TEXT) {
            sendMessage("I could receive only text messages.");

            return;
        }

        TextMsg textMessage(msg);

        sendMessage(textMsg.text());
    }
};


int main(int argc, char* argv[]) {
    EchoBot bot("botname", "credentials");

    bot.start();
    bot.waitStop();

	return 0;
}
