// Praktikos Darbas 1 - HashApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include "hash.h"
#include <Windows.h>

void printHash(const Hash& hash) { std::cout << "Hash: " << hash.getHash() << "\n"; }
void printError(const std::exception& ex) { std::cout << "\nError: " << ex.what(); }

//TODO LITHUANIAN LETTERS DO NOT WORK

void inputHash(Hash& hash)
{
	string text;
	//get text
	std::cout << "Please input text to hash: ";
	std::getline(std::cin, text);
	while (text.empty())
		std::getline(std::cin, text);
	if (!text.empty())
		hash.setHash(text);
}


//read from file and write to file
int output(std::ifstream& inp, Hash& hash)
{
	string text;
	while (!inp.eof())// && !text.empty())
	{
		//read text
		inp.ignore(3, '\n');
		string temp;
		inp >> temp;
		text += temp;
	}
	if (inp.eof())
		inp.close();

	if (text.empty())
	{
		std::cout << "\nFile is empty. Please retry.\n";
		inp.close();
		return 1;
	}

	if (!text.empty())
	{
		std::cout << "\n\nText: " << text << "\n";
		hash.setHash(text);

		std::ofstream out("hash.txt");
		
		out << hash.getHash();
		printHash(hash);

		return 0;
	}
	return 1;
}

void mainHash1(std::ifstream& inp, const char* filename)
{
	std::cout << "Text file \"" << filename << "\" is opened. Trying to read file...\n";

	Hash hash;
	if (output(inp, hash) == 0)
		return;
}

void mainHash2(std::ifstream& inp, const char* filename)
{
	Hash hash;

	//UI
	while (1)
	{
		std::cout << "No file is opened. Open file? (Y/N): ";
		char condition_char;
		std::cin >> condition_char;

		// if accept, read from file
		if (condition_char == 'Y' || condition_char == 'y')
		{
			std::cout << "\nEnter file name (filename.txt): ";
			string filename;
			std::cin >> filename;

			//open file
			try
			{
				inp.open(filename, std::fstream::in);
				//if open
				if (inp.is_open())
				{
					output(inp, hash);	//extract text and hash
					if (!inp.is_open())	//if not opened
						continue;
					break;
				}
				else
				{
					std::cout << "\nFile could not be opened. Please check the file name.\n";
					continue;
				}
			}
			catch (std::exception ex)
			{
				printError(ex);
			}


		}
		// if not accept, insert string in console
		else if (condition_char == 'N' || condition_char == 'n')
		{
			try
			{
				inputHash(hash);
				printHash(hash);
				break;
			}
			catch (std::exception ex)
			{
				printError(ex);
				continue;
			}
		}
		else
			std::cout << "\nInvalid symbol. ";
	}
}

void mainHash(std::ifstream& inp, const char* filename)
{
	//in file
	if (inp.is_open())
		mainHash1(inp, filename);

	//by hand in console
	if (!inp.is_open())
		mainHash2(inp, filename);
}


int main(int argc, char *argv[])
{
	//utf-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	//setlocale(LC_ALL, "Lithuanian");

	//setlocale(LC_ALL, "lt.LT.UTF-8");
	//std::cin.imbue(std::locale("Lithuanian"));
	//std::cout.imbue(std::locale("Lithuanian"));
	setvbuf(stdin, nullptr, _IOFBF, 1000);

	std::ifstream inp;
	//setvbuf(stdin, nullptr, _IOFBF, 1000);

	// if additional arguments are passed
	if (argc > 1)
	{
		// try to run all arguments as files
		for (int i = 1; i < argc; i++)
		{
			inp.open(argv[i], std::ifstream::in);

			//setvbuf(stdout, nullptr, _IOFBF, 1000);


			if (!inp.is_open())
				continue;

			mainHash1(inp, argv[i]);
		}
	}
	// else try to open default file
	else if (argc <= 1)
	{
		inp.open("data.txt", std::fstream::in);

		mainHash(inp, "data.txt");
	}

}

