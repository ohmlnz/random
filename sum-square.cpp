#include <iostream>
#include <cmath>

using namespace std;

int sumOfSquares(int arr[], int arrSize);
bool isSorted(int arr[], int arrSize);

int main()
{
	int arr[4] = { 2, -1, 3, 10 };
	int sortedArr[6] = { 1, 2, 3, 4, 5, 6 };
	int unsortedArr[6] = { 2, 3, 1, 5, 7, 4 };

	cout << "sumOfSquares function:" << endl;
	cout << sumOfSquares(arr, 4) << endl << endl;

	cout << "isSorted function:" << endl;
	cout << "sortedArr " << isSorted(sortedArr, 6) << endl;
	cout << "unsortedArr " << isSorted(unsortedArr, 6) << endl;
	return 0;
}

int sumOfSquares(int arr[], int arrSize)
{
	if (arrSize == 1)
	{
		return pow(arr[0], 2);
	}
	else
	{
		return pow(arr[arrSize - 1], 2) + sumOfSquares(arr, arrSize - 1);
	}
}

bool isSorted(int arr[], int arrSize)
{
	if (arrSize == 1)
	{
		return true;
	}
	else
	{
		if (arr[arrSize - 2] < arr[arrSize - 1])
		{
			isSorted(arr, arrSize - 1);
		}
		else
		{
			return false;
		}
	}
}
