#include "testhttpheandler.h"
#include "testhttpheandlerfactory.h"

TestHttpHeandlerFactory::TestHttpHeandlerFactory()
{

}

TestHttpHeandlerFactory::~TestHttpHeandlerFactory()
{

}

AbstractHttpHeandler *TestHttpHeandlerFactory::getHttpHeandler(QObject *parent) {
	return new TestHttpHeandler(parent);
}
