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
	if (working->drawable == false)				//Искуственный корень дерева не рисуется
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
		if (working->drawn == false)		//Если вершина не нарисована рисуем
		{	
			graphicsScene->addEllipse(QRectF(working->x_pos, working->y_pos, 60, 60), QPen(working->color), QBrush(working->color));
			QString str = QString::number((int)working->value);
			QGraphicsSimpleTextItem* value = graphicsScene->addSimpleText(str, font);
			value->setPos(working->x_pos + 10, working->y_pos + 10);
			working->drawn = true;
		}
		//Если левый потомок есть и не нарисован идём в него
		if ((working->left != nullptr) && (working->left->drawn == false)) 
		{
			graphicsScene->addLine(QLineF(working->x_pos + 30, working->y_pos + 60, working->left->x_pos + 30, working->left->y_pos), QPen(Qt::darkBlue,3));
			working = working->left;
			f = true;
			continue;
		}
		//Если правый потомок есть и не нарисован идём в него
		if ((working->right != nullptr) && (working->right->drawn == false))
		{
			graphicsScene->addLine(QLineF(working->x_pos + 30, working->y_pos + 60, working->right->x_pos + 30, working->right->y_pos), QPen(Qt::darkBlue, 3));
			working = working->right;
			continue;
		}
		//Если потомков нет или уже нарисованы идём в родителя
		working = working->parentnode;
	} while (working->drawable);	//Пока не вернёмся в иск. корень
	current.tree->clear_drawn(current.tree);//Снимаем метки отрисовки
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
	//Тут вся логика демонстрации
	QString qs = ui->textEdit->toPlainText();
	unsigned int value = qs.toUInt();
	
	if (calculate_search_steps(value))	//Считаем все шаги
	{
		if (analysis())
		{
			calculate_search_min_steps();
			calculate_delete_min_steps();
		}
	}
	cadre t;
	t.tree = copy_tree(current.tree);	//Искуственные 2 шага в конце гарантируют что шаги будут
	t.comment = QString::fromUtf8(u8"Вершина удалена!\n");
	demo.push_back(t);
	t.comment = "";
	demo.push_back(t);
	ind = 1;
	paint(demo[ind]);					//Выводим шаг с индексом 1(по индексу 0 исходное дерево)
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
	working = working->left;			//Выходим в реальный корень
	do
	{
		working->color = Qt::red;		
		current.comment = QString::fromUtf8(u8"Проверим вершину ") + QString::number(working->value);
		cadre t;
		t.tree = copy_tree(current.tree);
		t.comment = current.comment;
		demo.push_back(t);
		if (working->value == value)	//Если нашли то завершаем успешно
		{
			current.comment = QString::fromUtf8(u8"Ключи совпадают, поиск завершён");
			t.tree = copy_tree(current.tree);
			t.comment = current.comment;
			demo.push_back(t);
			active = working;
			return true;
		}
		else
		{
			if(value < working->value)//Если налево то идём налево
			{
				current.comment = QString::fromUtf8(u8"Ключ меньше чем у текущей вершины, идём налево");
				t.tree = copy_tree(current.tree);
				t.comment = current.comment;
				demo.push_back(t);
				working->color = Qt::blue;
				if (working->left == nullptr) //Но если налево пути нет то не идём
				{
					current.comment = QString::fromUtf8(u8"Слева нет потомка, поиск неудачный");
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
											//То же самое направо
			{
				current.comment = QString::fromUtf8(u8"Ключ больше чем у текущей вершины, идём направо");
				t.tree = copy_tree(current.tree);
				t.comment = current.comment;
				demo.push_back(t);
				working->color = Qt::blue;
				if (working->right == nullptr)
				{
					current.comment = QString::fromUtf8(u8"Cправа нет потомка, поиск неудачный");
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
	if ((active->left == nullptr) && (active->right == nullptr))	//Если нет потомков всё просто
	{

		t.tree = copy_tree(current.tree);
		t.comment = QString::fromUtf8(u8"У вершины нет потомков, просто удаляем её\n");
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
		if ((active->left != nullptr) && (active->right != nullptr))//Если  потомков 2 то считать будем в другом месте
		{
			t.tree = copy_tree(current.tree);
			t.comment = QString::fromUtf8(u8"У вершины два потомка\n");
			demo.push_back(t);
			return true;
		}
		//Если потомок 1(левый или правый) удалитб тоже можно на месте, заменой на потомка
		else
		{
			if (active->left != nullptr)
			{
				t.comment = QString::fromUtf8(u8"У вершины только левый потомок, замещаем вершину им\n");
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
				t.comment = QString::fromUtf8(u8"У вершины только правый потомок, замещаем вершину им\n");
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
	//В принципе в строках всё написано
	cadre t;
	active->color = Qt::blue;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"Найдём наименьшую вершину справа от удаляемой\n");
	demo.push_back(t);
	min = active->right;
	min->color = Qt::red;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"Идём налево пока есть левые потомки\n");
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
	t.comment = QString::fromUtf8(u8"Найдена минимальная вершина справа от удаляемой\n");
	demo.push_back(t);
}
void Demostration::calculate_delete_min_steps()
{
	//1)Заменяем активный минимальным(значение)
	cadre t;
	active->value = min->value;
	active->color = Qt::red;
	t.tree = copy_tree(current.tree);
	t.comment = QString::fromUtf8(u8"Заменяем удаляемую вершину минимальной справа\n");
	demo.push_back(t);
	//2)Сохраняем все данные минимальной для отрисовки
	active->color = Qt::blue;
	int save_x_pos = min->x_pos;
	int save_y_pos = min->y_pos;
	int save_l = min->length_line;
	//3) Если у минимальной нет потомков,просто сносим её
	if ((min->left == nullptr) && (min->right == nullptr))
	{
		t.tree = copy_tree(current.tree);
		t.comment = QString::fromUtf8(u8"У минимальной вершины нет потомков, просто удаляем её\n");
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
	//4)Если потомок есть то (для левого)
	else
	{
		//1)Заменяем ссылку на родителя у потомка минимальной
		//2)Заменяем ссылку на левого потомка у родителя минимальной
		//3)Заменяем минимальную
		//4)Так как значения отрисовки хранятся в вершинах записываем минимальной её сохраненные
		//Чтобы она на картинке не уехала
		if (min->left != nullptr)
		{
			t.comment = QString::fromUtf8(u8"У минимальной вершины только левый потомок, замещаем вершину им\n");
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
			t.comment = QString::fromUtf8(u8"У вершины только правый потомок, замещаем вершину им\n");
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