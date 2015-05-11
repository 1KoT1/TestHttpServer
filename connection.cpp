#include "abstracthttpheandler.h"
#include "connection.h"
#include <QTextStream>

Connection::Connection(QAbstractSocket *socket, AbstractHttpHeandler* heandler, QObject *parent) :
	QObject(parent),
	mSocket(socket),
	mAllByteWriten(false),
	mHeandler(heandler)
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

	mHeandler->makeResponce(&textStream);

	mAllByteWriten = true;
}

void Connection::bytesWritten() {
	if(mAllByteWriten) {
		emit allDataSend(this);
	}
}

