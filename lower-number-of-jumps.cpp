#include <iostream>

using namespace std;

int lowestNumberOfJumpsInSequence(int arr[], int arrSize, int total);

int main()
{
	int sequence[6] = { 0, 3, 80, 6, 57, 10 };
	cout << lowestNumberOfJumpsInSequence(sequence, 6, 0);
	return 0;
}

int lowestNumberOfJumpsInSequence(int arr[], int arrSize, int total)
{
	total += *arr;
	if (arrSize == 1)
	{
		return total;
	}
	else if (arrSize == 2)
	{
		return lowestNumberOfJumpsInSequence(arr + 1, arrSize - 1, total);
	}
	else
	{
		int path1 = lowestNumberOfJumpsInSequence(arr + 1, arrSize - 1, total);
		int path2 = lowestNumberOfJumpsInSequence(arr + 2, arrSize - 2, total);
		return path1 < path2 ? path1 : path2;
	}
}
