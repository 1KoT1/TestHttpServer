#ifndef ABSTRACTHTTPHEANDLERFACTORY_H
#define ABSTRACTHTTPHEANDLERFACTORY_H

#include <QObject>

class AbstractHttpHeandler;

class AbstractHttpHeandlerFactory : public QObject {
	Q_OBJECT
public:
	explicit AbstractHttpHeandlerFactory(QObject *parent = 0);
	~AbstractHttpHeandlerFactory();

	virtual AbstractHttpHeandler *getHttpHeandler(QObject *parent = 0) = 0;

signals:

public slots:
};

#endif // ABSTRACTHTTPHEANDLERFACTORY_H
