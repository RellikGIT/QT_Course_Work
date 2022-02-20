#pragma once

#include "Question.h"

class ClosedQuestion : public Question
{
	Q_OBJECT

public:
	ClosedQuestion(QObject* parent, std::string text, std::vector <answer> answers, int diff);
	int check_ans(QString ans, std::vector <bool> ansv);	//Переопр. проверка ответа(проверка вектора)
	int max_mark();											//Переопр. макс оценка(проверка вектора)
	~ClosedQuestion();
};
