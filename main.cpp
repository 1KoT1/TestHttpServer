#include "testhttpheandlerfactory.h"
#include <QCoreApplication>
#include "httpserver.h"

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	HttpServer httpServer(8080, new TestHttpHeandlerFactory());
	httpServer.start();
	return a.exec();
}
