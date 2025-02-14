﻿#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>

void swap(double* a, double* b)
{
	double t = *a;
	*a = *b;
	*b = t;
}

int compare(const void* a, const void* b)
{
	double a1, a2;
	a1 = *(const double*)a;
	a2 = *(const double*)b;

	if (a1 < a2)
		return -1;
	if (a1 > a2)
		return 1;
	return 0;
}
int check(double* mas1, double* mas, int na)
{
	int i;
	double* arr;
	arr = (double*)malloc(sizeof(double) * na);
	arr = mas;
	qsort(arr, na, sizeof(double), compare);
	for (i = 0; i < na - 1; i++)
		if (mas1[i] != arr[i])
			return 0;
	return 1;
	free(arr);
}
void check_res(double* mas, double* mas1, int na)
{
	if (check(mas, mas1, na))
		printf("\nмассив отсортирован верно\n");
	else printf("\nОшибка сортировки");

}

//сортировка пузырьком
void bubble(double* mas, int na) {
	clock_t start, end;
	double ti = 0;
	int flag = 0;
	start = clock();
	for (int i = 0; i < na - 1; i++)
	{
		flag = 0;
		for (int j = 0; j < na - 1 - i; j++)
			if (mas[j] > mas[j + 1]) {
				swap(&mas[j], &mas[j + 1]);
				flag = 1;
			}
		if (flag == 0) break;
	}
	end = clock();
	ti = (end - start) / (double)(CLOCKS_PER_SEC);
	/*printf("Отсортированный массив: ");
	for (int i = 0; i < na; i++)
		printf("%lf ", mas[i]);*/
	printf("\nзатраченное время: %lf", ti);
}

//сортировка вставками
//определение местоположения элемента
int place(double* mas, double r, int k)
{
	int s = k;
	for (int i = 0; i < k; i++)
		if (mas[i] > r)
		{
			s = i;
			break;
		}
	return s;
}

//сдвиг для места элемента
void shift(double* mas, int s, int k)
{
	for (int i = k; i > s; i--)
		mas[i] = mas[i - 1];
}

void insert(double* mas, int na)
{
	int k, s;
	double r;
	clock_t start, end;
	double ti = 0;
	start = clock();
	for (k = 1; k < na; k++)
	{
		r = mas[k];
		s = place(mas, r, k);
		shift(mas, s, k);
		mas[s] = r;
	}
	end = clock();
	ti = (end - start) / (double)(CLOCKS_PER_SEC);
	/*printf("Отсортированный массив: ");
	for (int i = 0; i < na; i++)
		printf("%lf ", mas[i]);*/
	printf("\nзатраченное время: %lf", ti);
}

//соритровка Шелла
void shell(double* mas, int na)
{
	clock_t start, end;
	double t;
	double ti = 0;
	start = clock();
	for (int i = na / 2; i > 0; i /= 2)//шаг между элементами
		for (int j = i; j < na; j++)
			for (int k = j - i; k >= 0 && mas[k] > mas[k + i]; k -= i)
				swap(&mas[k], &mas[k + i]);
	end = clock();
	ti = (end - start) / (double)(CLOCKS_PER_SEC);
	/*printf("Отсортированный массив: ");
	for (int i = 0; i < na; i++)
		printf("%lf ", mas[i]);*/
	printf("\nзатраченное время: %lf", ti);
}

//сортировка слиянием
//обмен местами
void merge(double* mas, int first, int last)
{
	int l, r, m;
	double* a;
	a = (double*)malloc((last - first) * sizeof(double));
	m = (first + last) / 2;
	l = first;
	r = m + 1;
	for (int i = first; i <= last; i++)
	{
		if ((l <= m) && ((r > last) || (mas[l] < mas[r])))
		{
			a[i - first] = mas[l];
			l++;
		}
		else
		{
			a[i - first] = mas[r];
			r++;
		}
	}
	for (int j = first; j <= last; j++)
		mas[j] = a[j - first];

}

void mergesort1(double* mas, int st, int end1)
{
	if (st < end1)
	{
		mergesort1(mas, st, (st + end1) / 2);
		mergesort1(mas, (st + end1) / 2 + 1, end1);
		merge(mas, st, end1);
	}
}

void mergesort(double* mas, int na)
{
	clock_t start, end;
	double ti = 0;
	start = clock();
	mergesort1(mas, 0, na - 1);
	end = clock();
	ti = (end - start) / (double)(CLOCKS_PER_SEC);
	//printf("Отсортированный массив: ");
	//for (int i = 0; i < na; i++)
	//	printf("%lf ", mas[i]);
	printf("\nзатраченное время: %lf", ti);
}



int main()
{
	setlocale(LC_CTYPE, "RUS");
	int n = 0;//размер массива
	clock_t start, end;
	double a, b; //значения концов отрезка, в котором находятся элементы
	int k = 0; //выбор номера сортировки

	printf("введите количество элементов в массиве: ");
	scanf_s("%d", &n);

	double* mas = NULL;
	double* mas1 = NULL;
	mas = (double*)malloc(sizeof(double) * n);
	mas1 = (double*)malloc(sizeof(double) * n);
	printf("введите диапазон, в котором находятся элементы массива: ");
	scanf_s("%lf %lf", &a, &b);

	//генерирование массива с рандомными элементами
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		mas[i] = ((double)rand() / ((double)RAND_MAX)) * (b - a) + a;
	mas1 = mas;

	////вывод изачального массива
	//for (int i = 0; i < n; i++)
	//	printf("%lf ", mas1[i]);

	printf("\n1.Сортировка пузырьком");
	printf("\n2.Сортировка вставками");
	printf("\n3.Сортировка Шелла");
	printf("\n4.Сортировка слиянием");
	printf("\n5.Конец\n\n");

	while (k != 5)
	{
		printf("\nвыберите номер команды: ");
		scanf_s("%d", &k);


		switch (k)
		{
		case 1:
			bubble(mas1, n);
			check_res(mas1, mas, n);
			mas1 = mas;
			break;

		case 2:
			insert(mas1, n);
			check_res(mas1, mas, n);
			mas1 = mas;
			break;


		case 3:
			shell(mas1, n);
			check_res(mas1, mas, n);
			mas1 = mas;
			break;

		case 4:
			mergesort(mas1, n);
			check_res(mas1, mas, n);
			mas1 = mas;
			break;

		case 5: break;
		default:
			printf("Неправильный ввод данных");
			break;
		}
	}

}
