#include <QDateTime>
#include <QDebug>
#include <QThread>
#include <map>
#include "testdotnetstreamreadhttpheandler.h"

using namespace std;

const QString delayParmKey = "delay";
const QString countParmKey = "count";

TestDotNetStreamReadHttpHeandler::TestDotNetStreamReadHttpHeandler(QObject *parent) :
	AbstractHttpHeandler(parent)
{

}

TestDotNetStreamReadHttpHeandler::~TestDotNetStreamReadHttpHeandler() {

}

void TestDotNetStreamReadHttpHeandler::makeResponce(QTextStream *textStream, const QString &requestParams) {
	auto requestParamsParts = requestParams.split('&');
	map<QString, QString> params;
	for(auto requestParamsPart: requestParamsParts)	{
		auto pair = requestParamsPart.split('=');
		if(pair.size() == 2) {
			params.emplace(pair.first(), pair.at(1));
		}
	}

	bool ok = true;
	int delay	= params.count(delayParmKey) ? params.at(delayParmKey).toInt(&ok) : 0;
	if(!ok) {
		qWarning() << trUtf8("Не удалось распарсить значение параметра %0").arg(delayParmKey) << params.at(delayParmKey);
	}
	int count	= params.count(countParmKey) ? params.at(countParmKey).toInt(&ok) : 0;
	if(!ok) {
		qWarning() << trUtf8("Не удалось распарсить значение параметра %0").arg(delayParmKey) << params.at(countParmKey);
	}

	*textStream << trUtf8("Поток для проверки.\n");

	for(uint i = 0; i < count; i++) {
		*textStream << QString("Test %0 \n").arg(QDateTime::currentDateTime().toString());
		textStream->flush();
		QThread::currentThread()->sleep(delay);
	}

	emit responceMade();
}
