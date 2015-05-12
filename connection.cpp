#include "abstracthttpheandler.h"
#include "connection.h"
#include <exception>

using namespace std;

class RequestFormatError : public runtime_error {
public:
	RequestFormatError() : runtime_error ("Request has bad format.") {}
};

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
	mBufferIn.reserve(200);
}

Connection::~Connection() {

}

int getNextLim(const QByteArray &buffer,const char *mark, int from) {
	auto i = buffer.indexOf(mark, from);
	if(i == -1) {
		throw RequestFormatError();
	} else {
		return i;
	}
}

void Connection::processNewData() {
	mBufferIn.push_back(mSocket->readAll());
	try {
		if(mBufferIn.endsWith("\r\n\r\n")) {
			auto i = getNextLim(mBufferIn, " ", 0);

			auto command = mBufferIn.left(i);
			if(command == "GET") {
				i++;
				auto i2 = getNextLim(mBufferIn, " ", i);
				auto uri = mBufferIn.mid(i, i2 - i);

				i2++;
				auto i3 = getNextLim(mBufferIn, "\r\n", i2);
				if(i3 != i2) {
					mTextStream << mBufferIn.mid(i2, i3 - i2) << ' ';
				}
				mTextStream << "200 OK\r\n\r\n";

				mHeandler->makeResponce(&mTextStream, uri);
			} else {
				throw RequestFormatError();
			}
		}
	} catch(RequestFormatError) {
		qWarning() << trUtf8("Запрос имеет неподдерживаемый формат: ") << mBufferIn;
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

