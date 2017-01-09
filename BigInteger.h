
#define MAX_LENGTH 128
class BigInteger{
private:
	//��Ŵ�����������
	short int value[MAX_LENGTH];
	//����λ,trueΪ����
	bool sign;
	//���ֵ�λ��
	short int count;
public:
	BigInteger();		//Ĭ�Ϲ��캯��
	BigInteger(char * bigInteger);		//�������Ĺ��캯��.��������д+,����д-,��"-123456"
	BigInteger(bool _sign, short int _value[],short int _count);
	short int getCount(){ return this->count; }	//��ȡλ��
	bool getSign(){ return this->sign; }	//��ȡ����λ
	short int* getValue(){ return this->value; }	//��ȡ��ֵ
	void print();		//����Ļ������Լ�
	BigInteger abs();		//�����Լ��ľ���ֵ
	bool isZero();			//�ж��Ƿ�Ϊ0
	BigInteger getOpposite(){ return BigInteger(!this->sign, this->value, this->count); }	//ȡ�෴��
	void Zizeng();	//��ֵλ����,�����1��ô���������2,�����-1���������-2
	short int compare(BigInteger b);		//�Ƚ��������Ĵ�С,��ǰ��>b����Ϊ1,��Ƚ��Ϊ0 ����Ϊ-1
	BigInteger add(BigInteger b);	//�ӷ�,�Լ�+b ,���Ϊ����ֵ
	BigInteger sub(BigInteger b);	//����,�Լ�-b ,���Ϊ����ֵ
	BigInteger mult(BigInteger b);	//�˷�.�Լ�*b ,���Ϊ����ֵ
	BigInteger div(BigInteger b);	//����,�Լ�/b ,���Ϊ����ֵ
	BigInteger shiftInt(short int length);	//���������length��0, ���̷��õ�
};