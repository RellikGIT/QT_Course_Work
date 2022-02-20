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
	std::vector<Question*> test;					//��� ����
	std::vector<QCheckBox*> boxes;					//�������� � ��������� �������
	int test_size;									//�������� � ����� (�� ������ ����)
	int diff;										//��������� �����
	bool mode;										//����������� �����
	int ind;										//������ � test
	int max_ind;									//test_size  -1
	int timer;										//minutes
	std::chrono::system_clock::time_point start;	//������ �����
	void shuffle_test();							//���������� �������
	void cut_test();								//������� ������� ��� �����
	void display_question(Question* q);				//������� ������ �� �����
	void display_empty();							//�������� ����� �� �������
	void clear_ans();								//�� ��
	void clear_test();								//�������� ���� �� ������� � �������
	bool check_time();								//�������� �������
};

std::vector<Question*> load_test_from_base(QObject* parent);	//�������� ����� �� ����
