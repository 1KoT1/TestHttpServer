#ifndef TESTDOTNETSTREAMREADHTTPHEANDLER_H
#define TESTDOTNETSTREAMREADHTTPHEANDLER_H

#include "abstracthttpheandler.h"
#include <QObject>
#include <QTimer>

class TestDotNetStreamReadHttpHeandler : public AbstractHttpHeandler {
	Q_OBJECT
public:
	TestDotNetStreamReadHttpHeandler(QObject *parent = 0);
	~TestDotNetStreamReadHttpHeandler();

	// AbstractHttpHeandler interface
public:
	void makeResponce(QTextStream *textStream, const QString &requestParams);

private:
	QTimer mTimer;
	uint mCountOfIteration;
	uint mIteration;
	QTextStream *mTextStream;

private slots:
	void timeout();
};

#endif // TESTDOTNETSTREAMREADHTTPHEANDLER_H
