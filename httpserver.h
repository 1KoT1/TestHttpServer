#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "abstracthttpheandlerfactory.h"
#include "connection.h"
#include <list>
#include <memory>
#include <QObject>
#include <QTcpServer>

using ConectionsCollectionType = std::list<std::unique_ptr<Connection>>;

class HttpServer : public QObject {
	Q_OBJECT
public:
	explicit HttpServer(ushort port, AbstractHttpHeandlerFactory * heandlerFactory, QObject *parent = 0);
	~HttpServer();

	void start();
	void stop();

signals:

public slots:

private:
	QTcpServer mTcpServer;
	ushort mPort;
	ConectionsCollectionType mConectionsCollection;
	std::unique_ptr<AbstractHttpHeandlerFactory> mHeandlerFactory;

private slots:
	void newConnection();
	void connectionAllDataSend(const Connection* closingConnection);
	void logError(QAbstractSocket::SocketError err);
};

#endif // HTTPSERVER_H
