#include "testhttpheandler.h"

TestHttpHeandler::TestHttpHeandler(QObject *parent) : AbstractHttpHeandler(parent)
{

}

TestHttpHeandler::~TestHttpHeandler()
{

}

void TestHttpHeandler::makeResponce(QTextStream *textStream, const QString &) {
	*textStream << "<h1>Test</h1>\n";

	emit responceMade();
}
