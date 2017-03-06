#include <iostream>
#define _USE_MATH_DEFINES
#include "ATLComTime.h"
#include <cmath>
using namespace std;

double true_I = 1.7183;
//составим функцию, реализующую 
//подинтегральное выражение e^(cos(x))*sin(x)
double func(double x) {
	double f = exp(cos(x))*sin(x);
	return f;

}
//функция, реализующая приближенное вычисление
//по методу Гаусса, на вход подаются границы интегрирования
double IntegrationGauss(double a, double b) {


	//точное значение используем для сравнения
	
	cout << "границы интеграрования: " << "[" << a << ", " << b << "]" << endl;
	//находим интеграл по формуле Гаусса
	double I =
		(b - a) / 2 *
		(func((a + b) / 2 - (b - a) / (2 * sqrt(3))) +
			func((a + b) / 2 + (b - a) / (2 * sqrt(3))));
	return I;
}

int main() {
	setlocale(LC_ALL, "ru");
	cout.precision(30);
	cout.setf(ios::fixed);

	double part = (M_PI / 2) / 8;
	double ParallelIntegral = 0;
#pragma omp parallel for reduction(+:ParallelIntegral)
	for (int i = 1; i <= 8; i++) {
		ParallelIntegral += IntegrationGauss(part*(i - 1), part*i);
	}

	cout << "найден ответ = " << ParallelIntegral << endl;
	cout << "с погрешностью = " << fabs((true_I - ParallelIntegral) * 100 / true_I) << endl;

	double normalIntegration = IntegrationGauss(0, M_PI / 2);


	cout << "найден ответ = " << normalIntegration << endl;
	cout << "с погрешностью = " << fabs((true_I - normalIntegration) * 100 / true_I) << endl;
	system("pause");
}
