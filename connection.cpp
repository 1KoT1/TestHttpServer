#include "abstracthttpheandler.h"
#include "connection.h"

Connection::Connection(QAbstractSocket *socket, AbstractHttpHeandler* heandler, QObject *parent) :
	QObject(parent),
	mSocket(socket),
	mAllByteWriten(false),
	mHeandler(heandler),
	mTextStream(mSocket.get())
{
	connect(mSocket.get(), SIGNAL(readyRead()), SLOT(processNewData()));
	connect(mSocket.get(), SIGNAL(bytesWritten(qint64)), SLOT(bytesWritten()));
	connect(mHeandler, SIGNAL(responceMade()), SLOT(responceMade()));
	mTextStream.setAutoDetectUnicode(true);
}

Connection::~Connection() {

}

void Connection::processNewData() {
	while(mSocket->canReadLine()) {
		qDebug() << mTextStream.readLine();
	}

	mHeandler->makeResponce(&mTextStream);
}

void Connection::bytesWritten() {
	if(mAllByteWriten) {
		emit allDataSend(this);
	}
}

void Connection::responceMade() {
	mTextStream.flush();
	mAllByteWriten = true;
}

