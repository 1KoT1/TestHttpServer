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
	QStringList request;
	while(mSocket->canReadLine()) {
		request << mTextStream.readLine();
	}
	if(request.empty()){
		return;
	}
	auto requestParts = request.first().split(' ');
	if(requestParts.empty()){
		qWarning() << trUtf8("Запрос имеет неподдерживаемый формат: ") << request;
		return;
	}
	if(requestParts.first() == "GET") {
		mHeandler->makeResponce(&mTextStream);
	} else {
		qWarning() << trUtf8("Запрос имеет неподдерживаемый формат: ") << request;
	}
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

