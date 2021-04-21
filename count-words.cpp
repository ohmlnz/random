#include <iostream>
#include <string>

using namespace std;

string* createWordsArray(string sentence, int& outWordsArrSize);
int countWordsInString(string& line);
void printResults(string arr[], int arrSize);

int main()
{
	int wordsArrSize;
	string sentence;

	cout << "Enter a sentence:" << endl;
	getline(cin, sentence);

	string* arrayOfWords = createWordsArray(sentence, wordsArrSize);
	cout << endl << "Result from the array:" << endl;
	printResults(arrayOfWords, wordsArrSize);
	cout << endl << "Size of the final array: " << wordsArrSize << endl;

	delete[] arrayOfWords;
	arrayOfWords = nullptr;

	return 0;
}

string* createWordsArray(string sentence, int& outWordsArrSize)
{
	int numberOfWords = countWordsInString(sentence);
	int currentIndex = 0;
	string* arrayOfWords = new string[numberOfWords];
	string currentString = sentence;

	while (currentIndex < numberOfWords)
	{
		size_t spaceIndex = currentString.find(' ');
		arrayOfWords[currentIndex] = currentString.substr(0, spaceIndex);
		currentIndex++;
		currentString = currentString.substr(spaceIndex + 1);
	}

	outWordsArrSize = numberOfWords;
	return arrayOfWords;
}


int countWordsInString(string& line)
{
	int totalWords = 1;

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ' && line[i - 1] != ' ')
		{
			totalWords++;
		}
	}
	return totalWords;
}


void printResults(string arr[], int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}
