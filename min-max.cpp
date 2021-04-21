/*
*	(Weiss 7.40): The following divide-and-conquer algorithm is proposed for finding the simultaneous
*	maximum and minimum: If there is one item, it is the maximum and
*	minimum, and if there are two items, then compare them, and in one comparison
*	you can find the maximum and minimum. Otherwise, split the input into two
*	halves, divided as evenly as possibly (if N is odd, one of the two halves will have
*	one more element than the other). Recursively find the maximum and minimum
*	of each half, and then in two additional comparisons produce the maximum and
*	minimum for the entire problem.
*
*	Write the above function which will take in a vector and solve the problem, producing a vector of two elements, the min and max.
*/

#include <iostream>
#include <vector>

using namespace std;

template <class T>
vector<T> findMinMax(const vector<T>& vec, int start, int end, vector<T>& temp)
{
	int mid = (start + end) / 2;
	if (start == end) // one element
	{
		temp = { vec[start], vec[end] };
		return temp;
	}
	else if (start + 1 == end) // two elements
	{
		if (vec[start] < vec[end])
		{
			temp = { vec[start], vec[end] };
		}
		else
		{
			temp = { vec[end], vec[start] };
		}
		return temp;
	}
	vector<T> v1 = findMinMax(vec, start, mid, temp); // left side
	vector<T> v2 = findMinMax(vec, mid + 1, end, temp); // right side

	temp[0] = v1[0] < v2[0] ? v1[0] : v2[0];
	temp[1] = v1[1] > v2[1] ? v1[1] : v2[1];

	return temp;
}

template <class T>
vector<T> findMinMax(const vector<T>& vec)
{
	vector<T> temp(2);
	return findMinMax(vec, 0, vec.size() - 1, temp);
}

template <class T>
void printMinMax(const vector<T>& vec)
{
	cout << "min: " << vec[0] << endl;
	cout << "max: " << vec[1] << endl;
}

int main()
{
	vector<int> odd = { 18, 3, 5, 33, 9, 42, 111 };
	vector<int> even = { 7, 9, 3, 2, 1, 0, 4, 8 };
	vector<int> res(2);
	res = findMinMax(odd);
	printMinMax(res);
	return 0;
}
