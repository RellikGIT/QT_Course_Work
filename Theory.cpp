#include "Theory.h"
#include <qfile.h>
#include <qtextstream.h>
Theory::Theory(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Theory)
{
	ui->setupUi(this);
	QFile file("1.html");						//��������� ��������� ����
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		ui->textBrowser->setHtml(in.readAll());	//���������� � �������, ������ �� ������������
	}
}

Theory::~Theory()
{
	delete ui;
}
void Theory::on_menuButton_theory_clicked()
{
	this->close();
	emit menuButton_theory_clicked();
}