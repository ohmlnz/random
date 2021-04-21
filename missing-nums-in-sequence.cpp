#include <iostream>

using namespace std;

int* findMissing(int arr[], int n, int& resArrSize);
void printResults(int arr[], int arrSize);

int main()
{
	int resArrSize = 0;
	int arr[6] = { 3, 1, 3, 0, 6, 4 };

	int* arrOfMissingInt = findMissing(arr, 6, resArrSize);
	printResults(arrOfMissingInt, resArrSize);

	delete[] arrOfMissingInt;
	arrOfMissingInt = nullptr;

	return 0;
}

int* findMissing(int arr[], int n, int& resArrSize)
{
	int* indexes = new int[n + 1]{ 0 };
	int nbOfMissingInt = n + 1;

	for (int i = 0; i < n; i++)
	{
		if (indexes[arr[i]] == 0)
		{
			nbOfMissingInt--;
		}
		indexes[arr[i]]++;
	}

	int* arrOfMissingInt = new int[nbOfMissingInt];
	int missingIntIndex = 0;

	for (int i = 0; i < n + 1; i++)
	{
		if (indexes[i] == 0)
		{
			arrOfMissingInt[missingIntIndex] = i;
			missingIntIndex++;
		}
	}
	resArrSize = nbOfMissingInt;
	return arrOfMissingInt;
}

void printResults(int arr[], int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}
