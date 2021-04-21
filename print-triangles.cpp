#include <iostream>

using namespace std;

void printTriangle(int n);
void printOpositeTriangles(int n);
void printRuler(int n);
void printSymbol(int n, char symbol);

int main()
{
	cout << "printTriangle:" << endl << endl;
	printTriangle(4);
	cout << endl << endl;

	cout << "printOpositeTriangles:" << endl << endl;
	printOpositeTriangles(4);
	cout << endl << endl;

	cout << "printRuler:" << endl << endl;
	printRuler(4);
	cout << endl << endl;
	return 0;
}

void printTriangle(int n)
{
	if (n == 1)
	{
		cout << '*';
	}
	else {
		printTriangle(n - 1);
		cout << endl;
		printSymbol(n, '*');
	}
}

void printOpositeTriangles(int n)
{
	if (n == 1)
	{
		cout << '*' << endl << '*';
	}
	else {
		printSymbol(n, '*');
		cout << endl;
		printOpositeTriangles(n - 1);
		cout << endl;
		printSymbol(n, '*');
	}
}

void printRuler(int n)
{
	if (n == 1)
	{
		cout << '-' << endl;
	}
	else
	{
		printRuler(n - 1);
		printSymbol(n, '-');
		cout << endl;
		printRuler(n - 1);
	}
}

void printSymbol(int n, char symbol)
{
	if (n == 1)
	{
		cout << symbol;
	}
	else
	{
		cout << symbol;
		printSymbol(n - 1, symbol);
	}
}
