#include "testhttpheandler.h"

TestHttpHeandler::TestHttpHeandler(QObject *parent) : AbstractHttpHeandler(parent)
{

}

TestHttpHeandler::~TestHttpHeandler()
{

}

void TestHttpHeandler::makeResponce(QTextStream *textStream, const QString &) {
	*textStream << "HTTP/1.0 200 Ok\r\n"
								 "Content-Type: text/html; charset=\"utf-8\"\r\n"
								 "\r\n"
								 "<h1>Test</h1>\n";

	emit responceMade();
}
