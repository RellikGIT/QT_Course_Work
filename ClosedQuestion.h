#pragma once

#include "Question.h"

class ClosedQuestion : public Question
{
	Q_OBJECT

public:
	ClosedQuestion(QObject* parent, std::string text, std::vector <answer> answers, int diff);
	int check_ans(QString ans, std::vector <bool> ansv);	//�������. �������� ������(�������� �������)
	int max_mark();											//�������. ���� ������(�������� �������)
	~ClosedQuestion();
};
