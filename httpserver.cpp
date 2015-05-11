#include "httpserver.h"
#include <QDateTime>
#include <QTcpSocket>
#include <QTextStream>

#include <QDebug>

using namespace std;

HttpServer::HttpServer(ushort port, AbstractHttpHeandlerFactory * heandlerFactory, QObject *parent) :
	QObject(parent),
	mTcpServer(this),
	mPort(port),
	mConectionsCollection(),
	mHeandlerFactory(heandlerFactory)
{
	if(!mHeandlerFactory->parent()) {
		mHeandlerFactory->setParent(this);
	}
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
	auto newConnection = new Connection(mTcpServer.nextPendingConnection(), mHeandlerFactory->getHttpHeandler(this));
	connect(newConnection,
					SIGNAL(allDataSend(const Connection*)),
					SLOT(connectionAllDataSend(const Connection*))
				 );
	mConectionsCollection.push_back(unique_ptr<Connection>(newConnection));
}

void HttpServer::connectionAllDataSend(const Connection *closingConnection){
	qDebug() << mConectionsCollection.size();
	mConectionsCollection.remove_if([closingConnection](const unique_ptr<Connection>& c) { return c.get() == closingConnection; });
	qDebug() << mConectionsCollection.size();
}

