#include "TestingQT.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TestingQT wgt;
	wgt.show();
	return a.exec();
}
