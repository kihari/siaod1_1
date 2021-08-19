#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono> 

using namespace std;

//прототипы функций
int BetterLinearSearch(int arr[], int requiredKey, int size); // линейный поиск
int SentLinearSearch(int arr[], int requiredKey, int arrSize);// быстрый поиск
int BinarySearch(int arr[], int requiredKey, int arrSize);// бинарный
void showArr(int arr[], int size); // печать массива
void Proverka(int n);

class Timer
{
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

int main()
{
	system("color F0");
	setlocale(LC_ALL, "rus");
	const int arrSize = 10;
	int arr[arrSize];
	int requiredKey = 0; //искомое значение (ключ)
	int nElement = 0; //номер элемента массива

	srand(time(NULL));

	//запись случайных чисел в массив
	for (int i = 0; i < arrSize; i++)
	{
		arr[i] = 1 + rand() % 30;
	}
	showArr(arr, arrSize);// печать массива

	cout << "Какое число необходимо искать? ";
	cin >> requiredKey;// ввод искомого числа

	//Последовательный поиск
	cout << "\nЛинейный поиск:" << endl;
	Timer t;
	nElement = BetterLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << t.elapsed() << '\n';
	Proverka(nElement);
	
	//Быстрый поиск
	cout << "\nБыстрый поиск:" << endl;
	Timer c;
	SentLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << c.elapsed() << '\n';
	Proverka(nElement);

	

	//Сортировка прямого выбора
	for (int i = 0; i < arrSize - 1; i++)
	{
		int temp;
		int small = i;
		for (int j = i + 1; j < arrSize; j++)
			if (arr[j] < arr[small]) small = j;
		temp = arr[i];
		arr[i] = arr[small];
		arr[small] = temp;
	}
	showArr(arr, arrSize);//Печать отсортированного массива

	//Быстрый поиск по отсортированному массиву
	cout << "\nБыстрый поиск по отсортированному массиву:" << endl;
	Timer m;
	nElement = SentLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << m.elapsed() << '\n';
	Proverka(nElement);
	cout << endl;
	showArr(arr, arrSize);
	cout << endl;
	//Бинарный поиск
	cout << "\nБинарный поиск:" << endl;
	Timer e;
	nElement = BinarySearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << e.elapsed() << '\n';
	Proverka(nElement);
	
	return 0;
}
//Печать индекса искомого значения
void Proverka(int n)
{
	if (n != -1) cout << "Значение находится в ячейке с индексом: " << n << endl;
	else cout << "В массиве нет такого значения" << endl;
}
//Печать массива
void showArr(int arr[], int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << setw(4) << arr[i];
		if ((i + 1) % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << endl << endl;
}

//Последовательный поиск
int BetterLinearSearch(int arr[], int requiredKey, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == requiredKey)
		{
			return i;
		}
	}
	return -1;
}

//Быстрый последовательный поиск
int SentLinearSearch(int arr[], int requiredKey, int arrSize)
{
	int last = arr[arrSize];
	arr[arrSize] = requiredKey;
	int i = 0;
	while (arr[i] != requiredKey) i++;
	arr[arrSize] = last; 
	if (i < arrSize || arr[arrSize] == requiredKey) return i;
	else return -1;
}

//Бинарный поиск
int BinarySearch(int arr[], int requiredKey, int arrSize)
{
	int p = 0;
	int r = arrSize;
	while (p <= r)
	{
		int q = (p + r) / 2;
		if (arr[q] == requiredKey) return q;
		else if (arr[q] != requiredKey && arr[q] > requiredKey) r = q - 1;
		else if (arr[q] < requiredKey) p = q + 1;
	}
	return -1;
}