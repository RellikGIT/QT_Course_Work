#include <qtextcodec.h>
#include <random>

#include "Testing.h"
#include "OpenQuestion.h"
#include "ClosedQuestion.h"
const std::string path = "test//base.txt";
const std::string path2 = "test//baseDC.txt";
int test_mark_5(int mark, int max_mark);	
Testing::Testing(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Testing)
{
	//Много всякой уи фигни
	ui->setupUi(this);
	test = load_test_from_base(parent);
	
	boxes.push_back(ui->checkBox);
	boxes.push_back(ui->checkBox_2);
	boxes.push_back(ui->checkBox_3);
	boxes.push_back(ui->checkBox_4);
	boxes.push_back(ui->checkBox_5);
	boxes.push_back(ui->checkBox_6);
	boxes.push_back(ui->checkBox_7);
	boxes.push_back(ui->checkBox_8);
	boxes.push_back(ui->checkBox_10);
	for (int i = 0; i < boxes.size(); ++i)
		boxes[i]->setVisible(false);
	ui->answerSumbitButton->setVisible(false);
	ui->plainAnswer->setVisible(false);
	ui->answerSumbitButton->setVisible(false);
	ui->testprevQuestionButton->setVisible(false);
	ui->testprevQuestionButton_2->setVisible(false);
	ui->test_endButton->setVisible(false);

	ui->plainLabel->setVisible(false);
	ui->plainLabel_2->setVisible(false);
	ui->plainLabel_3->setVisible(false);
	ui->plainLabel_4->setVisible(false);
	ui->plain0->setVisible(false);
	ui->plain1->setVisible(false);
	ui->plain2->setVisible(false);
	ui->plain3->setVisible(false);
	ui->checkBox_9->setVisible(false);
	ui->test_settingsButton_2->setVisible(false);

	mode = false;
	diff = 1;
	test_size = 10;
	ind = 0;
	max_ind = test_size - 1;
	timer = 0;
	start = std::chrono::system_clock::now();
}

