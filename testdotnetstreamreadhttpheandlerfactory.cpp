#include "testdotnetstreamreadhttpheandler.h"
#include "testdotnetstreamreadhttpheandlerfactory.h"

TestDotNetStreamReadHttpHeandlerFactory::TestDotNetStreamReadHttpHeandlerFactory()
{

}

TestDotNetStreamReadHttpHeandlerFactory::~TestDotNetStreamReadHttpHeandlerFactory() {

}

AbstractHttpHeandler *TestDotNetStreamReadHttpHeandlerFactory::getHttpHeandler(QObject *parent) {
	return new TestDotNetStreamReadHttpHeandler(parent);
}

