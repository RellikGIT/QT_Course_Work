#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestingQT.h"
#include "About.h"
#include "Help.h"
#include "Demostration.h"
#include "Testing.h"
#include "Theory.h"
class TestingQT : public QMainWindow
{
	Q_OBJECT

public:
	TestingQT(QWidget *parent = Q_NULLPTR);
private slots:
	void on_aboutButton_clicked();
	void on_helpButton_clicked();
	void on_demonstrationButton_clicked();
	void mainMenu();
	void on_testButton_clicked();
	void on_theoryButton_clicked();
signals :
	void aboutButton_clicked();
	void helpButton_clicked();
	void demonstrationButton_clicked();
	void testButton_clicked();
	void theoryButton_clicked();
private:
	Ui::TestingQTClass ui;
	About* aboutW;
	Help* helpW;
	Demostration* demoW;
	Testing* testW;
	Theory* theoryW;
};
