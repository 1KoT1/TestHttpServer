#ifndef CONNECTION_H
#define CONNECTION_H

#include <QAbstractSocket>
#include <QByteArray>
#include <memory>
#include <QObject>
#include <QTextStream>

class AbstractHttpHeandler;

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
	explicit Connection(QAbstractSocket* socket, AbstractHttpHeandler* heandler, QObject *parent = 0);
	virtual ~Connection();

signals:
	void allDataSend(const Connection* closingConnection);
public slots:

private:
	std::unique_ptr<QAbstractSocket> mSocket;
	bool mAllByteWriten;
	AbstractHttpHeandler* mHeandler;
	QTextStream mTextStream;
	QByteArray mBufferIn;

private slots:
	void processNewData();
	void bytesWritten();
	void responceMade();
};

#endif // CONNECTION_H
