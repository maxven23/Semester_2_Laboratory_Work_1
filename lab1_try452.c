#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

// Структура многочлена состоящая из буферной переменной, степени и размера элемента
typedef struct Polynomial {
	void* buffer;
	int degree;
	int el_size;
} P;

/*  
Реализация комплесных чисел и операции над ними
*/
typedef struct {
	float re;
	float im;
} complex;

// Функция сложения двух комплексных чисел
complex add_c(complex a, complex b) {
	complex res;
	res.re = a.re + b.re;
	res.im = a.im + b.im;
	return res;
}

// Функция перемножения двух комплексных чисел
complex mult_c(complex a, complex b) {
	complex res;
	res.re = (a.re * b.re) - (a.im * b.im);
	res.im = (a.re * b.im) + (a.im * b.re);
	return res;
}

// Вывод комплексного числа на экран
void print_c(complex a) {
	if (a.im >= 0) 
		printf("(%f + %f*I)", a.re, a.im);
	else if (a.im < 0) {
		a.im = abs(a.im);
		printf("(%f - %f*I)", a.re, a.im);
	}
}

// Возведение комплесного числа в степень
complex power_complex(complex a, int pow) {
	complex res;
	res = a;
	for (int i = 1; i < pow; i++) {
		res = mult_c(a, res);
	}
	return res;
}

// Установка новых коэфициентов
void setCoef(P* polynom, int index, void* coef) {
	if (!polynom->buffer) {
		system("cls");
		printf("An error occurred\nClosing . . .");
		exit(0);
	}
	void* a = (float*)polynom->buffer + index;
	memcpy(a, coef, polynom->el_size);
};		

// Установка комплексных коэфициентов
void setCoef_complex(P* polynom, int index, void* coef1, void* coef2) {
	if (!polynom->buffer) {
		system("cls"); 
		printf("An error occurred\nClosing . . .");
		exit(0);
	}
	void* a = (float*)polynom->buffer + index;
	memcpy(a, coef1, polynom->el_size);
	a = (float*)polynom->buffer + index + 1;
	memcpy(a, coef2, polynom->el_size);
};

// Создание многочлена степени degree и элементом, размером el_size. Начальные коэф-ты - def_coef
P* create_Polynomial(int degree, int el_size, void* def_coef) {
	P* polynom = (P*)malloc(sizeof(P));
	if (!polynom) {
		system("cls");
		printf("Out of memmory\n");
		printf("Closing . . . ");
		exit(0);
	}
	polynom->el_size = el_size;
	polynom->degree = degree + 1;
	polynom->buffer = malloc(el_size * polynom->degree);
	if (!polynom->buffer) {
		system("cls");
		printf("Out of memmory\n");
		printf("Closing . . . ");
		exit(0);
	}
	for (int i = 0; i < polynom->degree; i++) {
		setCoef(polynom, i, def_coef);
	}
	return polynom;
};

// Умножение многочлена на число
void multiply_P(P* polynom, int index, float multiply) {
	system("cls");
	*((float*)polynom->buffer + index) *= multiply;
}

// Умножение комплексного многочлена на число
void multiply_P_complex(P* polynom, int index, float multiply) {
	system("cls");
	*((float*)polynom->buffer + index) *= multiply;
}

// Вывод многочлена на экран
void print_P(P* polynom) {
	system("cls");
	system("color 0b");
	float first = *((float*)polynom->buffer);
	printf("\n%.5f", first);
	for (int i = 1; i < polynom->degree; i++) {
		float b = *((float*)polynom->buffer + i);
		if (b >= 0) {
			printf(" + %.5fx^%d", b, i);
		}
		else if (b < 0) {
			b = fabs(b);
			printf(" - %.5fx^%d", b, i);
		}
	}
}

// Вывод комплексного многочлена на экран
void print_P_complex(P* polynom) {
	system("cls");
	system("color 0b");
	complex b;
	b.re = *((float*)polynom->buffer);
	b.im = *((float*)polynom->buffer + 1);
	print_c(b);
	for (int i = 2; i < (polynom->degree); i += 2) {
		b.re = *((float*)polynom->buffer + i);
		b.im = *((float*)polynom->buffer + i + 1);
		printf(" + ");
		print_c(b);
		printf("x^%d", (i + 1) / 2);
	}
}

// Подсчёт значения многочлена в некоторой точке x
void calculate_P(P* polynom, float x) {
	system("cls");
	float out = 0;
	for (int i = 0; i < polynom->degree; i++) {
		out = out + *((float*)polynom->buffer + i) * powf(x, (float)i);
	}
	printf("\nValue of your polynomial at x = %f is equal %f\n", x, out);
}