Testing::~Testing()
{
	delete ui;
}
void Testing::on_test_menuButton_clicked()
{
	setVisible(false);
	emit test_menuButton_clicked();
}
void Testing::on_test_startButton_clicked()
{
	on_test_settingsButton_2_clicked();
	ui->test_startButton->setVisible(false);
	ui->plain0->setVisible(true);
	ui->answerSumbitButton->setVisible(true);
	ui->testprevQuestionButton->setVisible(true);
	ui->testprevQuestionButton_2->setVisible(true);
	
	ui->test_settingsButton->setVisible(false);
	if (mode) ui->test_menuButton->setVisible(false);
	//Выборка и вывод теста
	shuffle_test();
	cut_test();
	display_question(test[ind]);
	start = std::chrono::system_clock::now();
}
void Testing::on_test_settingsButton_clicked()
{
	ui->plainLabel->setVisible(true);
	ui->plainLabel_2->setVisible(true);
	ui->plainLabel_3->setVisible(true);
	ui->plainLabel_4->setVisible(true);
	ui->plain1->setVisible(true);
	ui->plain2->setVisible(true);
	ui->plain3->setVisible(true);
	ui->checkBox_9->setVisible(true);
	ui->test_settingsButton_2->setVisible(true);
}
void Testing::on_test_settingsButton_2_clicked()
{
	ui->plainLabel->setVisible(false);
	ui->plainLabel_2->setVisible(false);
	ui->plainLabel_3->setVisible(false);
	ui->plainLabel_4->setVisible(false);
	ui->plain1->setVisible(false);
	ui->plain2->setVisible(false);
	ui->plain3->setVisible(false);
	ui->checkBox_9->setVisible(false);
	ui->test_settingsButton_2->setVisible(false);

	//Сохранение введённых настроек
	QString qs = ui->plain1->toPlainText();
	test_size = qs.toUInt();
	if ((test_size <= 0) || (test_size > 25))
	{
		test_size = 10;
	}
	qs = ui->plain2->toPlainText();
	diff = qs.toUInt();
	if ((diff < 1) || (diff > 3)) diff = 1;
	qs = ui->plain3->toPlainText();
	timer = qs.toInt();
	if (timer < 0) timer = 0;
	mode = ui->checkBox_9->isChecked();
}
void Testing::on_answerSumbitButton_clicked()
{
	QString ans = ui->plainAnswer->toPlainText();
	std::vector <bool> ansv;
	ansv.push_back(ui->checkBox->isChecked());
	ansv.push_back(ui->checkBox_2->isChecked());
	ansv.push_back(ui->checkBox_3->isChecked());
	ansv.push_back(ui->checkBox_4->isChecked());
	ansv.push_back(ui->checkBox_5->isChecked());
	ansv.push_back(ui->checkBox_6->isChecked());
	ansv.push_back(ui->checkBox_7->isChecked());
	ansv.push_back(ui->checkBox_8->isChecked());
	ansv.push_back(ui->checkBox_10->isChecked());
	test[ind]->mark = test[ind]->check_ans(ans, ansv);
	test[ind]->answered = true;
	bool clear = true;
	//Если на все вопросы ответили то можно и завершать
	for (int i = 0; i <= max_ind; ++i)
		if (test[i]->answered == false)
		{
			clear = false;
			break;
		} 
	if (clear) ui->test_endButton->setVisible(true);
	if (check_time()) on_test_endButton_clicked();
}
void Testing::on_test_endButton_clicked()
{
	ui->test_startButton->setVisible(true);
	ui->plain0->setVisible(false);
	ui->answerSumbitButton->setVisible(false);
	ui->testprevQuestionButton->setVisible(false);
	ui->testprevQuestionButton_2->setVisible(false);
	ui->test_endButton->setVisible(false);
	ui->test_settingsButton->setVisible(true);
	ui->test_menuButton->setVisible(true);
	display_empty();
	//Считаем оценки, выводим результаты
	int total_mark = 0;
	int total_max_mark = 0;
	for (int i = 0; i <= max_ind; ++i)
	{
		total_mark += test[i]->mark;
		total_max_mark += test[i]->max_mark();

	}
	if (check_time())
		ui->questionText->setPlainText(QString::fromUtf8(u8"Вы не уложились по времени!!!"));
	else
	{
		QString first = QString::fromUtf8(u8"Результат: баллов набрано ") + QString::number(total_mark) + QString::fromUtf8(u8" из ") + QString::number(total_max_mark) + QString::fromUtf8(u8"\n");
		QString second = QString::fromUtf8(u8"Оценка: ") + QString::number(test_mark_5(total_mark, total_max_mark));
		ui->questionText->setPlainText(first + second);
	}
	clear_test();
	clear_ans();
}
void read_file()//Считывает базу и дешифрует в отдельный временный файл
{
	using namespace std;
	ifstream is(path);
	ofstream os(path2);
	vector <string> file_v;
	if (is.is_open())
	{
		char buff[255];
		while (!is.eof())
		{
			is.getline(buff, 255);
			string s(buff);
			file_v.push_back(s);
		}
		is.close();
	}
	for (unsigned i = 0; i < file_v.size(); ++i)
	{
		for (unsigned int j = 0; j < file_v[i].length(); j += 2)
			if (j + 1 < file_v[i].length())
				swap(file_v[i][j], file_v[i][j + 1]);
	}
	for (unsigned int i = 0; i < file_v.size() - 1; ++i)
		os << file_v[i] << "\n";
	os << file_v[file_v.size() - 1];
	os.close();
	
}
std::vector<Question*> load_test_from_base(QObject* parent)
{
	using namespace std;
	vector <Question*> ret;
	vector <answer> curr_ans;
	answer curr;
	string curr_text;
	bool curr_type;
	int current_diff;
	read_file();
	ifstream is(path2);
	if (is.is_open())
	{
		char buff[255];
		while (!is.eof())
		{
			is.getline(buff, 255);					//Считать текст вопроса
			string s(buff);
			
			curr_text = s;
			is.getline(buff, 255);
			current_diff = buff[0] - 48;			//Сложность
			is.getline(buff, 255);
			string s1(buff);
			curr_type = (s1 == "закрытый");//Тип
			if (curr_type)							//Закрытый вопрос
			{
				int i = 0; is.getline(buff, 255); i = buff[0] - 48;
				for (int j = 0; j < i; ++j)			//Считать количество ВО
				{
					is.getline(buff, 255);			//Считать вариант
					curr.right_ans = buff[0] == '+';//Правильный ли
					buff[0] = ' ';					
					string s2(buff);					
					curr.ans = s2;
					curr_ans.push_back(curr);		//Записать вариант ответа в вопрос
				}
				ret.push_back(new ClosedQuestion(parent, curr_text, curr_ans, current_diff));//Записать вопрос в вектор
			}
			else
			{										//Открытый вопрос
				is.getline(buff, 255);				//Считать эталонный ответ
				string s3(buff);
				curr.ans = s3;
				curr.right_ans = true;
				curr_ans.push_back(curr);			//Записать в вопрос
				ret.push_back(new OpenQuestion(parent, curr_text, curr_ans, current_diff));//Записать вопрос в вектор
			}
			curr_ans.clear();
		}
		is.close();
	}
	ofstream os(path2);	//Чистим расшифрованную базу
	os.close();
	return ret;
}
void Testing::display_question(Question* q)
{
	display_empty();
	ui->plain0->setPlainText(QString::fromUtf8(u8"Вопрос №") + QString::number(ind + 1));
	QTextCodec* codec = QTextCodec::codecForName("CP1251");
	QByteArray ba(q->text.c_str());              // Convert to QByteArray
	QString msg = codec->toUnicode(ba);          // Qt magic !!! 
	ui->questionText->setText(msg);
	if (q->type)
	{
		q->shuffle_answers();
		for (int i = 0; i < q->answers.size(); ++i)
		{
			boxes[i]->setVisible(true);
			QByteArray ba(q->answers[i].ans.c_str());    // Convert to QByteArray
			QString msg = codec->toUnicode(ba);          // Qt magic !!! 
			boxes[i]->setText(msg);
		}	
	}
	else
	{
		ui->plainAnswer->setVisible(true);
	}
	
}
void Testing::display_empty()
{
	ui->plain0->setPlainText("");
	ui->questionText->setText("");
	ui->plainAnswer->setVisible(false);
	for (int i = 0; i < boxes.size(); ++i)
		boxes[i]->setVisible(false);
}
void Testing::shuffle_test()
{
	using namespace std;
	mt19937 gen(unsigned(time(nullptr)));
	for (int i = 0; i < test.size() - 1; ++i)
	{
		uniform_int_distribution<int> uid(i, test.size() - 2);
		swap(test[i], test[uid(gen)]);
	}
}
void Testing::cut_test()
{
	max_ind = std::min(test.size() - 1, (size_t)(test_size - 1)); //А это чтобы за базу не вылезти
	ind = 0;
}
void Testing::on_testprevQuestionButton_clicked()
{
	if (ind > 0)
	{
		ind--;
		display_question(test[ind]);
		clear_ans();
	}
	if (check_time()) on_test_endButton_clicked();
}
void Testing::on_testprevQuestionButton_2_clicked()
{
	if (ind < max_ind)
	{
		ind++;
		display_question(test[ind]);
		clear_ans();
	}
	if (check_time()) on_test_endButton_clicked();
}
void Testing::clear_ans()
{
	ui->checkBox->setChecked(false);
	ui->checkBox_2->setChecked(false);
	ui->checkBox_3->setChecked(false);
	ui->checkBox_4->setChecked(false);
	ui->checkBox_5->setChecked(false);

	ui->checkBox_6->setChecked(false);
	ui->checkBox_7->setChecked(false);
	ui->checkBox_8->setChecked(false);
	ui->checkBox_10->setChecked(false);
	ui->plainAnswer->setPlainText("");
}
void Testing::clear_test()
{
	for (int i = 0; i <= max_ind; ++i)
	{
		test[i]->mark = 0;
		test[i]->answered = false;
	}
}
bool Testing::check_time()
{
	if (timer == 0) return false;
	auto crnt = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = crnt - start;
	auto x = std::chrono::duration_cast<std::chrono::minutes>(diff).count();
	return (x >= timer);

}
int test_mark_5(int mark, int max_mark) //Оценка по 5 бальной
{
	double markd = mark;
	double mmarkd = max_mark;
	if ((markd / mmarkd) >= 0.9) return 5;
	if ((markd / mmarkd) >= 0.75) return 4;
	if ((markd / mmarkd) >= 0.6) return 3;
	if ((markd / mmarkd) >= 0.4) return 2;
	if ((markd / mmarkd) >= 0.1) return 1;
	return 0;
}