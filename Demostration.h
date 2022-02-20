#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <vector>
#include "ui_Demostration.h"
#include "TreeNode.h"
struct cadre											//����- ��������� ������������
{	
	TreeNode* tree;
	QString comment;
};
class Demostration : public QWidget
{
	Q_OBJECT

public:
	Demostration(QWidget *parent = Q_NULLPTR);
	~Demostration();
	void paint();										//��������� ������ � �����������
	void paint(cadre c);								//�� �� ����� ������ ���������� �����
	bool calculate_search_steps(unsigned int value);	//������ ����� ������ ��������
	bool analysis();									//���� �������
	void calculate_search_min_steps();					//���� ������ ������������ ������ �� �����������
	void calculate_delete_min_steps();					//���� �������� ������������ ������ �� �����������
private slots:
	void on_menuButton_3_clicked();
	void on_fillRandomButton_clicked();
	void on_addElementButton_clicked();
	void on_deleteElementButton_clicked();
	void on_clearTreeButton_clicked();
	void on_forwardButton_clicked();
	void on_backButton_clicked();
signals:
	void menuButton_3_clicked();
	void fillRandomButton_clicked();
	void addElementButton_clicked();
	void deleteElementButton_clicked();
	void clearTreeButton_clicked();
	void forwardButton_clicked();
	void backButton_clicked();
private:
	Ui::Demostration* ui;								//��
	QGraphicsScene* graphicsScene;						//�������
	cadre current;										//������� ����
	std::vector<cadre> demo;							//��� �����
	TreeNode* active;									//������� ���������
	TreeNode* min;										//����������� ������ �� active
	int ind;											//������ � demo

};
