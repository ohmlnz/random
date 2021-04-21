/* 
*  Write a checkbook balancing program. The program will read in, from the console, the following for all checks that were not cashed as of the last time you balanced your checkbook: the number of each check (int), the amount of the check (double), and whether or not it has been cashed (1 or 0, boolean in the array). 
*  Use an array with the class as the type. The class should be a class for a check. There should be three member variables to record the check number, the check amount, and whether or not the check was cashed. The class for a check will have a member variable of type Money (as defined on page 662 in the book; Display 11.9) to record the check amount. So, you will have a class used within a class. The class for a check should have accessor and mutator functions as 
*  well as constructors and functions for both input and output of a check.  In addition to the checks, the program also reads all the deposits (from the console; cin), the old and the new account balance (read this in from the user at the console; cin). You may want another array to hold the deposits. The new account balance should be the old balance plus all deposits, minus all checks that have been cashed.
*  The program outputs the total of the checks cashed, the total of the deposits, what the new balance should be, and how much this figure differs from what the bank says the new balance is. It also outputs two lists of checks: the checks cashed since the last time you balanced your checkbook and the checks still not cashed.[ edit: if you can, Display both lists of checks in sorted order from lowest to highest check number.]
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Employee
{
public:
	Employee(int newIdNumber = 0, double newHourlyPay = 0.0, string newName = "") :
		idNumber(newIdNumber), hourlyPay(newHourlyPay), name(newName), wage(0.0) {}
	friend ostream& operator<< (ostream& outs, const Employee& employee);
	void incrementWage(int hours);
private:
	int idNumber;
	double hourlyPay;
	double wage;
	string name;

	template<class T> friend class LList;
};

ostream& operator<< (ostream& outs, const Employee& employee)
{
	outs << employee.name << ", " << "$" << employee.wage << endl;
	return outs;
}

void Employee::incrementWage(int hours)
{
	wage += hours * hourlyPay;
}

template <class T>
class LListNode
{
public:
	LListNode(T newdata = T(), LListNode<T>* newNext = nullptr) :
		data(newdata), next(newNext) {}
	LListNode<T>* getNextNode() const;
	void setNextNode(LListNode<T>* newNext);
	T& getData();
private:
	T data;
	LListNode<T>* next;
};

template <class T>
LListNode<T>* LListNode<T>::getNextNode() const
{
	return next;
}

template <class T>
void LListNode<T>::setNextNode(LListNode<T>* newNext)
{
	next = newNext;
}

template <class T>
T& LListNode<T>::getData()
{
	return data;
}

template <class T>
class LList {
public:
	LList() : head(nullptr) {}
	LList(const LList& rhs);
	~LList();
	LList<T>& operator=(const LList<T>& rhs);
	LListNode<T>* findNode(int idNumber) const;
	void readNodes() const;
	void insertNode(LListNode<T>* newNode);
	void sortNodesInDescendingOrder() const;
	void clearNodes();
	
private:
	LListNode<T>* head;
	LListNode<T>* recursiveCopy(LListNode<T>* rhs);
};

template <class T>
LList<T>::LList(const LList& rhs) : head(nullptr)
{
	*this = rhs;
}

template <class T>
LList<T>::~LList()
{
	clearNodes();
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs) {
	if (this == &rhs)
		return *this;
	clearNodes();
	recursiveCopy(rhs);
	return *this;
}

template <class T>
LListNode<T>* LList<T>::findNode(int idNumber) const
{
	LListNode<T>* node = head;
	while (node->getNextNode() != nullptr && (node->getData()).idNumber != idNumber)
	{
		node = node->getNextNode();
	}

	if ((node->getData()).idNumber == idNumber)
	{
		return node;
	}
	else
	{
		return nullptr;
	}
}

template <class T>
void LList<T>::readNodes() const
{
	LListNode<T>* node = head;
	while (node != nullptr)
	{
		cout << node->getData();
		node = node->getNextNode();
	}
}

template <class T>
void LList<T>::insertNode(LListNode<T>* newNode)
{
	newNode->setNextNode(head);
	head = newNode;
}

template <class T>
void LList<T>::sortNodesInDescendingOrder() const
{
	LListNode<T>* node = head;
	LListNode<T>* temp;
	Employee tempData;

	while (node != nullptr)
	{
		temp = node;
		while (temp->getNextNode() != nullptr)
		{
			if ((temp->getData()).wage < (temp->getNextNode()->getData()).wage)
			{
				tempData = temp->getData();
				temp->getData() = temp->getNextNode()->getData();
				temp->getNextNode()->getData() = tempData;
			}
			temp = temp->getNextNode();
		}
		node = node->getNextNode();
	}
}

template <class T>
void LList<T>::clearNodes()
{
	LListNode<T>* node = head->getNextNode();
	LListNode<T>* next;

	while (node != nullptr)
	{
		next = node->getNextNode();
		delete node;
		node = next;
	}

	delete head;
	head = nullptr;
}

template <class T>
LListNode<T>* LList<T>::recursiveCopy(LListNode<T>* rhs)
{
	if (rhs == nullptr)
	{
		return nullptr;
	}
	return new LListNode<T>(rhs->data, recursiveCopy(rhs->next));
}

void openInputFile(ifstream& ins, string label);

int main()
{
	int idNumber;
	int nbOfHours;
	double hourlyPay;
	string name;
	ifstream employees;
	ifstream payroll;
	LList<Employee> employeesList;

	openInputFile(employees, "employee");
	openInputFile(payroll, "payroll");

	while (employees >> idNumber >> hourlyPay)
	{
		getline(employees >> ws, name);
		Employee newEmployee(idNumber, hourlyPay, name);
		LListNode<Employee>* node = new LListNode<Employee>(newEmployee);
		employeesList.insertNode(node);
	}

	while (payroll >> idNumber >> nbOfHours)
	{		
		if (employeesList.findNode(idNumber) != nullptr)
		{
			(employeesList.findNode(idNumber)->getData()).incrementWage(nbOfHours);
		}
	}
	
	cout << "*********Payroll Information********" << endl;
	employeesList.sortNodesInDescendingOrder();
	employeesList.readNodes();
	cout << "*********End payroll**************" << endl;
	return 0;
}

void openInputFile(ifstream& inFile, string label)
{
	string filename;
	cout << "Which " << label << " file would you like to open?" << endl;
	cin >> filename;
	cout << endl;

	inFile.open(filename);

	while (!inFile)
	{
		cout << "Incorrect file name!" << endl;
		cout << "Which " << label << " file would you like to open?" << endl;
		cin >> filename;
		cout << endl;
		inFile.clear();
		inFile.open(filename);
	}
}
