#pragma once

#include <QWidget>
#include <vector>
#include <fstream>
#include <chrono>
#include "ui_Testing.h"
#include "Question.h"

class Testing : public QWidget
{
	Q_OBJECT

public:
	Testing(QWidget *parent = Q_NULLPTR);
	~Testing();
private slots:
	void on_test_menuButton_clicked();
	void on_test_startButton_clicked();
	void on_test_settingsButton_clicked();
	void on_test_settingsButton_2_clicked();
	void on_test_endButton_clicked();
	void on_testprevQuestionButton_clicked();
	void on_testprevQuestionButton_2_clicked();
	void on_answerSumbitButton_clicked();
signals:
	void test_menuButton_clicked();
	void test_startButton_clicked();
	void test_settingsButton_clicked();
	void test_settingsButton_2_clicked();
	void testprevQuestionButton_clicked();
	void testprevQuestionButton_2_clicked();
	void answerSumbitButton_clicked();
private:
	Ui::Testing* ui;
	std::vector<Question*> test;					//Это тест
	std::vector<QCheckBox*> boxes;					//Чекбоксы к закрытому вопросу
	int test_size;									//Вопросов в тесте (не размер базы)
	int diff;										//Сложность теста
	bool mode;										//Контрольный режим
	int ind;										//Индекс в test
	int max_ind;									//test_size  -1
	int timer;										//minutes
	std::chrono::system_clock::time_point start;	//Начало теста
	void shuffle_test();							//Перемешать вопросы
	void cut_test();								//Выбрать вопросы для теста
	void display_question(Question* q);				//Вывести вопрос на экран
	void display_empty();							//Очистить экран от вопроса
	void clear_ans();								//То же
	void clear_test();								//Очистить тест от пометок и прочего
	bool check_time();								//Проверка таймера
};

std::vector<Question*> load_test_from_base(QObject* parent);	//Загрузка теста из базы
