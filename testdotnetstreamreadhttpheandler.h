#ifndef TESTDOTNETSTREAMREADHTTPHEANDLER_H
#define TESTDOTNETSTREAMREADHTTPHEANDLER_H

#include "abstracthttpheandler.h"
#include <QObject>

class TestDotNetStreamReadHttpHeandler : public AbstractHttpHeandler {
	Q_OBJECT
public:
	TestDotNetStreamReadHttpHeandler(QObject *parent = 0);
	~TestDotNetStreamReadHttpHeandler();

	// AbstractHttpHeandler interface
public:
	void makeResponce(QTextStream *textStream, const QString &requestParams);
};

#endif // TESTDOTNETSTREAMREADHTTPHEANDLER_H
