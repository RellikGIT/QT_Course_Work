#include "TreeNode.h"
#include <random>
#include <chrono>
TreeNode::TreeNode(QObject *parent)
	: QObject(parent)
{
	//Этот конструктор вызывается только для искуственного корня
	color = QColor(Qt::blue);
	drawable = false;
	drawn = true;
	parentnode = nullptr;
	right = nullptr;
	left = nullptr;
	value = 255;
	x_pos = 1000;
	y_pos = 200;
	length_line = 500;
}
TreeNode::TreeNode(QObject* parent, TreeNode* parentnode, unsigned short value, int x_pos, int y_pos, int l)
	: QObject(parent)
{
	//Этот конструктор вызывается при формировании дерева
	color = QColor(Qt::blue);
	drawable = true;
	drawn = false;
	this->parentnode = parentnode;
	right = nullptr;
	left = nullptr;
	this->value = value;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->length_line = l;
}
TreeNode::TreeNode(QObject* parent, TreeNode* parentnode, unsigned short value, int x_pos, int y_pos, int l, QColor c)
	: QObject(parent)
{
	//Этот конструктор вызывается при копировании дерева
	color = QColor(Qt::blue);
	drawable = true;
	drawn = false;
	this->parentnode = parentnode;
	right = nullptr;
	left = nullptr;
	this->value = value;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->length_line = l;
	this->color = c;
}
TreeNode::~TreeNode()
{
	//Тут можно было написать рекурсивное удаление дерева, но
}
void TreeNode::insert(TreeNode* node, unsigned short value)
{
	if (node->value == value) return;
	if (value < node->value)
	{
		if (node->left == nullptr)
		{
			node->left = new TreeNode(parent(), node, value, node-> x_pos - node->length_line, node->y_pos + 100, node->length_line / 2.0);
		}
		else
		{
			insert(node->left, value);
		}
	}
	else
	{
		if (node->right == nullptr)
		{
			node->right = new TreeNode(parent(), node, value, node->x_pos + node->length_line, node->y_pos + 100, node->length_line / 2.0);
		}
		else
		{
			insert(node->right, value);
		}
	}
}
void TreeNode::insert_randomly(TreeNode* node)
{
	//Чтобы пользователю было удобнее и дерево не вылезало при плохом рандоме делаем хороший
	std::mt19937 gen(unsigned(time(nullptr)));
	std::uniform_int_distribution<int> range1(40, 60);

	std::uniform_int_distribution<int> range2(10, 20);
	std::uniform_int_distribution<int> range4(0, 9);
	std::uniform_int_distribution<int> range6(25, 30);
	std::uniform_int_distribution<int> range3(21, 24);
	std::uniform_int_distribution<int> range5(31, 39);

	std::uniform_int_distribution<int> range8(80, 90);
	std::uniform_int_distribution<int> range9(61, 79);
	std::uniform_int_distribution<int> range10(91, 99);

	insert(node, range1(gen));
	insert(node, range2(gen));
	insert(node, range3(gen));
	insert(node, range4(gen));
	insert(node, range5(gen));
	insert(node, range8(gen));
	insert(node, range9(gen));
	insert(node, range10(gen));
}
void TreeNode::clear_drawn(TreeNode* node)
{
	node->drawn = false;
	if (node->left != nullptr)
		clear_drawn(node->left);
	if (node->right != nullptr)
		clear_drawn(node->right);
}
TreeNode* copy_tree(TreeNode* node)
{
	//Создаем искуственный корень и к нему цепляем копию того дерева без иск. корня
	TreeNode* newnode = new TreeNode(node->parent());
	newnode->left = copy(node->left);
	//Так как родительские ссылки про копировании проставить не получится делаем это отдельно
	set_parents(newnode);
	return newnode;

}
TreeNode* copy(TreeNode* node)
{	
	if (node == nullptr)
		return nullptr;
	TreeNode* newnode = new TreeNode(node->parent(), node->parentnode, node->value, node->x_pos, node->y_pos, node->length_line, node->color);
	newnode->left = copy(node->left);
	newnode->right = copy(node->right);

	return newnode;
}
void set_parents(TreeNode* node)
{
	if (node->left != nullptr)
	{
		node->left->parentnode = node;
		set_parents(node->left);
	}
	if (node->right != nullptr)
	{
		node->right->parentnode = node;
		set_parents(node->right);
	}
}