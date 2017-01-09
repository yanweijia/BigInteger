#include"BigInteger.h"
#include<cstring>
#include<iostream>
using namespace std;
//Ĭ�Ϲ��캯��
BigInteger::BigInteger(){
	for (int i = 0; i < MAX_LENGTH; i++){
		this->value[i] = 0;
		this->sign = true;
		this->count = 0;
	}
}

//���������캯��,һ�����������ַ���
BigInteger::BigInteger(char * bigInteger){
	//�ж��ַ�������(λ��)
	int length = strlen(bigInteger);
	
	//ȡ��һ���ַ�,�ж��Ƿ�Ϊ����
	char firstChar = bigInteger[0];
	if (firstChar == '+' || firstChar == '-'){
		if (firstChar == '+')
			this->sign = true;
		else
			this->sign = false;
		this->count = length - 1;	//λ��
		for (int i = 0; i < length - 1; i++){
			//�����ʼ��
			this->value[i] = bigInteger[length - 1 - i]-48;//��48��ASCII
		}
		for (int j = length-1; j < MAX_LENGTH; j++){
			this->value[j] = 0;
		}
		return;
	}
	else{
		//��û�и�������λ,Ĭ��������
		this->sign = true;
		this->count = length;
		for (int i = 0; i < length ; i++){
			this->value[i] = bigInteger[length - 1-i]-48;//charתintҪ��48
		}
		for (int j = length; j < MAX_LENGTH; j++){
			this->value[j] = 0;
		}
	}

}
//�����ִ�ӡ����Ļ��
void BigInteger::print()
{
	if (this->sign == false && this->value[0] == 0 && (this->count == 0 || this->count == 1))
	{
		cout << "ιιι,����һ���Ƿ�������!";
		return;
	}
		

	cout << " ";
	if (this->sign == false)
		cout << "-";
	for (int i = this->count - 1; i >= 0; i--)
	{
		cout << this->value[i];
	}
	cout << " ";
}
//���캯��
BigInteger::BigInteger(bool _sign, short int _value[], short int _count)
{
	this->sign = _sign;
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		this->value[i] = _value[i];
	}
	this->count = _count;
}
//������ľ���ֵ
BigInteger BigInteger::abs()
{
	short int tempValue[MAX_LENGTH];
	for (int i = 0; i < MAX_LENGTH; i++){
		tempValue[i] = this->value[i];
	}
	BigInteger c(true,tempValue,this->count);
	return c;
}

//�жϸ������Ƿ�Ϊ0
bool BigInteger::isZero(){
	if (this->value[0] == 0 && (this->count == 1 || this->count == 0))
		return true;
	else
		return false;
}

//�Ƚ��������Ĵ�С
short int BigInteger::compare(BigInteger b){
	if (this->sign == true && b.sign == false)
		return 1;
	if (this->sign == false && b.sign == true)
		return -1;
	if (this->sign == true && b.sign == true)
	{
		if (this->count > b.count)
			return 1;
		else if (this->count < b.count)
			return -1;
		else
		{
			int i = this->count - 1;
			for (; i >= 0; i--)
			{
				if (this->value[i]>b.value[i])
					return 1;
				else if (this->value[i] < b.value[i])
					return -1;
			}
			return 0;	//�����û���,��֤�����������
		}
	}
	if (this->sign == false && b.sign == false)
	{
		if (this->count > b.count)
			return -1;
		else if (this->count < b.count)
			return 1;
		else
		{
			int i = this->count - 1;
			for (; i >= 0; i--){
				if (this->value[i]>b.value[i])
					return -1;
				else if (this->value[i] < b.value[i])
					return 1;
			}
			return 0;	//�����û���,��֤�����������
		}
	}
	//���û�з����������,�����,����0
	return 0;
}

//�ӷ�����
BigInteger BigInteger::add(BigInteger b){
	//����������ķ�����ͬ
	if (this->sign == true && b.sign == true || this->sign==false && b.sign==false){
		short int jinwei = 0;
		short int tempValue[MAX_LENGTH] = { 0 };	//��Ž��������
		short max = (this->count>b.count?this->count:b.count);	//maxΪ���λ��
		for (int i = 0; i < max; i++)
		{
			int result = this->value[i] + b.value[i] + jinwei;
			tempValue[i] = result % 10;
			jinwei = result / 10;
		}
		tempValue[max] = jinwei;
		if (jinwei != 0)
			max++;
		BigInteger c(this->sign,tempValue,max);
		return c;
	}
	//���������Ų�ͬ(�жϾ���ֵ��С,�����Ϳ���֪������ķ���λ,֮���ڽ������)
	int compareResult = this->abs().compare(b.abs());	//���߾���ֵ���бȽ�
	if (compareResult == 0){//���������
		BigInteger c("0");
		return c;
	}
	if (compareResult == 1 || compareResult== -1){//��������ֵ����b����С��b���Ľ��
		short int jiewei = 0;	//������Ҫ��λ
		short int tempValue[MAX_LENGTH] = { 0 };	//���������������
		for (int i = 0; i < (compareResult == 1 ? this->count:b.count); i++){
			int result = (compareResult == 1) ? this->value[i] - jiewei - b.value[i] : b.value[i] - jiewei - this->value[i];
			jiewei = 0;
			if (result < 0){
				result += 10;
				jiewei = 1;
			}
			tempValue[i] = result;
		}
		//�������жϽ����λ��
		int tempCount = 1;
		for (tempCount = 128; tempCount > 1; tempCount--){
			if (tempValue[tempCount-1] != 0)
				break;
		}
		//��Ϊ����ķ��ſ϶�Ϊ�ղ��������о���ֵ�Ƚϴ�ķ���
		BigInteger c((compareResult == 1 ? this->sign:b.sign), tempValue, tempCount);
		return c;
	}
	//���Ϊ�����������,�򷵻�һ��0
	BigInteger c("0");
	return c;
}

