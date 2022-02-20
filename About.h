#pragma once

#include <QWidget>
#include "ui_About.h"

class About : public QWidget
{
	Q_OBJECT

public:
	About(QWidget *parent = Q_NULLPTR);
	~About();
private slots: 
	void on_menuButton_clicked();
signals:
	void menuButton_clicked();
private:
	Ui::About* ui;
};
