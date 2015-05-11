#ifndef CONNECTION_H
#define CONNECTION_H

#include <QAbstractSocket>
#include <memory>
#include <QObject>

class Connection : public QObject {
	Q_OBJECT
public:
	/** Соединние с клиентом.
	 *
	 * Необходимо передать уакзатель на уже открытый сокет. Полученный, к примеру из QTcpServer::nextPendingConnection().
	 * Connection сам позаботиться об уничтожении переданного
	 * объекта-сокета.
	 *
	 * @param socket Указатель на открытый сокет через который подключился клиент.
	 * Connection сам позаботиться об уничтожении переданного объекта-сокета.
	 * @param parent
	 */
	explicit Connection(QAbstractSocket* socket, QObject *parent = 0);
	virtual ~Connection();

signals:
	void allDataSend(const Connection* closingConnection);
public slots:

private:
	std::unique_ptr<QAbstractSocket> mSocket;
	bool mAllByteWriten;

private slots:
	void processNewData();
	void bytesWritten();
};

#endif // CONNECTION_H