//��������
BigInteger BigInteger::sub(BigInteger b){
	//����������ķ��Ų�ͬ,�൱��ͬ�����
	if (this->sign == true && b.sign == false || this->sign == false && b.sign == true){
		short int jinwei = 0;
		short int tempValue[MAX_LENGTH] = { 0 };	//��Ž��������
		short max = (this->count>b.count ? this->count : b.count);	//maxΪ���λ��
		for (int i = 0; i < max; i++){
			int result = this->value[i] + b.value[i] + jinwei;
			tempValue[i] = result % 10;
			jinwei = result / 10;
		}
		tempValue[max] = jinwei;
		if (jinwei != 0)
			max++;
		BigInteger c(this->sign, tempValue, max);
		return c;
	}
	
	//������������ͬ,�����жϾ���ֵ��С(�����жϽ������λ),֮�������
	int compareResult = this->abs().compare(b.abs());	//���߾���ֵ���бȽ�
	if (compareResult == 0){//���������
		BigInteger c("0");
		return c;
	}
	if (compareResult == 1 || compareResult == -1){//��������ֵ����b����С��b���Ľ��
		short int jiewei = 0;	//������Ҫ��λ
		short int tempValue[MAX_LENGTH] = { 0 };	//���������������
		for (int i = 0; i < (compareResult == 1 ? this->count : b.count); i++){
			int result = (compareResult == 1) ? this->value[i] - jiewei - b.value[i] : b.value[i] - jiewei - this->value[i];
			jiewei = 0;
			if (result < 0){
				result += 10;
				jiewei = 1;
			}
			tempValue[i] = result;
		}
		//�������жϽ����λ��
		int tempCount = 1;
		for (tempCount = 128; tempCount > 1; tempCount--){
			if (tempValue[tempCount - 1] != 0)
				break;
		}
		//��Ϊ����ķ��ſ϶�Ϊ�ղ��������о���ֵ�Ƚϴ�ķ���
		BigInteger c((compareResult == 1 ? this->sign : !b.sign), tempValue, tempCount);
		return c;
	}
	//���δ�����������,�򷵻�һ��0
	BigInteger c("0");
	return c;
}

//�˷�ת��Ϊ�ַ���������
//�˷�����,����������㷨
BigInteger BigInteger::mult(BigInteger b){
		//�����һ��Ϊ0
	if (this->isZero() || b.isZero()){
		BigInteger c("0");
		return c;
	}
	//���ͬ��,�������λΪ��
	bool resultSign = (this->sign == b.sign) ? true : false;

	char pa[MAX_LENGTH] = { 0 }, pb[MAX_LENGTH] = { 0 };
	for (int i = 0; i < this->count; i++){
		pa[i] = this->value[i]+48;
	}
	pa[this->count] = '\0';
	for (int j = 0; j < b.count; j++){
		pb[j] = b.value[j]+48;
	}
	pb[b.count] = '\0';
	short int resultValue[MAX_LENGTH] = { 0 };        //��Ž����λ,��ʼ��Ϊ0  
	//now��ʾ������(�����b��)�ĵ�now+1λ  
	//temp��ʾ��ǰ���ڼ����λ  
	int now = 0, temp = 0;

	while (pb[now])
	{//δ����pbĩβʱ  
		temp = now;
		int bit = pb[now] - 48;     //0��asicc��Ϊ48  
		int left = 0, sum = 0;      //left��ʾ��λ,sum��ʾ��ǰλ��������ܺ�  
		int aCount = 0;         //aCount��ŵ�ǰ���㵽�����ĵڼ�λ  

		while (pa[aCount] || left)
		{ //��������λ��������� �� û�н�λʱ ��ֹ  
			if (!pa[aCount])
			{//��������λ���������,��λֵ�����������λ  
				resultValue[temp] = left;
				break;
			}
			else
				sum = resultValue[temp] + bit*(pa[aCount] - 48) + left;

			resultValue[temp] = sum % 10;
			left = sum / 10;
			aCount++;
			temp++;
		}
		now++;
		aCount = 0;

	}
	//������λ��
	int resultCount;
	for (resultCount = MAX_LENGTH-1; resultCount > 1; resultCount--){
		if (resultValue[resultCount-1] != 0)
			break;
	}
	BigInteger c(resultSign, resultValue, resultCount);
	return c;
}
//ȡ����������ǰ��λ��,����û����Ҫȡ��λ�����ڴ�����λ�������
BigInteger BigInteger::shiftInt(short int length)
{
	if (length == 0)
		return BigInteger(this->sign, this->value, this->count);
	BigInteger result(this->sign, this->value, this->count);
	for (int i = 0; i < length; i++){
		result = result.mult(BigInteger("10"));
	}
	return result;
}

