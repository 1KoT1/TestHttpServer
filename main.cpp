#include <QCoreApplication>
#include "httpserver.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	HttpServer httpServer(8080);
	httpServer.start();
	return a.exec();
}
