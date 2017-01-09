#include"BigInteger.h"
#include<iostream>
using namespace std;
#include<fstream>

const char* fileA = "a.txt";
const char* fileB = "b.txt";
const char* fileHistory = "history.txt";
BigInteger a, b,c;//�ֱ�Ϊa b ���н��c
char lastOperator = '+';	//���һ�ε������

//��ӡ�˵�
void printMenu(){
	cout << endl;
	cout << "=================���Ǵ�����Ŷ===============" << endl;
	cout << " 1.�Ӽ�������(���浽�ļ���)����������������" << endl;
	cout << " 2.���ļ���ȡ����������������" << endl;
	cout << " 3.�鿴a��b������Ӧ�ļ�" << endl;
	cout << " 4.�鿴��ʷ������" << endl;
	cout << " 5.ɾ����ʷ�������ļ�" << endl;
	cout << " 6.�˳�ϵͳ" << endl;
	cout << "============================================" << endl;
	cout << " >>����������ѡ��:" << endl;
}

//�����ĺ���,����ϵͳ����������
void clearScreen()
{
	system("cls");
}
//��a��bд�뵽�ļ���
void writeToFile()
{
	ofstream outfile;
	//���ļ���ͬʱ����ļ�
	outfile.open(fileA, ios::trunc);
	int i = 0;//ѭ������

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
//��a��b�Լ�������д��history.txt��
void writeResultToHistory()
{
	ofstream outfile;
	//���ļ���ͬʱ����ļ�
	outfile.open(fileHistory, ios::app);
	outfile << endl;
	int i = 0;//ѭ������
	if (a.getSign() == false)
		outfile << "-";
	for (int i = a.getCount() - 1; i >= 0; i--)
	{
		outfile << a.getValue()[i];
	}

	outfile << " " << lastOperator << " ";	//�����

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
//���ļ���a��b������
void readFromFile(){
	ifstream infile;
	infile.open(fileA, ios::in);
	//������ļ�ʧ��
	if (infile.fail())
	{
		cout << "û�д浵�ļ���Ϣ���ʧ�ܣ�" << endl;
		return;
	}
	//����ļ���Ϊ��,��ȡ��A
	char charA[MAX_LENGTH];
	if (!infile.eof())
		infile >> charA;
	a = BigInteger(charA);
	infile.close();
	//��ȡB
	infile.open(fileB, ios::in);
	//������ļ�ʧ��
	if (infile.fail())
	{
		cout << "û�д浵�ļ���Ϣ���ʧ�ܣ�" << endl;
		return;
	}
	//����ļ���Ϊ��,��ȡ��B
	char charB[MAX_LENGTH];
	if (!infile.eof())
		infile >> charB;
	b = BigInteger(charB);
	infile.close();


}
//��ӡ�Ӽ��˳��Ӳ˵�
void printSubMenu()
{
	cout << "***********************" << endl;
	cout << "*  1.�ӷ�             *" << endl;
	cout << "*  2.����             *" << endl;
	cout << "*  3.�˷�             *" << endl;
	cout << "*  4.����             *" << endl;
	cout << "*  5.������������     *" << endl;
	cout << "***********************" << endl;
	cout << "������Ҫѡ�������:";
}

//����a��b���������㲢������
void calcAndPrintResult()
{
	cout << "aΪ:";
	a.print(); cout << endl;
	cout << "bΪ:";
	b.print(); cout << endl;
	printSubMenu();
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "������ӵĽ��Ϊ:";
		c = a.add(b);
		c.print(); cout << endl;
		lastOperator = '+';
		writeResultToHistory();
		break;
	case 2:
		cout << "��������Ľ��Ϊ:";
		c = a.sub(b);
		c.print(); cout << endl;
		lastOperator = '-';
		writeResultToHistory();
		break;
	case 3:
		cout << "������˵Ľ��Ϊ:";
		c = a.mult(b);
		c.print(); cout << endl;
		lastOperator = '*';
		writeResultToHistory();
		break;
	case 4:
		cout << "��������Ľ��Ϊ;";
		c = a.div(b);
		c.print(); cout << endl;
		lastOperator = '/';
		writeResultToHistory();
		break;
	case 5:
		cout << "������ӵĽ��Ϊ:";
		c = a.add(b);
		c.print(); cout << endl;
		lastOperator = '+';
		writeResultToHistory();
		cout << "��������Ľ��Ϊ:";
		c = a.sub(b);
		c.print(); cout << endl;
		lastOperator = '-';
		writeResultToHistory();
		cout << "������˵Ľ��Ϊ:";
		c = a.mult(b);
		c.print(); cout << endl;
		lastOperator = '*';
		writeResultToHistory();
		cout << "��������Ľ��Ϊ;";
		c = a.div(b);
		c.print(); cout << endl;
		lastOperator = '/';
		writeResultToHistory();
		break;
	default:
		cout << "�㿴���Լ��������ʲô,�۸��Ҳ��������? ��!" << endl;
	}

	
}


int main()
{

	system("color 0E");
	int choice = 0;
	while (choice != 6){
		clearScreen();	//����
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "������һ��������:";
			char bigInteger[MAX_LENGTH];
			cin >> bigInteger;
			a = BigInteger(bigInteger);
			cout << "��������һ��������:";
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
			system("del /f /q /s history.txt");	//ɾ���ļ�
			break;
		case 6:
			cout << "��л��ʹ�ñ�ϵͳ,�����������!" << endl;
			system("pause>nul");
			exit(1);
			break;
		default:
			cout << "ιιι�Ҳ���ʶ������Ķ���ѽ." << endl;
			break;
		}
		cout << "�����������!" << endl;
		system("pause>nul");		//�ڽ�����ʱ����ͣ,���û���������
	}
	return 0;
}