////��ֵλ����,�����1��ô���������2,�����-1���������-2
//void BigInteger::Zizeng(){
//	if (this->count == 0)
//		count = 1;
//		short int jinwei = 0;
//		short int tempValue[MAX_LENGTH] = { 1 };	//����һ��1
//		for (int i = 0; i < this->count; i++){
//			int result = this->value[i] + tempValue[i] + jinwei;
//			this->value[i] = result % 10;
//			jinwei = result / 10;
//		}
//		this->value[this->count] = jinwei;
//		if (jinwei != 0)
//			this->count++;
//}
////���������,ѭ��,��İ취
//BigInteger BigInteger::div(BigInteger b)
//{
//	//������Ϊ0,����0 ,,����Ϊ0,�����Ϲ���,Ҳ����0��
//	if (this->abs().isZero() || b.abs().isZero())
//	{
//		BigInteger c("0");
//		return c;
//	}
//	//������С�ڳ���,������������Ϊ0,������0
//	if (this->abs().compare(b.abs()) == -1)
//	{
//		BigInteger c("0");
//		return c;
//	}
//	//�����������ֵ���,���� 1��-1
//	if (this->abs().compare(b.abs())==0)
//	{
//		if (this->sign == b.sign){
//			BigInteger c("1");
//			return c;
//		}
//		else{
//			BigInteger c("-1");
//			return c;
//		}
//	}
//	//ʣ�µ������������b�ľ���ֵ��
//	BigInteger divdend(true, this->value, this->count);
//	BigInteger divdor(true, b.getValue(), b.getCount());
//	BigInteger result("-1");
//	while (divdend.getSign() == true)
//	{
//		divdend = divdend.sub(divdor);
//		result.Zizeng();
//	}
//
//	if (this->sign == b.sign)
//		return result;
//	else
//	{
//		return result.getOpposite();
//	}
//}




//���������,���̷�
BigInteger BigInteger::div(BigInteger b)
{
	//������Ϊ0,����0 ,,
	if (this->abs().isZero())
	{
		BigInteger c("0");
		return c;
	}
	//����Ϊ0,�����Ϲ���,����-0 ���Ƿ�ֵ
	if (b.abs().isZero())
	{
		BigInteger c("-0");
		return c;
	}
	//������С�ڳ���,������������Ϊ0,������0
	if (this->abs().compare(b.abs()) == -1)
	{
		BigInteger c("0");
		return c;
	}
	//�����������ֵ���,���� 1��-1
	if (this->abs().compare(b.abs())==0)
	{
		if (this->sign == b.sign)
		{
			BigInteger c("1");
			return c;
		}
		else{
			BigInteger c("-1");
			return c;
		}
	}
	//ʣ�µ������������b�ľ���ֵ��

	//ȡ�������ĳ���
	int aCount = this->count;
	int bCount = b.count;
	int bit = aCount - bCount + 1;//�����λ��
	char* result = new char[bit + 1];
	BigInteger divdend(true,this->value,this->count);	//������
	BigInteger divdor(true, b.value, b.count);	//����
	BigInteger subtracter;	//����
	BigInteger remainder(true, this->value, this->count);	//����
	BigInteger temp;

	for (int i = 0; i < bit; i++)
	{
		int res = 0;
		subtracter = divdor.shiftInt(bit-i-1);	//�����Ժ�ļ���
		temp = remainder.sub(subtracter);
		while (temp.sign == true)
		{
			res++;
			remainder = temp;
			temp = temp.sub(subtracter);
		}
		result[i] = res + '0';
	}
	result[bit] = '\0';
	bool resultSign = (this->sign == b.sign ? true : false);	//�жϽ���ķ���λ
	int resultCount = strlen(result);	//�����λ��
	short int resultValue[MAX_LENGTH] = { 0 };
	for (int i = 0; i < resultCount; i++)
	{
		resultValue[resultCount - i - 1] = result[i]-'0';
	}
	if (resultValue[resultCount-1]==0)
		return BigInteger(resultSign, resultValue, resultCount - 1);
	else
		return BigInteger(resultSign, resultValue, resultCount);
}