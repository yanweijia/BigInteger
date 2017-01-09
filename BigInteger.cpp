#include"BigInteger.h"
#include<cstring>
#include<iostream>
using namespace std;
//默认构造函数
BigInteger::BigInteger(){
	for (int i = 0; i < MAX_LENGTH; i++){
		this->value[i] = 0;
		this->sign = true;
		this->count = 0;
	}
}

//带参数构造函数,一个大整数的字符串
BigInteger::BigInteger(char * bigInteger){
	//判断字符串长度(位数)
	int length = strlen(bigInteger);
	
	//取第一个字符,判断是否为符号
	char firstChar = bigInteger[0];
	if (firstChar == '+' || firstChar == '-'){
		if (firstChar == '+')
			this->sign = true;
		else
			this->sign = false;
		this->count = length - 1;	//位数
		for (int i = 0; i < length - 1; i++){
			//数组初始化
			this->value[i] = bigInteger[length - 1 - i]-48;//减48的ASCII
		}
		for (int j = length-1; j < MAX_LENGTH; j++){
			this->value[j] = 0;
		}
		return;
	}
	else{
		//若没有给出符号位,默认是正数
		this->sign = true;
		this->count = length;
		for (int i = 0; i < length ; i++){
			this->value[i] = bigInteger[length - 1-i]-48;//char转int要减48
		}
		for (int j = length; j < MAX_LENGTH; j++){
			this->value[j] = 0;
		}
	}

}
//将数字打印在屏幕上
void BigInteger::print()
{
	if (this->sign == false && this->value[0] == 0 && (this->count == 0 || this->count == 1))
	{
		cout << "喂喂喂,这是一个非法的数字!";
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
//构造函数
BigInteger::BigInteger(bool _sign, short int _value[], short int _count)
{
	this->sign = _sign;
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		this->value[i] = _value[i];
	}
	this->count = _count;
}
//求数组的绝对值
BigInteger BigInteger::abs()
{
	short int tempValue[MAX_LENGTH];
	for (int i = 0; i < MAX_LENGTH; i++){
		tempValue[i] = this->value[i];
	}
	BigInteger c(true,tempValue,this->count);
	return c;
}

//判断该数字是否为0
bool BigInteger::isZero(){
	if (this->value[0] == 0 && (this->count == 1 || this->count == 0))
		return true;
	else
		return false;
}

//比较两个数的大小
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
			return 0;	//如果还没结果,则证明两个数相等
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
			return 0;	//如果还没结果,则证明两个数相等
		}
	}
	//如果没有发生上述结果,则出错,返回0
	return 0;
}

