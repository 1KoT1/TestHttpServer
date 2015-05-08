#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QTcpServer>

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

	void newConnection();
};

#endif // HTTPSERVER_H