// Подсчёт значения комплескного многочлена в точке х
void calculate_P_complex(P* polynom, complex a) {
	system("cls");
	complex h;
	complex res;
	complex out;
	out.re = 0;
	out.im = 0;
	res = a;
	h.re = *((float*)polynom->buffer);
	h.im = *((float*)polynom->buffer + 1);
	out = add_c(out, h);
	for (int i = 2; i < polynom->degree; i += 2) {
		h.re = *((float*)polynom->buffer + i);
		h.im = *((float*)polynom->buffer + i + 1);
		for (int k = 1; k < (i + 1) / 2; k++) {
			res = mult_c(res, a);
		}
		res = mult_c(res, h);
		out = add_c(out, res);
	}
	printf("\nValue of your polynomial at x = ");
	print_c(a);
	printf(" is equal ");
	print_c(out);
}

void Delete_P(P* polynom) {
	free(polynom->buffer);
	free(polynom);
}

void okMessage(char func_name[50]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightCyan));
	printf("\n%-20s", func_name);
	SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
	printf(" is OK");
}

int main() {
	struct Polynomial* polynom = NULL;
	struct Polynomial* test = NULL;
	const int REAL = 1;
	const int COMPLEX = 2;
	int degree;
	int answer;
	int type;
	float x;
	complex c_x;
	complex help;
	float test_c; 
	float test_c1;
	float cf = 1;
	float newcoef;
	float newcoef1;
	float newcoef2;
	float multiply;
	float coef;
	void* p;
	p = &cf;




	// Ввод степени многочлена
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color 0a");
	printf("Enter degree of your polynomial:\n\n");
	do {
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
		scanf("%d", &degree);
		system("cls");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
		printf("Enter degree of your polynomial:\n\n");
	} while ((degree <= 0) || (degree > 255));	while (1) {
		system("cls");
		// Выбор типа многочлена (действительные/комплексный)
		printf("Choose type of your polynomial:\n");
		system("color 0a");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
		printf("\nEnter 1 for Real");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
		printf("\nEnter 2 for Complex\n\n");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
		scanf("%d", &type);
		if (type == REAL) {
			polynom = create_Polynomial((degree), sizeof(float), p);
			break;
		}
		else if (type == COMPLEX) {
			/*
			Реализация комплексного многочлена как обычного многочлена с "двойными" коэфициентами
			Т.е.:
			Первый коэф. - действительная часть;
			Второй коэф. - мнимая часть;
			*/
			degree = 2 * degree + 1;
			polynom = create_Polynomial(degree, sizeof(float), p);
			break;
		}
		else continue;
	}
	
	while (1) {
		system("cls");
		system("color 0a");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightCyan));
		printf("_______________Menu:_______________\n\n");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
		printf("1 - Show your polynomial\n");
		printf("2 - Setting new coefficients to your polynomial\n");
		printf("3 - Multiplication your polynomial by a number\n");
		printf("4 - Calculating the value of your polynomial at some point x\n");
		printf("5 - Test\n");
		printf("6 - Change type and/or degree of your polynomial (resets coef. to default)\n");
		printf("7 - Exit\n\n");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightCyan));
		printf("___________________________________\n\n");
		SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
		scanf("%d", &answer);

		switch (answer)
		{
		case 1:
			if (type == REAL) {
				print_P(polynom);
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			else {
				print_P_complex(polynom);
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			break;

		case 2:
			if (type == REAL) {
				for (int k = 0; k <= degree; k++) {
					system("cls");
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
					printf("\nChoose new coefficient to %d-th power:  ", k);
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
					scanf("%f", &newcoef);
					setCoef(polynom, k, &newcoef);
				}
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			else {				for (int k = 0; k <= (degree - 1) / 2; k++) {
					system("cls");
					printf("\nChoose new coefficient to %d-th power:  ", k);
					scanf("%f", &newcoef1);
					printf("\n\nEnter imagine part of coefficient: ");
					scanf("%f", &newcoef2);
					setCoef_complex(polynom, 2 * k, &newcoef1, &newcoef2);
				}
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			break;

		case 3:
			system("cls");
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
			printf("\nEnter the number you want to multiply your polinomial:  ");
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));			scanf("%f", &multiply);
			for (int k = 0; k <= degree; k++) {
				multiply_P(polynom, k, multiply);
			}
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
			printf("Done. \n");
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
			printf("\nPress any button to continue . . . ");
			system("pause>>VOID");
			break;

		case 4:
			if (type == REAL) {
				system("cls");
				system("color 0a");
				printf("\nEnter the value of x:  ");
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
				scanf("%f", &x);
				calculate_P(polynom, x);
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			else if (type == COMPLEX) {
				system("cls");
				system("color 0a");
				printf("\nEnter the value of x:  \n");
				printf("Real part of x: ");
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
				scanf("%f", &c_x.re);
				printf("\n");
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
				printf("Imagine part of x: ");
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
				scanf("%f", &c_x.im);
				calculate_P_complex(polynom, c_x);
				SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
				printf("\n\nPress any button to continue . . . ");
				system("pause>>VOID");
			}
			break;
		case 5:
			test = create_Polynomial(rand() % 256, sizeof(float), p);
			okMessage("Create_Polynomial");

			print_P(test);
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");

			for (int k = 0; k <= degree; k++) {
				test_c = ((float)((rand() % 10000000) - 5000000) * 0.00001);
				setCoef(test, k, &test_c);
			}
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("setCoef");

			test_c = ((float)((rand() % 10000000) - 5000000) * 0.00001);
			for (int k = 0; k <= degree; k++) {
				multiply_P(test, k, test_c);
			}
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("setCoef");
			okMessage("Multiply_P");
			
			test_c = ((float)((rand() % 10000000) - 5000000) * 0.00001);
			calculate_P(test, test_c);
			test_c = 0;
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("setCoef");
			okMessage("Multiply_P");
			okMessage("calculate_P");

			Delete_P(test);
			okMessage("Delete_P");

			test = create_Polynomial((rand() % 256 * 2 + 1), sizeof(float), p);
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("setCoef");
			okMessage("Multiply_P");
			okMessage("calculate_P");
			okMessage("Delete_P");

			print_P_complex(test);
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("Print_P_complex");
			okMessage("setCoef");
			okMessage("Multiply_P");
			okMessage("calculate_P");
			okMessage("Delete_P");
			
			for (int k = 0; k <= (degree - 1) / 2; k++) {
				test_c = ((float)((rand() % 10000000) - 5000000) * 0.00001);
				test_c1 = ((float)((rand() % 10000000) - 5000000) * 0.00001);
				setCoef_complex(test, 2 * k, &test_c, &test_c1);
			}
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("Print_P_complex");
			okMessage("setCoef");
			okMessage("setCoef_complex");
			okMessage("Multiply_P");
			okMessage("calculate_P");
			okMessage("Delete_P");

			test_c = ((float)(rand() % 10000000) * 0.00001);
			for (int k = 0; k <= degree; k++) {
				multiply_P(test, k, test_c);
			}
			
			help.re = ((float)((rand() % 10000000) - 5000000) * 0.00001);
			help.im = ((float)((rand() % 10000000) - 5000000) * 0.00001);
			calculate_P_complex(test, help);
			system("cls");
			okMessage("Create_Polynomial");
			okMessage("Print_P");
			okMessage("Print_P_complex");
			okMessage("setCoef");
			okMessage("setCoef_complex");
			okMessage("Multiply_P");
			okMessage("calculate_P");
			okMessage("calculate_P_complex");
			okMessage("Delete_P");
			Delete_P(test);
			printf("\n");
			
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
			printf("\nPress any button to continue . . . ");
			system("pause>>VOID");
			break;
		case 6:
			Delete_P(polynom);
			system("cls");
			system("color 0a");
			printf("Choose type of new polynomial:\n");
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
			printf("\nEnter 1 for Real");
			printf("\nEnter 2 for Complex\n\n");
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
			
			scanf("%d", &type);
			switch (type) {
			case 1:
				system("cls");
				system("color 0a");
				printf("Enter degree of new polynomial:\n\n");
				do {
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
					scanf("%d", &degree);
					system("cls");
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
					printf("Enter degree of new polynomial:\n\n");
				} while ((degree <= 0) || (degree > 255));
				polynom = create_Polynomial((degree), sizeof(float), p);
				break;

			case 2:
				system("cls");
				system("color 0a");
				printf("Enter degree of new polynomial:\n\n");
				do {
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Cyan));
					scanf("%d", &degree);
				} while ((degree == 0) || (degree > 255));
				degree = 2 * degree + 1;
				polynom = create_Polynomial(degree, sizeof(float), p);
				break;

			default:
				continue;
			}
			break;
		case 7:
			Delete_P(polynom);
			system("cls");
			system("color 0c");
			printf("\nClosing . . . \n");
			exit(0);
		default:
			break;
		}
	}
	return 0;
}