//加法运算
BigInteger BigInteger::add(BigInteger b){
	//如果两个数的符号相同
	if (this->sign == true && b.sign == true || this->sign==false && b.sign==false){
		short int jinwei = 0;
		short int tempValue[MAX_LENGTH] = { 0 };	//存放结果的数组
		short max = (this->count>b.count?this->count:b.count);	//max为最大位数
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
	//两个数符号不同(判断绝对值大小,这样就可以知道结果的符号位,之后在进行相减)
	int compareResult = this->abs().compare(b.abs());	//两者绝对值进行比较
	if (compareResult == 0){//两个数相等
		BigInteger c("0");
		return c;
	}
	if (compareResult == 1 || compareResult== -1){//本数绝对值大于b数或小于b数的结果
		short int jiewei = 0;	//减法需要借位
		short int tempValue[MAX_LENGTH] = { 0 };	//存放相减结果的数组
		for (int i = 0; i < (compareResult == 1 ? this->count:b.count); i++){
			int result = (compareResult == 1) ? this->value[i] - jiewei - b.value[i] : b.value[i] - jiewei - this->value[i];
			jiewei = 0;
			if (result < 0){
				result += 10;
				jiewei = 1;
			}
			tempValue[i] = result;
		}
		//接下来判断结果的位数
		int tempCount = 1;
		for (tempCount = 128; tempCount > 1; tempCount--){
			if (tempValue[tempCount-1] != 0)
				break;
		}
		//因为结果的符号肯定为刚才两个数中绝对值比较大的符号
		BigInteger c((compareResult == 1 ? this->sign:b.sign), tempValue, tempCount);
		return c;
	}
	//如果为发生上述情况,则返回一个0
	BigInteger c("0");
	return c;
}

//减法运算
BigInteger BigInteger::sub(BigInteger b){
	//如果两个数的符号不同,相当于同号相加
	if (this->sign == true && b.sign == false || this->sign == false && b.sign == true){
		short int jinwei = 0;
		short int tempValue[MAX_LENGTH] = { 0 };	//存放结果的数组
		short max = (this->count>b.count ? this->count : b.count);	//max为最大位数
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
	
	//两个数符号相同,则按照判断绝对值大小(用于判断结果符号位),之后再相减
	int compareResult = this->abs().compare(b.abs());	//两者绝对值进行比较
	if (compareResult == 0){//两个数相等
		BigInteger c("0");
		return c;
	}
	if (compareResult == 1 || compareResult == -1){//本数绝对值大于b数或小于b数的结果
		short int jiewei = 0;	//减法需要借位
		short int tempValue[MAX_LENGTH] = { 0 };	//存放相减结果的数组
		for (int i = 0; i < (compareResult == 1 ? this->count : b.count); i++){
			int result = (compareResult == 1) ? this->value[i] - jiewei - b.value[i] : b.value[i] - jiewei - this->value[i];
			jiewei = 0;
			if (result < 0){
				result += 10;
				jiewei = 1;
			}
			tempValue[i] = result;
		}
		//接下来判断结果的位数
		int tempCount = 1;
		for (tempCount = 128; tempCount > 1; tempCount--){
			if (tempValue[tempCount - 1] != 0)
				break;
		}
		//因为结果的符号肯定为刚才两个数中绝对值比较大的符号
		BigInteger c((compareResult == 1 ? this->sign : !b.sign), tempValue, tempCount);
		return c;
	}
	//如果未发生上述情况,则返回一个0
	BigInteger c("0");
	return c;
}

//乘法转换为字符串方便做
//乘法运算,这里采用手算法
BigInteger BigInteger::mult(BigInteger b){
		//如果有一个为0
	if (this->isZero() || b.isZero()){
		BigInteger c("0");
		return c;
	}
	//如果同号,结果符号位为正
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
	short int resultValue[MAX_LENGTH] = { 0 };        //存放结果的位,初始化为0  
	//now表示被乘数(存放在b中)的第now+1位  
	//temp表示当前正在计算的位  
	int now = 0, temp = 0;

	while (pb[now])
	{//未到达pb末尾时  
		temp = now;
		int bit = pb[now] - 48;     //0的asicc码为48  
		int left = 0, sum = 0;      //left表示进位,sum表示当前位数计算的总和  
		int aCount = 0;         //aCount存放当前计算到乘数的第几位  

		while (pa[aCount] || left)
		{ //乘数所有位数计算完毕 且 没有进位时 终止  
			if (!pa[aCount])
			{//乘数所有位数计算完毕,进位值放入结果的最高位  
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
	//计算结果位数
	int resultCount;
	for (resultCount = MAX_LENGTH-1; resultCount > 1; resultCount--){
		if (resultValue[resultCount-1] != 0)
			break;
	}
	BigInteger c(resultSign, resultValue, resultCount);
	return c;
}
//取出大整数的前几位数,这里没考虑要取得位数大于大整数位数的情况
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

////数值位自增,如果是1那么自增后就是2,如果是-1自增后就是-2
//void BigInteger::Zizeng(){
//	if (this->count == 0)
//		count = 1;
//		short int jinwei = 0;
//		short int tempValue[MAX_LENGTH] = { 1 };	//定义一个1
//		for (int i = 0; i < this->count; i++){
//			int result = this->value[i] + tempValue[i] + jinwei;
//			this->value[i] = result % 10;
//			jinwei = result / 10;
//		}
//		this->value[this->count] = jinwei;
//		if (jinwei != 0)
//			this->count++;
//}
////大整数相除,循环,最笨的办法
//BigInteger BigInteger::div(BigInteger b)
//{
//	//被除数为0,返回0 ,,除数为0,不符合规则,也返回0吧
//	if (this->abs().isZero() || b.abs().isZero())
//	{
//		BigInteger c("0");
//		return c;
//	}
//	//被除数小于除数,则结果整数部分为0,即返回0
//	if (this->abs().compare(b.abs()) == -1)
//	{
//		BigInteger c("0");
//		return c;
//	}
//	//如果两数绝对值相等,返回 1或-1
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
//	//剩下的情况即本数比b的绝对值大
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




//大整数相除,试商法
BigInteger BigInteger::div(BigInteger b)
{
	//被除数为0,返回0 ,,
	if (this->abs().isZero())
	{
		BigInteger c("0");
		return c;
	}
	//除数为0,不符合规则,返回-0 即非法值
	if (b.abs().isZero())
	{
		BigInteger c("-0");
		return c;
	}
	//被除数小于除数,则结果整数部分为0,即返回0
	if (this->abs().compare(b.abs()) == -1)
	{
		BigInteger c("0");
		return c;
	}
	//如果两数绝对值相等,返回 1或-1
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
	//剩下的情况即本数比b的绝对值大

	//取两个数的长度
	int aCount = this->count;
	int bCount = b.count;
	int bit = aCount - bCount + 1;//结果的位数
	char* result = new char[bit + 1];
	BigInteger divdend(true,this->value,this->count);	//被除数
	BigInteger divdor(true, b.value, b.count);	//除数
	BigInteger subtracter;	//减数
	BigInteger remainder(true, this->value, this->count);	//余数
	BigInteger temp;

	for (int i = 0; i < bit; i++)
	{
		int res = 0;
		subtracter = divdor.shiftInt(bit-i-1);	//补零以后的减数
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
	bool resultSign = (this->sign == b.sign ? true : false);	//判断结果的符号位
	int resultCount = strlen(result);	//结果的位数
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