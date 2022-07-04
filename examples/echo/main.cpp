#include <QCoreApplication>
#include <QTimer>

#include "Main/Main.h"


int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    Main main(&app);

    QTimer::singleShot(0, &main, &Main::run);

    return app.exec();
}
