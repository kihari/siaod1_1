#include <iomanip>
#include <ctime>
#include <iostream>
#include <chrono> 

using namespace std;

//��������� �������
int BetterLinearSearch(int arr[], int requiredKey, int size); // �������� �����
int SentLinearSearch(int arr[], int requiredKey, int arrSize);// ������� �����
int BinarySearch(int arr[], int requiredKey, int arrSize);// ��������
void showArr(int arr[], int size); // ������ �������
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
	int requiredKey = 0; //������� �������� (����)
	int nElement = 0; //����� �������� �������

	srand(time(NULL));

	//������ ��������� ����� � ������
	for (int i = 0; i < arrSize; i++)
	{
		arr[i] = 1 + rand() % 30;
	}
	showArr(arr, arrSize);// ������ �������

	cout << "����� ����� ���������� ������? ";
	cin >> requiredKey;// ���� �������� �����

	//���������������� �����
	cout << "\n�������� �����:" << endl;
	Timer t;
	nElement = BetterLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << t.elapsed() << '\n';
	Proverka(nElement);
	
	//������� �����
	cout << "\n������� �����:" << endl;
	Timer c;
	SentLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << c.elapsed() << '\n';
	Proverka(nElement);

	

	//���������� ������� ������
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
	showArr(arr, arrSize);//������ ���������������� �������

	//������� ����� �� ���������������� �������
	cout << "\n������� ����� �� ���������������� �������:" << endl;
	Timer m;
	nElement = SentLinearSearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << m.elapsed() << '\n';
	Proverka(nElement);
	cout << endl;
	showArr(arr, arrSize);
	cout << endl;
	//�������� �����
	cout << "\n�������� �����:" << endl;
	Timer e;
	nElement = BinarySearch(arr, requiredKey, arrSize);
	cout << "Time taken: " << e.elapsed() << '\n';
	Proverka(nElement);
	
	return 0;
}
//������ ������� �������� ��������
void Proverka(int n)
{
	if (n != -1) cout << "�������� ��������� � ������ � ��������: " << n << endl;
	else cout << "� ������� ��� ������ ��������" << endl;
}
//������ �������
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

//���������������� �����
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

//������� ���������������� �����
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

//�������� �����
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