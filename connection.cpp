#include "connection.h"
#include <QTextStream>

Connection::Connection(QAbstractSocket *socket, QObject *parent) :
	QObject(parent),
	mSocket(socket),
	mAllByteWriten(false)
{
	connect(mSocket.get(), SIGNAL(readyRead()), SLOT(processNewData()));
	connect(mSocket.get(), SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten()));
}

Connection::~Connection() {

}

void Connection::processNewData() {
	QTextStream textStream(mSocket.get());
	textStream.setAutoDetectUnicode(true);
	while(mSocket->canReadLine()) {
		qDebug() << textStream.readLine();
	}
	textStream << "HTTP/1.0 200 Ok\r\n"
								"Content-Type: text/html; charset=\"utf-8\"\r\n"
								"\r\n"
								"<h1>Nothing to see here</h1>\n";
	mAllByteWriten = true;
}

void Connection::bytesWritten() {
	if(mAllByteWriten) {
		emit allDataSend(this);
	}
}

