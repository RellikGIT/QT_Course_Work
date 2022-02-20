#pragma once

#include <QWidget>
#include <QGraphicsView>
#include <vector>
#include "ui_Demostration.h"
#include "TreeNode.h"
struct cadre											//Кадр- состояние демонстрации
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
	void paint();										//Отрисовка дерева и комментария
	void paint(cadre c);								//То же самое только выбранного кадра
	bool calculate_search_steps(unsigned int value);	//Расчёт шагов поиска элемента
	bool analysis();									//Шаги анализа
	void calculate_search_min_steps();					//Шаги поиска минимального справа от удаляеемого
	void calculate_delete_min_steps();					//Шаги удаления минимального справа от удаляеемого
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
	Ui::Demostration* ui;								//Уи
	QGraphicsScene* graphicsScene;						//Графика
	cadre current;										//Текущий кадр
	std::vector<cadre> demo;							//Все кадры
	TreeNode* active;									//Вершина удаляемая
	TreeNode* min;										//Минимальная справа от active
	int ind;											//Индекс в demo

};
