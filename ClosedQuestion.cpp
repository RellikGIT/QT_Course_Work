#include "ClosedQuestion.h"

ClosedQuestion::ClosedQuestion(QObject* parent, std::string text, std::vector <answer> answers, int diff)
	: Question(parent, text, answers, diff)
{
	type = true;
}

ClosedQuestion::~ClosedQuestion()
{
	answers.clear();
}
int ClosedQuestion::check_ans(QString ans, std::vector <bool> ansv)
{
	double counter = 0;
	double right_counter = 0;
	for (int i = 0; i < answers.size(); ++i)	//Количество верных ответов
	{
		counter += answers[i].right_ans;		
	}
	for (int i = 0; i < answers.size(); ++i)	//Количество верных ответов пользователя 
	//Минус количество неверных
	{
		if ((answers[i].right_ans) && (ansv[i])) right_counter++;
		else if ((!answers[i].right_ans) && (ansv[i])) right_counter--;

	}
	if (right_counter < 0) right_counter = 0;
	int mlt = 10;
	if (diff == 1) mlt = 5;
	if (diff == 3) mlt = 20;
	int mark = (int)(right_counter / counter) * mlt ;
	return mark;
} 
int ClosedQuestion::max_mark()
{
	if (diff == 1) return 5;
	if (diff == 3) return 20;
	return 10;
}
