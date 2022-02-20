#include "About.h"

About::About(QWidget *parent)
	: QWidget(parent), 
	ui(new Ui::About)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

About::~About()
{
	delete ui;
}

void About::on_menuButton_clicked()
{
	this->close();
	emit menuButton_clicked();

}