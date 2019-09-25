// Praktikos Darbas 1 - HashApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <direct.h>
#include <cerrno>
#include <fstream>
#include "hash.h"
#include <Windows.h>

void printHash(const Hash& hash) { std::cout << "Hash: " << hash.getHash() << "\n"; }
void printError(const std::exception& ex) { std::cout << "\nError: " << ex.what(); }

//TODO LITHUANIAN LETTERS DO NOT WORK

string consoleInputString()
{
	string text;
	//get text
	std::cout << "\nPlease input text to hash: ";
	std::getline(std::cin, text);
	while (text.empty())
		std::getline(std::cin, text);
	if (!text.empty())
		return text;
}

string readInput(std::ifstream& inp)
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
	{
		inp.close();
		return text;
	}


	if (text.empty())
	{
		std::cout << "\nFile is empty. Please retry.\n";
		inp.close();
		return "";
	}
}

//read from file and write to file
void output(std::ofstream& out, Hash& hash)
{
	try
	{
		out << hash.getHash();
	}
	catch (std::exception ex)
	{
		printError(ex);
	}
}

const string createNewDirectory(const string& str)
{
	// creating new directory for output files
	std::cout << "Trying to make \".\\" << str << "\" folder...\n";
	_mkdir(str.c_str());
	if (errno == EEXIST)
	{
		std::cout << "No new file created: " << std::strerror(errno) << "\n";
		return str;
	}
	//std::cout << "Folder already exists.\n";
	else if (errno == ENOENT)
	{
		std::cout << "Error: " << std::strerror(errno) << "\n";
		return "";
	}
	else
	{
		std::cout << "Success\n";
		return str;
	}
	return "";
}


int main(int argc, char *argv[])
{
	//utf-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setvbuf(stdin, nullptr, _IOFBF, 1000);

	const string results_dir = "Results";
	string results_dir_ = "";

	try
	{
		results_dir_ = createNewDirectory(results_dir);
	}
	catch (std::exception ex)
	{
		printError(ex);
	}

	std::cout << "\n\n";

	// if additional arguments are passed
	if (argc > 1)
	{
		// try to run all arguments as files
		for (int i = 1; i < argc; i++)
		{
			std::cout << "-------------------------------------------------\n";
			std::cout << "Opening file \"" << argv[i] << "\"...\n";

			// try open file
			std::ifstream inp;
			inp.open(argv[i], std::ifstream::in);
			if (inp.is_open())
				std::cout << "Success\n";

			if (!inp.is_open())
			{
				std::cout << "Fail. Skipping this file.\n";
				continue;
			}

			try
			{
				// try hashing and then outputing results in file in seperate folder
				Hash hash(readInput(inp));
				string output_file_str = results_dir_ + "\\" + "hash" + std::to_string(i) + ".txt";	// file format "directory\hashX.txt"
				std::ofstream out(output_file_str, std::ifstream::out);
				

				output(out, hash);
				std::cout << "\nOutput stream succeeded! Please refer outputs to: \"" << output_file_str << "\n";

				printHash(hash);
			}
			catch (std::exception ex)
			{
				printError(ex);
			}
		}
	}
	// else try to open default file
	else if (argc <= 1)
	{
		std::cout << "-------------------------------------------------\n";

		std::ifstream inp;

		string default_file = "data.txt";	// DEFAULT FILE STRING

		std::cout << "Opening default file \"" << default_file << "\"...\n";

		bool opened = false;

		inp.open(default_file, std::fstream::in);
		if (inp.is_open())
		{
			opened = true;
			std::cout << "Success\n";

			// try hashing and then outputing results in file in seperate folder
			Hash hash(readInput(inp));
			string output_file_str = results_dir_ + "\\" + "hash" + default_file;	// file format "directory\hashX.txt"
			std::ofstream out(output_file_str, std::ifstream::out);


			output(out, hash);
			std::cout << "\nOutput stream succeeded! Please refer outputs to: \"" << output_file_str << "\n";

			printHash(hash);
		}




		if (opened == false)
		{
			std::cout << "Fail. Skipping this file.\n";
			std::cout << "Switching to console UI.\n";

			// try hashing and then outputing results in file in seperate folder
			Hash hash(consoleInputString());

			string output_file_str = results_dir_ + "\\consoleHash.txt";	// file format "directory\hashX.txt"
			std::ofstream out(output_file_str, std::ifstream::out);

			output(out, hash);
			std::cout << "\nOutput stream succeeded! Please refer outputs to: \"" << output_file_str << "\n";

			printHash(hash);
		}


	}

}

