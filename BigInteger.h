
#define MAX_LENGTH 128
class BigInteger{
private:
	//存放大整数的数组
	short int value[MAX_LENGTH];
	//符号位,true为正数
	bool sign;
	//数字的位数
	short int count;
public:
	BigInteger();		//默认构造函数
	BigInteger(char * bigInteger);		//带参数的构造函数.正数不用写+,负数写-,如"-123456"
	BigInteger(bool _sign, short int _value[],short int _count);
	short int getCount(){ return this->count; }	//获取位数
	bool getSign(){ return this->sign; }	//获取符号位
	short int* getValue(){ return this->value; }	//获取数值
	void print();		//在屏幕上输出自己
	BigInteger abs();		//返回自己的绝对值
	bool isZero();			//判断是否为0
	BigInteger getOpposite(){ return BigInteger(!this->sign, this->value, this->count); }	//取相反数
	void Zizeng();	//数值位自增,如果是1那么自增后就是2,如果是-1自增后就是-2
	short int compare(BigInteger b);		//比较两个数的大小,当前数>b则结果为1,相等结果为0 否则为-1
	BigInteger add(BigInteger b);	//加法,自己+b ,结果为返回值
	BigInteger sub(BigInteger b);	//减法,自己-b ,结果为返回值
	BigInteger mult(BigInteger b);	//乘法.自己*b ,结果为返回值
	BigInteger div(BigInteger b);	//除法,自己/b ,结果为返回值
	BigInteger shiftInt(short int length);	//往后面添加length个0, 试商法用到
};