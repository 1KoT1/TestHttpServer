#ifndef ABSTRACTHTTPHEANDLER_H
#define ABSTRACTHTTPHEANDLER_H

#include <QObject>
#include <QTextStream>

class AbstractHttpHeandler : public QObject {
	Q_OBJECT
public:
	explicit AbstractHttpHeandler(QObject *parent = 0);
	virtual ~AbstractHttpHeandler();

	virtual void makeResponce(QTextStream *) = 0;
signals:

public slots:
};

#endif // ABSTRACTHTTPHEANDLER_H
