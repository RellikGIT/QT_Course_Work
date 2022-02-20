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
	std::vector <answer> answers;						//�������� ������(��� ��������� - ������� ����� 1)
	std::string text;									//����� �������
	int diff;											//���������
	int mark;											//������ �� ������(�������� ��� �����  ��)
	bool answered;										//������� ������� �� ������(���� ����� �� ���)
	virtual int check_ans(QString ans, std::vector <bool> ansv); //��������
	virtual int max_mark();								//���� ������ �� ������
	void shuffle_answers();								//���������� �������� ������
	bool type;											//��� �������
};
