#pragma once

#include "Question.h"

class OpenQuestion : public Question
{
	Q_OBJECT

public:
	OpenQuestion(QObject *parent, std::string text, std::vector <answer> answers, int diff);
	int check_ans(QString ans, std::vector <bool> ansv);	//�������. �������� ������(�������� ������)
	int max_mark();											//�������. ���� ������(�������� �������)
	~OpenQuestion();
};
