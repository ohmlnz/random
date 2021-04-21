/*
*   1. Implement a symbol balance checker function for the Pascal programming language.  Pascal allows for the following pairs: {}, (), [], begin end .  All programs will begin with the word "begin" and end  with the word "end".  Your function should receive an ifstream object which is already open and will return true, all of the symbols match, or false, they do not.  You do not have to worry about comments in the program but you do have to avoid other parts of the program's code such as assignment statements (x=y) and other expressions.  
*
*   2. Although a queue is "best" implemented with a list, it can be implemented with a vector if you take into account the starting position of the queue.  For example, if five elements are pushed onto the queue, the start of the queue is at position zero and the end is at position 4.  If we, then, pop two elements, the start would be at position 2 and the end at position 4.  The two "popped" elements are not really removed from the vector, and that avoids the O(N) time problem for the pop function.
*   Implement a class which uses a vector to store the queue.  Be mindful of performance, such that if the queue is empty, the size of the underlying vector is "reset."
*/

#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <class T>
class Stack
{
public:
	void push(T newElement);
	void pop();
	T top() const;
	bool isEmpty() const;
	int size() const;
	void clear();
private:
	list<T> stack;
};

template <class T>
void Stack<T>::push(T newElement)
{
	stack.push_front(newElement);
}

template <class T>
void Stack<T>::pop()
{
	stack.pop_front();
}

template <class T>
T Stack<T>::top() const
{
	if (!stack.size() == 0)
	{
		return *stack.begin();
	}
}

template <class T>
bool Stack<T>::isEmpty() const
{
	return stack.size() == 0;
}

template <class T>
int Stack<T>::size() const
{
	return stack.size();
}

template <class T>
void Stack<T>::clear()
{
	stack.clear();
}

template <class T>
class Queue
{
public:
	void push(T newElement);
	void pop();
	T top() const;
	bool isEmpty() const;
	int size() const;
	void clear();
	void read();
private:
	vector<T> queue;
	int startIndex = 0;
};

template <class T>
void Queue<T>::push(T newElement)
{
	queue.push_back(newElement);
}

template <class T>
void Queue<T>::pop()
{
	if (startIndex + 1 < queue.size())
	{
		startIndex++;
	}
	else
	{
		// reset queue when last element is popped
		queue.clear();
		startIndex = 0;
	}
}

template <class T>
T Queue<T>::top() const
{
	return queue[startIndex];
}

template <class T>
bool Queue<T>::isEmpty() const
{
	return queue.size() == 0;
}

template <class T>
int Queue<T>::size() const
{
	return queue.size() - startIndex;
}

template <class T>
void Queue<T>::clear()
{
	queue.clear();
}

template <class T>
void Queue<T>::read()
{
	for (int i = startIndex; i < queue.size(); i++)
	{
		cout << queue[i] << endl;
	}
}

void openInputFile(ifstream& inputFile);
bool areSymbolsBalanced(ifstream& inputFile);

int main()
{
	ifstream inputFile;
	openInputFile(inputFile);

	if (areSymbolsBalanced(inputFile))
	{
		cout << "The program in the input file is valid." << endl;
	}
	else
	{
		cout << "The program in the input file is invalid" << endl;
	}

	Queue<int> myqueue;
	myqueue.push(1);
	myqueue.push(5);
	myqueue.push(93);
	myqueue.pop();
	cout << myqueue.top() << endl;
	myqueue.push(3939);
	cout << myqueue.size() << endl;
	return 0;
}

void openInputFile(ifstream& inputFile)
{
	inputFile.open("pascal.txt");

	if (!inputFile)
	{
		cout << "The file named pascal.txt does not exist in the current directory." << endl;
		cout << "Exiting the program..." << endl;
		exit(1);
	}
}

bool areSymbolsBalanced(ifstream& inputFile)
{
	Stack<char> parenthesis;
	Stack<string> statements;

	string keyword;
	char symbol;
	bool ignore = false;
	
	while (inputFile >> symbol)
	{
		// ignore any symbol that's within a string assignment
		if (symbol == '\'' && ignore == false) {
			ignore = true;
		} 
		else if (symbol == '\'' && ignore == true)
		{
			ignore = false;
		}

		if (ignore == false)
		{
			if ((symbol == '(' || symbol == '[' || symbol == '{'))
			{
				parenthesis.push(symbol);
			}
			else if (symbol == ')' || symbol == ']' || symbol == '}')
			{
				if (!parenthesis.isEmpty())
				{
					if (
						symbol == ')' && parenthesis.top() == '(' ||
						symbol == ']' && parenthesis.top() == '[' ||
						symbol == '}' && parenthesis.top() == '{'
						)
					{
						parenthesis.pop();
					}
				}
				else
				{
					return false;
				}
			}
		}
	}

	// reset file to the beginning
	inputFile.clear();
	inputFile.seekg(0, ios_base::beg);

	while (inputFile >> keyword)
	{
		if (keyword == "begin")
		{
			statements.push(keyword);
		}
		else if (keyword == "end")
		{
			if (!statements.isEmpty())
			{
				if (keyword == "end" && statements.top() == "begin")
				{
					statements.pop();
				}
			}
			else
			{
				return false;
			}
		}
	}
	return parenthesis.isEmpty() && statements.isEmpty();
}
