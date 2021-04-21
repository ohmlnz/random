/* 
*  Write a checkbook balancing program. The program will read in, from the console, the following for all checks that were not cashed as of the last time you balanced your checkbook: the number of each check (int), the amount of the check (double), and whether or not it has been cashed (1 or 0, boolean in the array). 
*  Use an array with the class as the type. The class should be a class for a check. There should be three member variables to record the check number, the check amount, and whether or not the check was cashed. The class for a check will have a member variable of type Money (as defined on page 662 in the book; Display 11.9) to record the check amount. So, you will have a class used within a class. The class for a check should have accessor and mutator functions as 
*  well as constructors and functions for both input and output of a check.  In addition to the checks, the program also reads all the deposits (from the console; cin), the old and the new account balance (read this in from the user at the console; cin). You may want another array to hold the deposits. The new account balance should be the old balance plus all deposits, minus all checks that have been cashed.
*  The program outputs the total of the checks cashed, the total of the deposits, what the new balance should be, and how much this figure differs from what the bank says the new balance is. It also outputs two lists of checks: the checks cashed since the last time you balanced your checkbook and the checks still not cashed.[ edit: if you can, Display both lists of checks in sorted order from lowest to highest check number.]
*/

#include <iostream>
#include <vector>

using namespace std;

class Money {
public:
	// Constructor
	Money(double dollars);

	// Getters
	double get_value() const;

	// Setters
	void set_value(double value);

	// Operators
	friend Money operator +(const Money& amount1, const Money& amount2);
	friend Money operator -(const Money& amount1, const Money& amount2);
	Money& operator +=(const Money& rhs);
	Money& operator =(const Money& rhs);
	friend istream& operator >>(istream& ins, Money& amount);
	friend ostream& operator <<(ostream& outs, const Money& amount);
private:
	double dollarAmount;
};

Money::Money(double dollars = 0)
{
	dollarAmount = dollars;
}

double Money::get_value() const
{
	return dollarAmount;
}

void Money::set_value(double value)
{
	dollarAmount = value;
}

Money operator +(const Money& amount1, const Money& amount2)
{
	return amount1.dollarAmount + amount2.dollarAmount;
}

Money operator -(const Money& amount1, const Money& amount2)
{
	return amount1.dollarAmount - amount2.dollarAmount;
}

Money& Money::operator +=(const Money& rhs)
{
	this->dollarAmount += rhs.dollarAmount;
	return *this;
}

Money& Money::operator =(const Money& rhs)
{
	this->dollarAmount = rhs.dollarAmount;
	return *this;
}

istream& operator >>(istream& ins, Money& amount)
{
	ins >> amount.dollarAmount;
	return ins;
}

ostream& operator <<(ostream& outs, const Money& amount)
{
	outs << "$" << amount.dollarAmount;
	return outs;
}

class Check
{
public:
	// Constructor
	Check(int identifiyingNumber, Money amount, bool hasBeenCashed);

	// Getters
	double getCheckValue() const;
	bool getCashedStatus() const;

	// Setters
	void cashCheck();

	// Operators
	friend ostream& operator <<(ostream& outs, const Check& check);
	friend bool operator <(const Check& check1, const Check& check2);
	Check& operator =(const Check& rhs);
private:
	int identifiyingNumber;
	Money amount;
	bool hasBeenCashed;
};

Check::Check(int checkIdNumber, Money checkAmount, bool checkStatus)
{
	identifiyingNumber = checkIdNumber;
	amount = checkAmount;
	hasBeenCashed = checkStatus;
}

double Check::getCheckValue() const
{
	return amount.get_value();
}

void Check::cashCheck()
{
	hasBeenCashed = true;
}

bool Check::getCashedStatus() const
{
	return hasBeenCashed;
}

ostream& operator <<(ostream& outs, const Check& check)
{
	outs << "Check ID: " << check.identifiyingNumber << endl;
	outs << "Check Amount: " << check.amount << endl;
	outs << "Check Status: " << (check.hasBeenCashed ? "Processed" : "Unprocessed") << endl;
	return outs;
}

bool operator <(const Check& check1, const Check& check2)
{
	return check1.amount.get_value() < check2.amount.get_value();
}

Check& Check::operator =(const Check& rhs)
{
	this->identifiyingNumber = rhs.identifiyingNumber;
	this->amount = rhs.amount;
	this->hasBeenCashed = rhs.hasBeenCashed;
	return *this;
}

