#ifndef TESTDOTNETSTREAMREADHTTPHEANDLERFACTORY_H
#define TESTDOTNETSTREAMREADHTTPHEANDLERFACTORY_H

#include "abstracthttpheandlerfactory.h"
#include <QObject>

class AbstractHttpHeandler;

class TestDotNetStreamReadHttpHeandlerFactory : public AbstractHttpHeandlerFactory {
public:
	TestDotNetStreamReadHttpHeandlerFactory();
	~TestDotNetStreamReadHttpHeandlerFactory();

	// AbstractHttpHeandlerFactory interface
public:
	AbstractHttpHeandler *getHttpHeandler(QObject *parent);
};

#endif // TESTDOTNETSTREAMREADHTTPHEANDLERFACTORY_H
