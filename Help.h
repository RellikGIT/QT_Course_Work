#pragma once

#include <QWidget>
#include "ui_Help.h"

class Help : public QWidget
{
	Q_OBJECT

public:
	Help(QWidget *parent = Q_NULLPTR);
	~Help();
private slots:
	void on_menuButton_2_clicked();
signals:
	void menuButton_2_clicked();
private:
	Ui::Help* ui;
};
