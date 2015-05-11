#include "httpserver.h"
#include <QDateTime>
#include <QTcpSocket>
#include <QTextStream>

HttpServer::HttpServer(ushort port, QObject *parent) :
	QObject(parent),
	mTcpServer(this),
	mPort(port),
	mConectionsCollection()
{
	connect(&mTcpServer, SIGNAL(newConnection()), SLOT(newConnection()));
}

HttpServer::~HttpServer() {
	stop();
}

void HttpServer::start() {
	mTcpServer.listen(QHostAddress::Any, mPort);
}

void HttpServer::stop() {
	mTcpServer.close();
}

void HttpServer::newConnection() {
	QAbstractSocket* socket = mTcpServer.nextPendingConnection();
	QTextStream textStream(socket);
	textStream.setAutoDetectUnicode(true);
	while(textStream.atEnd()) {
		socket->waitForReadyRead();
		if(socket->canReadLine()) {
			qDebug() << textStream.readLine();
		}
	}
	textStream << "HTTP/1.0 200 Ok\r\n"
								"Content-Type: text/html; charset=\"utf-8\"\r\n"
								"\r\n"
								"<h1>Nothing to see here</h1>\n"
						 << QDateTime::currentDateTime().toString() << "\n";
	socket->close();
}

