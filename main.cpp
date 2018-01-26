#include <fir_order_1.hpp>
#include <fir_order_n.hpp>
#include <iostream>

using namespace std;

typedef Fir_order_1<> filter_type1;
typedef Fir_order_n<> filter_typeN;

filter_type1 F1(4U);
filter_typeN Fn(4U);

void do_something()
{
	F1.NewSample<7, 1>(100U);
	Fn.NewSample<5, 5, 6, 6, 5, 5>(100U);
}

int main()
{
	do_something();
	cout << "first order output: " << F1.GetResult() << endl;
	cout << "fifth order output: " << Fn.GetResult() << endl;	
	return 0;
}
