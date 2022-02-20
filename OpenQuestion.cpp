#include <qtextcodec.h>
#include "OpenQuestion.h"

OpenQuestion::OpenQuestion(QObject *parent, std::string text, std::vector <answer> answers, int diff)
	: Question(parent, text, answers, diff)
{
	type = false;
}

OpenQuestion::~OpenQuestion()
{
	answers.clear();
}

int OpenQuestion::check_ans(QString ans, std::vector <bool> ansv)
{
	QTextCodec* codec = QTextCodec::codecForName("CP1251"); 
	//Строка в программе записана в анси, и это единсвтенный способ сделать из неё QString который я ншёл
	QByteArray ba(answers[0].ans.c_str());       // Convert to QByteArray
	QString msg = codec->toUnicode(ba);          // Qt magic !!! 
	int mark = 0;
	if (msg == ans)
	{
		if (diff == 1) return 5;
		if (diff == 2) return 10;
		if (diff == 3) return 20;
	}
	return 0;
}
int OpenQuestion::max_mark()
{
	if (diff == 1) return 5;
	if (diff == 3) return 20;
	return 10;
}