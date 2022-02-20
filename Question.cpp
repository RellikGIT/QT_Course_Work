#include "Question.h"
#include <random>
#include <chrono>
Question::Question(QObject *parent, std::string text, std::vector <answer> answers, int diff)
	: QObject(parent)
{
	this->text = text;
	this->answers = answers;
	this->diff = diff;
	type = false;
}

Question::~Question()
{
	answers.clear();
}
int Question::check_ans(QString ans, std::vector <bool> ansv)
{
	return 0;
}
int Question::max_mark()
{
	return 0;
}
void Question::shuffle_answers()
{
	using namespace std;
	mt19937 gen(unsigned(time(nullptr)));
	for (int i = 0; i < answers.size(); ++i)
	{
		uniform_int_distribution<int> uid(i, answers.size() - 1);
		std::swap(answers[i], answers[uid(gen)]);
	}
}