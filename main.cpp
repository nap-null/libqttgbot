#include <QtCore/QtCore>

int main(int argc, char* argv[]) {
	QStringList args;

	for(int i = 0; i < argc; i++)
		args << argv[i];

	qDebug() << args;

	return 0;
}
