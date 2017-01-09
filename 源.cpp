#include"BigInteger.h"
#include<iostream>
using namespace std;
#include<fstream>

const char* fileA = "a.txt";
const char* fileB = "b.txt";
const char* fileHistory = "history.txt";
BigInteger a, b,c;//分别为a b 还有结果c
char lastOperator = '+';	//最后一次的运算符

//打印菜单
void printMenu(){
	cout << endl;
	cout << "=================这是大整数哦===============" << endl;
	cout << " 1.从键盘输入(并存到文件中)两个大整数并计算" << endl;
	cout << " 2.从文件读取两个大整数并计算" << endl;
	cout << " 3.查看a和b两数对应文件" << endl;
	cout << " 4.查看历史计算结果" << endl;
	cout << " 5.删除历史计算结果文件" << endl;
	cout << " 6.退出系统" << endl;
	cout << "============================================" << endl;
	cout << " >>请输入您的选择:" << endl;
}

//清屏的函数,调用系统的清屏功能
void clearScreen()
{
	system("cls");
}
//将a和b写入到文件中
void writeToFile()
{
	ofstream outfile;
	//打开文件的同时清空文件
	outfile.open(fileA, ios::trunc);
	int i = 0;//循环变量

	if (a.getSign() == false)
		outfile << "-";
	for (int i = a.getCount()-1; i >= 0; i--)
	{
		outfile << a.getValue()[i];
	}
	outfile.close();
	outfile.open(fileB, ios::trunc);

	if (b.getSign() == false)
		outfile << "-";
	for (int i = b.getCount() - 1; i >= 0; i--)
	{
		outfile << b.getValue()[i];
	}
	outfile.close();
}
//将a和b以及运算结果写入history.txt中
void writeResultToHistory()
{
	ofstream outfile;
	//打开文件的同时清空文件
	outfile.open(fileHistory, ios::app);
	outfile << endl;
	int i = 0;//循环变量
	if (a.getSign() == false)
		outfile << "-";
	for (int i = a.getCount() - 1; i >= 0; i--)
	{
		outfile << a.getValue()[i];
	}

	outfile << " " << lastOperator << " ";	//运算符

	if (b.getSign() == false)
		outfile << "-";
	for (int i = b.getCount() - 1; i >= 0; i--)
	{
		outfile << b.getValue()[i];
	}

	outfile << " = ";

	if (c.getSign() == false)
		outfile << "-";
	for (int i = c.getCount() - 1; i >= 0; i--)
	{
		outfile << c.getValue()[i];
	}

	outfile.close();
}
//从文件读a和b的数据
void readFromFile(){
	ifstream infile;
	infile.open(fileA, ios::in);
	//如果打开文件失败
	if (infile.fail())
	{
		cout << "没有存档文件信息或打开失败！" << endl;
		return;
	}
	//如果文件不为空,读取到A
	char charA[MAX_LENGTH];
	if (!infile.eof())
		infile >> charA;
	a = BigInteger(charA);
	infile.close();
	//读取B
	infile.open(fileB, ios::in);
	//如果打开文件失败
	if (infile.fail())
	{
		cout << "没有存档文件信息或打开失败！" << endl;
		return;
	}
	//如果文件不为空,读取到B
	char charB[MAX_LENGTH];
	if (!infile.eof())
		infile >> charB;
	b = BigInteger(charB);
	infile.close();


}
//打印加减乘除子菜单
void printSubMenu()
{
	cout << "***********************" << endl;
	cout << "*  1.加法             *" << endl;
	cout << "*  2.减法             *" << endl;
	cout << "*  3.乘法             *" << endl;
	cout << "*  4.除法             *" << endl;
	cout << "*  5.上述四则运算     *" << endl;
	cout << "***********************" << endl;
	cout << "请输入要选择的运算:";
}

//计算a和b的四则运算并输出结果
void calcAndPrintResult()
{
	cout << "a为:";
	a.print(); cout << endl;
	cout << "b为:";
	b.print(); cout << endl;
	printSubMenu();
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "两数相加的结果为:";
		c = a.add(b);
		c.print(); cout << endl;
		lastOperator = '+';
		writeResultToHistory();
		break;
	case 2:
		cout << "两数相减的结果为:";
		c = a.sub(b);
		c.print(); cout << endl;
		lastOperator = '-';
		writeResultToHistory();
		break;
	case 3:
		cout << "两数相乘的结果为:";
		c = a.mult(b);
		c.print(); cout << endl;
		lastOperator = '*';
		writeResultToHistory();
		break;
	case 4:
		cout << "两数相除的结果为;";
		c = a.div(b);
		c.print(); cout << endl;
		lastOperator = '/';
		writeResultToHistory();
		break;
	case 5:
		cout << "两数相加的结果为:";
		c = a.add(b);
		c.print(); cout << endl;
		lastOperator = '+';
		writeResultToHistory();
		cout << "两数相减的结果为:";
		c = a.sub(b);
		c.print(); cout << endl;
		lastOperator = '-';
		writeResultToHistory();
		cout << "两数相乘的结果为:";
		c = a.mult(b);
		c.print(); cout << endl;
		lastOperator = '*';
		writeResultToHistory();
		cout << "两数相除的结果为;";
		c = a.div(b);
		c.print(); cout << endl;
		lastOperator = '/';
		writeResultToHistory();
		break;
	default:
		cout << "你看看自己输入的是什么,欺负我不认数字喽? 哼!" << endl;
	}

	
}


int main()
{

	system("color 0E");
	int choice = 0;
	while (choice != 6){
		clearScreen();	//清屏
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "请输入一个大整数:";
			char bigInteger[MAX_LENGTH];
			cin >> bigInteger;
			a = BigInteger(bigInteger);
			cout << "请输入另一个大整数:";
			cin >> bigInteger;
			b = BigInteger(bigInteger);
			writeToFile();
			calcAndPrintResult();
			break;
		case 2:
			readFromFile();
			calcAndPrintResult();
			break;
		case 3:
			system("start a.txt");
			system("start b.txt");
			break;
		case 4:
			system("start history.txt");
			break;
		case 5:
			system("del /f /q /s history.txt");	//删除文件
			break;
		case 6:
			cout << "感谢您使用本系统,按任意键结束!" << endl;
			system("pause>nul");
			exit(1);
			break;
		default:
			cout << "喂喂喂我不认识你输入的东西呀." << endl;
			break;
		}
		cout << "按任意键继续!" << endl;
		system("pause>nul");		//在结束的时候暂停,让用户看到数据
	}
	return 0;
}

