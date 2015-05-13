#include <QDateTime>
#include <QDebug>
#include <map>
#include "testdotnetstreamreadhttpheandler.h"

using namespace std;

const QString delayParmKey = "delay";
const QString countParmKey = "count";

TestDotNetStreamReadHttpHeandler::TestDotNetStreamReadHttpHeandler(QObject *parent) :
	AbstractHttpHeandler(parent),
	mTimer(this),
	mCountOfIteration(0),
	mIteration(0),
	mTextStream(nullptr)
{
	connect(&mTimer, SIGNAL(timeout()), SLOT(timeout()));
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

	*textStream << trUtf8("Поток для проверки.\n");
	textStream->flush();

	bool ok = true;
	mCountOfIteration	= params.count(countParmKey) ? params.at(countParmKey).toUInt(&ok) : 0;
	if(!ok) {
		qWarning() << trUtf8("Не удалось распарсить значение параметра %0").arg(delayParmKey) << params.at(countParmKey);
	}
	mTextStream = textStream;

	int delay	= params.count(delayParmKey) ? params.at(delayParmKey).toInt(&ok) : 0;
	if(!ok) {
		qWarning() << trUtf8("Не удалось распарсить значение параметра %0").arg(delayParmKey) << params.at(delayParmKey);
	}
	mTimer.start(delay);
}

void TestDotNetStreamReadHttpHeandler::timeout() {
	if(mIteration < mCountOfIteration) {
		if(!mTextStream) {
			qCritical() << trUtf8("Обработчик не имеет потока вывода.");
			mTimer.stop();
			return;
		}

		*mTextStream << QString("Test %0 \n").arg(QDateTime::currentDateTime().toString());
		mTextStream->flush();

		mIteration++;
		if(mIteration >= mCountOfIteration) {
			mTimer.stop();
			emit responceMade();
		}
	} else {
		mTimer.stop();
		return;
	}
}
