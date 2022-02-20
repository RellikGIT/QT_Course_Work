#pragma once

#include <QObject>
#include <vector>
struct answer
{
	std::string ans;
	bool right_ans = false;
};
class Question : public QObject
{
	Q_OBJECT
public:
	Question(QObject *parent, std::string text, std::vector <answer> answers, int diff);
	~Question();
	std::vector <answer> answers;						//Варианты ответа(для открытого - вариант всего 1)
	std::string text;									//Текст вопроса
	int diff;											//Сложность
	int mark;											//Оценка за вопрос(хранится тут зачем  то)
	bool answered;										//Пометка отвечен ли вопрос(тоже зачем то тут)
	virtual int check_ans(QString ans, std::vector <bool> ansv); //Проверка
	virtual int max_mark();								//Макс оценка за вопрос
	void shuffle_answers();								//Перемешать варианты ответа
	bool type;											//Тип вопроса
};
