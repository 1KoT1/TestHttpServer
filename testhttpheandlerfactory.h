#ifndef HTTPHEANDLERFACTORY_H
#define HTTPHEANDLERFACTORY_H

#include "abstracthttpheandlerfactory.h"

class TestHttpHeandlerFactory : public AbstractHttpHeandlerFactory {
	Q_OBJECT
public:
	TestHttpHeandlerFactory();
	~TestHttpHeandlerFactory();

	// AbstractHttpHeandlerFactory interface
public:
	AbstractHttpHeandler *getHttpHeandler(QObject *parent);
};

#endif // HTTPHEANDLERFACTORY_H
