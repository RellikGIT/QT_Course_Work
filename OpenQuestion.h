#pragma once

#include "Question.h"

class OpenQuestion : public Question
{
	Q_OBJECT

public:
	OpenQuestion(QObject *parent, std::string text, std::vector <answer> answers, int diff);
	int check_ans(QString ans, std::vector <bool> ansv);	//Переопр. проверка ответа(проверка строки)
	int max_mark();											//Переопр. макс оценка(проверка вектора)
	~OpenQuestion();
};
