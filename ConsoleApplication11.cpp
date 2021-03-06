#include "pch.h"
#include <iostream>
#include<iomanip>
#include <cmath>
using namespace std;
double integral_mid(double(*func)(double), double a, double b, double n)
{
	double h, S, x;
	h = (a - b) / n;
	S = 0;
	for (int i = 0; i < n - 1; i++)
	{
		x = a + i * h;
		S = S + func(x);
	}
	S = h * S;
	cout << S << endl;
	return S;
}

double sim(double(*func)(double), double a, double b, double eps)
{
	double value_last = eps + 1, value_first = 0; //предыдущее вычисленное значение интеграл  и новое с большим N.
	int steps; int n = 4;
	do
	{
		double h, summa2 = 0, summa4 = 0, summa = 0;
		h = (b - a) / (2.0 * (double)n);//Шаг интегрирования.
		for (int i = 1; i <= 2 * n - 1; i += 2)
		{
			summa4 += func(a + h * i);//Значения с нечётными индексами, которые нужно умножить на 4.
			summa2 += func(a + h * (i + 1));//Значения с чётными индексами, которые нужно умножить на 2.
		}
		summa = func(a) + 4 * summa4 + 2 * summa2 - func(b);//Отнимаем значение f(b) так как ранее прибавили его дважды.
		value_last = value_first;
		value_first = (h / 3)*summa;
		steps = n;
		n *= 2;

	} while (fabs(value_first - value_last) > eps);
	cout << "Значение интегралла равно : " << value_first << " . Оно было вычисленно при n = " << steps << endl;
	return 0;
}
double first_func(double x)
{
	return (x*x*x*exp(2 * x));
}
double second_func(double x)
{
	return 1 / (1 + sqrt(x));
}
double third_func(double x)
{
	return 1 / ((x + 1)*(sqrt(x*x + 1)));
}
int main()
{
	double ebs;
	setlocale(LC_ALL, ".1251");
	cout << "Введите значение e (где 0<e<10^(-k)) : " << endl;
	cin >> ebs;
	if ((ebs >= 1) || (ebs <= 0))
	{
		cout << "Значение е не соответсвует ограничениям. Попробуйте снова.";
		return 0;
	}
	double y_mid1 = integral_mid(first_func, 0.8, 0.0, ebs),
	y_mid2 = integral_mid(second_func, 1.8, 0.0, ebs),
	y_mid3 = integral_mid(third_func, 0.3, 0.0, ebs);
	double y_sim1 = sim(first_func, 0.8, 0.0, ebs), y_sim2 = sim(second_func, 1.8, 0.0, ebs), y_sim3 = sim(third_func, 0.3, 0.0, ebs);
	cout << "Значение интеграла по методу средних прямоугольников: \nПервый интеграл:" << y_mid1 <<endl<<"Второй интеграл:" << y_mid2<<endl<<"Третий интеграл:"<<y_mid3<< endl;
	//cout << "Значение интеграла по методу Симпсона: \nПервый интеграл:" << y_sim1 << endl << "Второй интеграл:" << y_sim2 << endl << "Третий интеграл:" << y_sim3 << endl;
	system("pause");
	return 0;
}
