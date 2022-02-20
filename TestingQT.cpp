#include "TestingQT.h"

TestingQT::TestingQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	testW = new Testing(this);
	connect(testW, SIGNAL(test_menuButton_clicked()), this, SLOT(mainMenu()));
	testW->setVisible(false);
	demoW = new Demostration(this);
	demoW->setVisible(false);
	connect(demoW, SIGNAL(menuButton_3_clicked()), this, SLOT(mainMenu()));
	theoryW = new Theory(this);
	theoryW->setVisible(false);
	connect(theoryW, SIGNAL(menuButton_theory_clicked()), this, SLOT(mainMenu()));
}
void TestingQT::on_theoryButton_clicked()
{
	ui.centralWidget->setVisible(false);
	theoryW->show();
}
void TestingQT::on_aboutButton_clicked()
{
	ui.centralWidget->setVisible(false);
	aboutW = new About(this);
	connect(aboutW, SIGNAL(menuButton_clicked()), this, SLOT(mainMenu()));
	aboutW->show();
}
void TestingQT::on_helpButton_clicked()
{
	ui.centralWidget->setVisible(false);
	helpW = new Help(this);
	connect(helpW, SIGNAL(menuButton_2_clicked()), this, SLOT(mainMenu()));
	helpW->show();
}
void TestingQT::on_demonstrationButton_clicked()
{
	ui.centralWidget->setVisible(false);
	demoW->show();
}
void TestingQT::mainMenu()
{
	ui.centralWidget->setVisible(true);
}
void TestingQT::on_testButton_clicked()
{
	ui.centralWidget->setVisible(false);
	testW->show();
}