Money sumOfAllChecks(const vector <Check>& checks, bool hasBeenCashed);
Money sumOfAllDepositedCash(const vector <double>& depositedCash);
void printAllChecks(const vector <Check>& checks, bool hasBeenCashed);
vector<Check> sortChecks(vector <Check>& checks);
int findMinIndex(const vector <Check>& checks, int startIndex);

int main()
{
	int identifiyingNumber;
	bool hasBeenCashed;
	double amount = 0.0;
	Money oldBalance;
	Money currentBalance;
	Money pendingBalance;
	vector <Check> checks;
	vector <double> depositedCash;

	cout << "#####################################################" << endl;
	cout << "###  Welcome to your checkbook balancing program  ###" << endl;
	cout << "#####################################################" << endl << endl;

	cout << "1. Old balance" << endl;
	cout << "Please enter last month's balance: ";

	cin >> oldBalance;

	cout << endl;
	cout << "2. Record written checks" << endl;
	cout << "Enter one check per line, including the following information: ";
	cout << "ID number, amount, and cashed status (1 being cashed and 0 being not cashed)." << endl;
	cout << "Enter -1 when you're done inputting checks." << endl << endl;
	
	while (true)
	{
		cin >> identifiyingNumber;

		if (identifiyingNumber == -1)
		{
			break;
		}

		cin >> amount >> hasBeenCashed;

		checks.push_back(Check(identifiyingNumber, Money(amount), hasBeenCashed));
	}

	cout << endl;
	cout << "3. Deposit cash" << endl;
	cout << "Please enter the amount you would like to deposit. ";
	cout << "Each entry should be on a separate line" << endl;
	cout << "Enter -1 when you're done inputting deposits." << endl << endl;

	while (true)
	{
		cin >> amount;

		if (amount == -1)
		{
			break;
		}

		depositedCash.push_back(amount);
	}

	cout << endl;
	cout << "4. Current balance" << endl;
	cout << "The current balance is: ";
	currentBalance = (Money(oldBalance) + sumOfAllDepositedCash(depositedCash)) - sumOfAllChecks(checks, true);
	cout << currentBalance;

	cout << endl << endl;
	cout << "5. Cashed checks total" << endl;
	cout << "The sum of all cashed checks is: ";
	cout << sumOfAllChecks(checks, true);

	cout << endl << endl;
	cout << "6. Deposited cash total" << endl;
	cout << "The sum of all deposited cash is: ";
	cout << sumOfAllDepositedCash(depositedCash);

	cout << endl << endl;
	cout << "7. Pending Balance" << endl;
	cout << "The pending balance (actual balance - outstanding checks) is: ";
	pendingBalance = currentBalance - sumOfAllChecks(checks, false);
	cout << pendingBalance << endl;
	cout << "Difference with actual balance: " << pendingBalance - currentBalance << endl;

	cout << endl << endl;
	cout << "8. List of cashed checks" << endl;
	printAllChecks(sortChecks(checks), true);

	cout << endl << endl;
	cout << "9. List of uncashed checks" << endl;
	printAllChecks(sortChecks(checks), false);

	cout << endl;
	return 0;
}

Money sumOfAllChecks(const vector <Check>& checks, bool hasBeenCashed)
{
	Money amount;

	for (auto const& check : checks)
	{
		if (check.getCashedStatus() == hasBeenCashed)
		{
			amount += check.getCheckValue();
		}
	}

	return amount;
}

Money sumOfAllDepositedCash(const vector <double>& depositedCash)
{
	Money amount;
	for (auto const& cash : depositedCash)
	{
		amount += cash;
	}
	return amount;
}

void printAllChecks(const vector <Check>& checks, bool hasBeenCashed)
{
	for (auto const& check : checks)
	{
		if (check.getCashedStatus() == hasBeenCashed)
		{
			cout << check;
		}
	}

	if (checks.size() == 0)
	{
		cout << "There are currently no checks to print." << endl;
	}
}

vector<Check> sortChecks(vector <Check>& checks)
{
	for (int index = 0; index < checks.size(); index++)
	{
		int minIndex = findMinIndex(checks, index);
		Check oldCheck = checks[index];
		Check minCheck = checks[minIndex];
		checks[index] = minCheck;
		checks[minIndex] = oldCheck;
	}
	return checks;
}

int findMinIndex(const vector <Check>& checks, int startIndex)
{
	int minIndex = startIndex;

	for (int i = startIndex; i < checks.size(); i++)
	{
		if (checks[i] < checks[minIndex])
		{
			minIndex = i;
		}
	}
	return minIndex;
}
