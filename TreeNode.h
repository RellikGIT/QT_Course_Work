#pragma once

#include <QObject>
#include <QPainter>

class TreeNode : public QObject 
{
	Q_OBJECT

public:

	TreeNode(QObject *parent);
	TreeNode(QObject* parent, TreeNode* parentnode, unsigned short value, int x_pos, int y_pos, int l);
	TreeNode(QObject* parent, TreeNode* parentnode, unsigned short value, int x_pos, int y_pos, int l, QColor c);
	~TreeNode();
	
	//������ � ������������ ������

	TreeNode* parentnode;			
	//������ �� �������� ����������� ��� ��������� ����� ������������

	TreeNode* left;
	TreeNode* right;

	unsigned short value : 8;
	//������� ������ ��� ������ ��� ����� ��������� � ���� ������������� ������ ��� ���� ��� ��������
	QColor color;
	bool drawable;
	bool drawn;

	int x_pos;
	int y_pos;
	int length_line;
	//����������� �������
	void insert(TreeNode* node, unsigned short value);
	//����� ��������� ����������
	void insert_randomly(TreeNode* node);
	//������� ������� drawn
	void clear_drawn(TreeNode* node);
};
//�������� ����������� ������, ��������
TreeNode* copy_tree(TreeNode* node);
//����������� �����
TreeNode* copy(TreeNode* node);
//����������� ������������ ������
void set_parents(TreeNode* node);