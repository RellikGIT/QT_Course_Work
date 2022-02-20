#include <QGraphicsSimpleTextItem>
#include "Demostration.h"

Demostration::Demostration(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Demostration)
{
	ui->setupUi(this);
	current.tree = new TreeNode(parent);
	graphicsScene = new QGraphicsScene(this);
	ui->graphicsView->setScene(graphicsScene);
	ind = -1;
	active = new TreeNode(current.tree->parent());
	min = new TreeNode(current.tree->parent());
}
void Demostration::paint()
{
	graphicsScene->clear();
	bool f = false;
	
	TreeNode* working = current.tree;
	if (working->drawable == false)				//������������ ������ ������ �� ��������
	{
		if (working->left != nullptr)
		{
			working = working->left;
		}
		else return;
	}
	auto font = QFont();
	font.setPointSize(18);
	do
	{
		if (working->drawn == false)		//���� ������� �� ���������� ������
		{	
			graphicsScene->addEllipse(QRectF(working->x_pos, working->y_pos, 60, 60), QPen(working->color), QBrush(working->color));
			QString str = QString::number((int)working->value);
			QGraphicsSimpleTextItem* value = graphicsScene->addSimpleText(str, font);
			value->setPos(working->x_pos + 10, working->y_pos + 10);
			working->drawn = true;
		}
		//���� ����� ������� ���� � �� ��������� ��� � ����
		if ((working->left != nullptr) && (working->left->drawn == false)) 
		{
			graphicsScene->addLine(QLineF(working->x_pos + 30, working->y_pos + 60, working->left->x_pos + 30, working->left->y_pos), QPen(Qt::darkBlue,3));
			working = working->left;
			f = true;
			continue;
		}
		//���� ������ ������� ���� � �� ��������� ��� � ����
		if ((working->right != nullptr) && (working->right->drawn == false))
		{
			graphicsScene->addLine(QLineF(working->x_pos + 30, working->y_pos + 60, working->right->x_pos + 30, working->right->y_pos), QPen(Qt::darkBlue, 3));
			working = working->right;
			continue;
		}
		//���� �������� ��� ��� ��� ���������� ��� � ��������
		working = working->parentnode;
	} while (working->drawable);	//���� �� ������� � ���. ������
	current.tree->clear_drawn(current.tree);//������� ����� ���������
	QString str = current.comment;
	QGraphicsSimpleTextItem* value = graphicsScene->addSimpleText(str, font);
	value->setPos(100, 900);
}
void Demostration::paint(cadre c)
{
	current = c;
	paint();
}
Demostration::~Demostration()
{
	delete ui;
}
void Demostration::on_menuButton_3_clicked()
{
	this->close();
	emit menuButton_3_clicked();
}
void Demostration::on_fillRandomButton_clicked()
{
	delete current.tree;
	current.tree = new TreeNode(parent());
	current.tree->insert_randomly(current.tree);
	paint();
	ind = -1;
	emit fillRandomButton_clicked();
}
void Demostration::on_addElementButton_clicked()
{
	ind = -1;
	QString qs = ui->textEdit->toPlainText();
	unsigned int value = qs.toUInt();
	current.tree->insert(current.tree, value);
	paint();
	emit addElementButton_clicked();
}
void Demostration::on_deleteElementButton_clicked()
{
	//��� ��� ������ ������������
	QString qs = ui->textEdit->toPlainText();
	unsigned int value = qs.toUInt();
	
	if (calculate_search_steps(value))	//������� ��� ����
	{
		if (analysis())
		{
			calculate_search_min_steps();
			calculate_delete_min_steps();
		}
	}
	cadre t;
	t.tree = copy_tree(current.tree);	//������������ 2 ���� � ����� ����������� ��� ���� �����
	t.comment = QString::fromUtf8(u8"������� �������!\n");
	demo.push_back(t);
	t.comment = "";
	demo.push_back(t);
	ind = 1;
	paint(demo[ind]);					//������� ��� � �������� 1(�� ������� 0 �������� ������)
	emit deleteElementButton_clicked();
}
void Demostration::on_clearTreeButton_clicked()
{
	ind = -1;
	delete current.tree;
	current.tree = new TreeNode(parent());
	graphicsScene->clear();
	emit clearTreeButton_clicked();
}
void Demostration::on_forwardButton_clicked()
{
	if ((ind > -1) && (ind < demo.size() - 1))
	{
		ind++;
		paint(demo[ind]);
	}
	emit forwardButton_clicked();
}
void Demostration::on_backButton_clicked()
{
	if (ind > 0)
	{
		ind--;
		paint(demo[ind]);
	}
	emit backButton_clicked();
}
bool Demostration::calculate_search_steps(unsigned int value)
{
	demo.clear();						
	demo.push_back(current);			
	TreeNode* working = current.tree;
	working = working->left;			//������� � �������� ������
	do
	{
		working->color = Qt::red;		
		current.comment = QString::fromUtf8(u8"�������� ������� ") + QString::number(working->value);
		cadre t;
		t.tree = copy_tree(current.tree);
		t.comment = current.comment;
		demo.push_back(t);
		if (working->value == value)	//���� ����� �� ��������� �������
		{
			current.comment = QString::fromUtf8(u8"����� ���������, ����� ��������");
			t.tree = copy_tree(current.tree);
			t.comment = current.comment;
			demo.push_back(t);
			active = working;
			return true;
		}
		else
		{
			if(value < working->value)//���� ������ �� ��� ������
			{
				current.comment = QString::fromUtf8(u8"���� ������ ��� � ������� �������, ��� ������");
				t.tree = copy_tree(current.tree);
				t.comment = current.comment;
				demo.push_back(t);
				working->color = Qt::blue;
				if (working->left == nullptr) //�� ���� ������ ���� ��� �� �� ���
				{
					current.comment = QString::fromUtf8(u8"����� ��� �������, ����� ���������");
					t.tree = copy_tree(current.tree);
					t.comment = current.comment;
					demo.push_back(t);
					return false;
				}
				else
				{
					working = working->left;
				}
			}
			else
											//�� �� ����� �������
			{
				current.comment = QString::fromUtf8(u8"���� ������ ��� � ������� �������, ��� �������");
				t.tree = copy_tree(current.tree);
				t.comment = current.comment;
				demo.push_back(t);
				working->color = Qt::blue;
				if (working->right == nullptr)
				{
					current.comment = QString::fromUtf8(u8"C����� ��� �������, ����� ���������");
					t.tree = copy_tree(current.tree);
					t.comment = current.comment;
					demo.push_back(t);
					return false;
				}
				else
				{
					working = working->right;
				}
			}
		}
	} while ((true));
	return false;
}
bool Demostration::analysis()
{
	cadre t;
	int save_x_pos = active->x_pos;
	int save_y_pos = active->y_pos;
	int save_l = active->length_line;
	if ((active->left == nullptr) && (active->right == nullptr))	//���� ��� �������� �� ������
	{

		t.tree = copy_tree(current.tree);
		t.comment = QString::fromUtf8(u8"� ������� ��� ��������, ������ ������� �\n");
		demo.push_back(t);
		if (active->parentnode->left == active)
		{
			active->parentnode->left = nullptr;

		}
		else
		{
			active->parentnode->right = nullptr;
		}
		active->parentnode = nullptr;
		delete active;
		return false;
	}
	else
	{
		if ((active->left != nullptr) && (active->right != nullptr))//����  �������� 2 �� ������� ����� � ������ �����
		{
			t.tree = copy_tree(current.tree);
			t.comment = QString::fromUtf8(u8"� ������� ��� �������\n");
			demo.push_back(t);
			return true;
		}
		//���� ������� 1(����� ��� ������) ������� ���� ����� �� �����, ������� �� �������
		else
		{
			if (active->left != nullptr)
			{
				t.comment = QString::fromUtf8(u8"� ������� ������ ����� �������, �������� ������� ��\n");
				t.tree = copy_tree(current.tree);
				demo.push_back(t);
				active->color = Qt::blue;
				active->left->parentnode = active->parentnode;
				active->parentnode->left = active->left;
				active = active->left;
				active->x_pos = save_x_pos;
				active->y_pos = save_y_pos;
				active->length_line = save_l;
				t.tree = copy_tree(current.tree);
				demo.push_back(t);
				return false;
			}
			else
			{
				t.comment = QString::fromUtf8(u8"� ������� ������ ������ �������, �������� ������� ��\n");
				active->color = Qt::blue;
				t.tree = copy_tree(current.tree);
				demo.push_back(t);
				active->right->parentnode = active->parentnode;
				active->parentnode->right = active->right;
				active = active->right;
				active->x_pos = save_x_pos;
				active->y_pos = save_y_pos;
				active->length_line = save_l;
				t.tree = copy_tree(current.tree);
				demo.push_back(t);
				return false;
			}
		}
	}
	return false;
}
void Demostration::calculate_search_min_steps()
{
	//� �������� � ������� �� ��������
	cadre t;
	active->color = Qt::blue;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"����� ���������� ������� ������ �� ���������\n");
	demo.push_back(t);
	min = active->right;
	min->color = Qt::red;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"��� ������ ���� ���� ����� �������\n");
	demo.push_back(t);
	min->color = Qt::blue;
	while (min->left != nullptr)
	{
		min = min->left;
		min->color = Qt::red;
		t.tree = copy_tree(current.tree);
		demo.push_back(t);
		min->color = Qt::blue;
	}
	min->color = Qt::red;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"������� ����������� ������� ������ �� ���������\n");
	demo.push_back(t);
}
void Demostration::calculate_delete_min_steps()
{
	//1)�������� �������� �����������(��������)
	cadre t;
	active->value = min->value;
	active->color = Qt::red;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"�������� ��������� ������� ����������� ������\n");
	demo.push_back(t);
	//2)��������� ��� ������ ����������� ��� ���������
	active->color = Qt::blue;
	int save_x_pos = min->x_pos;
	int save_y_pos = min->y_pos;
	int save_l = min->length_line;
	//3) ���� � ����������� ��� ��������,������ ������ �
	if ((min->left == nullptr) && (min->right == nullptr))
	{
		t.tree = copy_tree(current.tree);
		t.comment = QString::fromUtf8(u8"� ����������� ������� ��� ��������, ������ ������� �\n");
		demo.push_back(t);
		if (min->parentnode->left == min)
		{
			min->parentnode->left = nullptr;
		}
		else
		{
			min->parentnode->right = nullptr;
		}
		delete min;
	}
	//4)���� ������� ���� �� (��� ������)
	else
	{
		//1)�������� ������ �� �������� � ������� �����������
		//2)�������� ������ �� ������ ������� � �������� �����������
		//3)�������� �����������
		//4)��� ��� �������� ��������� �������� � �������� ���������� ����������� � �����������
		//����� ��� �� �������� �� ������
		if (min->left != nullptr)
		{
			t.comment = QString::fromUtf8(u8"� ����������� ������� ������ ����� �������, �������� ������� ��\n");
			min->color = Qt::blue;
			t.tree = copy_tree(current.tree);
			demo.push_back(t);
			min->left->parentnode = min->parentnode;
			min->parentnode->left = min->left;
			min = min->left;
			min->x_pos = save_x_pos;
			min->y_pos = save_y_pos;
			min->length_line = save_l;
			t.tree = copy_tree(current.tree);
			demo.push_back(t);
		}
		else
		{
			t.comment = QString::fromUtf8(u8"� ������� ������ ������ �������, �������� ������� ��\n");
			min->color = Qt::blue;
			t.tree = copy_tree(current.tree);
			demo.push_back(t);
			min->right->parentnode = min->parentnode;
			min->parentnode->right = min->right;
			min = min->right;
			min->x_pos = save_x_pos;
			min->y_pos = save_y_pos;
			min->length_line = save_l;
			t.tree = copy_tree(current.tree);
			demo.push_back(t);
		}
	}
}