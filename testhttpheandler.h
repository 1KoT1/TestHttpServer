#ifndef TESTHTTPHEANDLER_H
#define TESTHTTPHEANDLER_H

#include "abstracthttpheandler.h"

class TestHttpHeandler : public AbstractHttpHeandler {
	Q_OBJECT
public:
	explicit TestHttpHeandler(QObject *parent = 0);
	~TestHttpHeandler();

signals:

public slots:

	// AbstractHttpHeandler interface
public:
	void makeResponce(QTextStream *, const QString &requestParams);
};

#endif // TESTHTTPHEANDLER_H
