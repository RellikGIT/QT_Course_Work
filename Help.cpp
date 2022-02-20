#include "Help.h"

Help::Help(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Help)
{
	ui->setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

Help::~Help()
{
	delete ui;
}
void Help::on_menuButton_2_clicked()
{
	this->close();
	emit menuButton_2_clicked();
}