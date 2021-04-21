#include <iostream>
#include <vector>
using namespace std;

void main1();
void resizeArray(int*& arr, int& currentSize, int newSize);
void displayIndexes(int arr[], int arrSize, int numberToFind);

void main2();
void displayIndexes(vector<int> arr, int numberToFind);

int main()
{
	main1();
	main2();

	return 0;
}

void main1()
{
	int count = 0;
	int size = 10;
	int * arrOfIntegers = new int[size];
	int integer = 0;
	int numberToFind;

	cout << "Version A" << endl << endl;
	cout << "Please enter a sequence of positive integers, each in a separate line." << endl;
	cout << "End you input by typing -1." << endl;

	while (true)
	{
		cin >> integer;

		if (integer == -1)
		{
			break;
		}

		if (count >= size)
		{
			resizeArray(arrOfIntegers, size, size + 10);
		}

		arrOfIntegers[count] = integer;
		count++;
	}

	cout << endl << "Please enter a number you want to search." << endl;
	cin >> numberToFind;
	cout << endl << numberToFind << " shows in lines ";

	displayIndexes(arrOfIntegers, size, numberToFind);

	delete[] arrOfIntegers;
	arrOfIntegers = nullptr;

	cout << endl << endl;
}

void resizeArray(int*& arr, int& currentSize, int newSize)
{
	int *temp = new int[newSize];
	for (int i = 0; i < currentSize; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	currentSize = newSize;
}

void displayIndexes(int arr[], int arrSize, int numberToFind)
{
	int count = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (arr[i] == numberToFind)
		{
			if (count > 0)
			{
				cout << ", " << i + 1;
			}
			else
			{
				cout << i + 1;
			}
			count++;
		}
	}
	cout << '.';
}

void main2()
{
	int integer = 0;
	int numberToFind;
	vector<int> arrOfIntegers;

	cout << "Version B" << endl << endl;
	cout << "Please enter a sequence of positive integers, each in a separate line." << endl;
	cout << "End you input by typing -1." << endl;

	while (true)
	{
		if (integer == -1)
		{
			break;
		}

		cin >> integer;
		arrOfIntegers.push_back(integer);
	}

	cout << endl << "Please enter a number you want to search." << endl;
	cin >> numberToFind;
	cout << endl << numberToFind << " shows in lines ";

	displayIndexes(arrOfIntegers, numberToFind);

	cout << endl << endl;
}

void displayIndexes(vector<int> arr, int numberToFind)
{
	int count = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i] == numberToFind)
		{
			if (count > 0)
			{
				cout << ", " << i + 1;
			}
			else
			{
				cout << i + 1;
			}
			count++;
		}
	}
	cout << '.';
}
