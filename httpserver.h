#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "connection.h"
#include <list>
#include <QObject>
#include <QTcpServer>

using ConectionsCollectionType = std::list<Connection>;

class HttpServer : public QObject {
	Q_OBJECT
public:
	explicit HttpServer(ushort port, QObject *parent = 0);
	~HttpServer();

	void start();
	void stop();

signals:

public slots:

private:
	QTcpServer mTcpServer;
	ushort mPort;
	ConectionsCollectionType mConectionsCollection;

private slots:
	void newConnection();
};

#endif // HTTPSERVER_H
