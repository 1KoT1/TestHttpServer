#include "httpserver.h"

HttpServer::HttpServer(ushort port, QObject *parent) :
	QObject(parent),
	mTcpServer(this),
	mPort(port)
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

}

