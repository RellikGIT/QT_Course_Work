#pragma once

#include <QWidget>
#include "ui_Theory.h"

class Theory : public QWidget
{
	Q_OBJECT
private slots:
	void on_menuButton_theory_clicked();
signals:
	void menuButton_theory_clicked();

public:
	Theory(QWidget *parent = Q_NULLPTR);
	~Theory();

private:
	Ui::Theory* ui;

};
