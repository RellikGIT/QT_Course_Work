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
	
	//ƒерево с искуственным корнем

	TreeNode* parentnode;			
	//—сылка на родител€ об€зательна дл€ генерации шагов демонстрации

	TreeNode* left;
	TreeNode* right;

	unsigned short value : 8;
	//¬ершина хранит все данные дл€ своей отрисовки в силу рекурсивности дерева это путь его рисовать
	QColor color;
	bool drawable;
	bool drawn;

	int x_pos;
	int y_pos;
	int length_line;
	//–екурсивна€ вставка
	void insert(TreeNode* node, unsigned short value);
	//ѕочти случайное заполнение
	void insert_randomly(TreeNode* node);
	//ќчистка пометок drawn
	void clear_drawn(TreeNode* node);
};
//√лубокое копирование дерева, рекурси€
TreeNode* copy_tree(TreeNode* node);
//–екурсивна€ часть
TreeNode* copy(TreeNode* node);
//ѕроставл€ет родительские ссылки
void set_parents(TreeNode* node);