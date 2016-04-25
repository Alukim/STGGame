#include <iostream>

class base
{
	int lel;
public:
	base(int a) : lel(a)
	{
	}
	virtual void print() = 0;
	virtual ~base()
	{
	}
};

class der : public base
{
	float lol;
public:
	der(int a, float b) : base(a), lol(b)
	{
	}
	void print() override
	{
		std::cout << "getPrice" << std::endl;
	}
	virtual ~der()
	{
	}
};
class der2 : public base
{
	char x;
public:
	der2(int a, char s) : base(a), x(s)
	{
	}

	void print() override
	{
		std::cout << "fuck" << std::endl;
	}

	virtual ~der2()
	{
	}

};
int main(int argc, char **argv)
{
	//int *ptr = new int(32);
	base * ptr = new der(32, 24);
	der2 *test = 0;
	if (test = dynamic_cast<der2*>(ptr))
	{
		std::cout << "keke" << std::endl;
	}
	system("pause");
}