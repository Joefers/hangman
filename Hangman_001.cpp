// Hangman_001.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <time.h>

#include <streambuf>
#include <windows.h>
#include <cstdio>
#include <sstream>
#include "resource.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	DWORD size = 0;
	const char* data = NULL;

	HMODULE handle = ::GetModuleHandle(NULL);
	HRSRC rc = ::FindResource(NULL, MAKEINTRESOURCE(IDR_MYTEXTFILE), MAKEINTRESOURCE(TEXTFILE));
	HGLOBAL rcData = ::LoadResource(handle, rc);
	size = ::SizeofResource(handle, rc);
	data = static_cast<const char*>(::LockResource(rcData));

	char* buffer = new char[size + 1];
	::memcpy(buffer, data, size);
	buffer[size] = 0;

	istringstream inputFile(buffer);


	//cout << buffer << endl;
	//ifstream inputFile(buffer);

	//Create input file from text file
	//ifstream inputFile("TextFile1.txt");

	vector<string> fileStrs;
	string inStr;

	while (getline(inputFile, inStr))
	{
		fileStrs.push_back(inStr);
	}

	//Pick random word 
	srand(time(NULL));
	int pickThis = rand() % fileStrs.size();
	string ourWord(fileStrs[pickThis]);

	vector<char> ourChars;
	vector<char> solvedChars;

	for (string::size_type i = 0; i != ourWord.size() - 1; ++i)
	{
		ourChars.push_back(ourWord[i]);
	}

	int guessesLeft = 10;

	bool gameRunning = true;

	while (gameRunning)
	{
		cout << "Guesses remaining: " << guessesLeft << endl << endl;

		bool anyBlanks = false;
		cout << "Your word is..." << endl;

		for (auto i : ourChars)
		{
			if (solvedChars.empty())
			{
				cout << "_ ";
				anyBlanks = true;
			}
			else if (find(solvedChars.begin(), solvedChars.end(), i) != solvedChars.end())
			{
				//This character was found within solved chars. Output normally.
				cout << i << " ";
			}
			else 
			{
				//This character was not solved for yet. Output as blank.
				cout << "_ ";
				anyBlanks = true;
			}
		}

		if (!anyBlanks)
		{
			cout << endl << endl << "YOU WIN!";
			cout << endl << "Your word was: " << ourWord;
			break;
		}

		cout << endl << endl << "Type in your guess: ";

		string inGuessStr;

		cin >> inGuessStr;
		char inGuess = inGuessStr[0];

		cout << endl;
		system("cls");

		if (find(ourChars.begin(), ourChars.end(), inGuess) != ourChars.end())
		{
			//Char was found. Correct guess.
			cout << inGuess << " is correct!" << endl << endl;
			solvedChars.push_back(inGuess);
		}
		else
		{
			//Char was not found. Incorrect guess.
			cout << inGuess << " is incorrect..." << endl << endl;
			--guessesLeft;
		}

		if (!guessesLeft)
		{
			cout << "Guesses remaining: " << guessesLeft << endl << endl;
			cout << "You lose...sorry!" << endl;
			cout << "Your word was: " << ourWord;
			break;
		}
	}

	cout << endl << endl;
	system("pause");
	return 0;
}

