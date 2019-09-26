// Praktikos Darbas 1 - HashApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cerrno>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "hash.h"
#include "TimerClass.h"

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
		//inp.ignore(3, '\n');
		string temp;
		//inp >> temp;
		std::getline(inp, temp);
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
		out << hash.getHash() << "\n";
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

std::ifstream setInputStream(const string& filename)
{
	// try open file
	std::ifstream ifstream;
	ifstream.open(filename, std::ifstream::in);
	if (ifstream.is_open())
		std::cout << "Success\n";
	return ifstream;
}


int main(int argc, char *argv[])
{
	// utf-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	// results directory strings
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
		// if second argument is 0, 1 line = 1 hash
		string temp_argv1 = argv[1];
		if (temp_argv1 == "0")
		{
			for (int i = 2; i < argc; i++)
			{
				std::cout << "-------------------------------------------------\n";
				std::cout << "Opening file \"" << argv[i] << "\"...\n";

				// open file
				std::ifstream inp = setInputStream(argv[i]);

				if (!inp.is_open())
				{
					std::cout << "Fail. Skipping this file.\n";
					continue;
				}

				try
				{
					// create output file
					string output_file_str = results_dir_ + "\\" + "hash" + std::to_string(i-1) + ".txt";	// file format "directory\hashX.txt"
					std::ofstream out(output_file_str, std::ifstream::out);

					//create timer
					Timer timer;
					timer.pause();
					std::cout << "Beginning hashing...";

					// read from file
					int line_count = 0;
					while (!inp.eof())// && !text.empty())
					{
						string temp;
						std::getline(inp, temp);

						line_count++;
						if (temp.empty())
							continue;

						timer.resume();
						Hash hash(temp);	//hashing
						timer.pause();

						// print to results file
						out << "line " << line_count << ": \t";
						output(out, hash);

					}
					if (inp.eof())
					{
						std::cout << "Hashing Finished! Took: " << timer.elapsed() << "s\n";
						inp.close();
					}

					std::cout << "\nOutput stream succeeded! Please refer outputs to: \"" << output_file_str << "\n";
				}
				catch (std::exception ex)
				{
					printError(ex);
				}
			}
		}
		// else 1 file = 1 hash
		else
		{
			// try to run all arguments as files
			for (int i = 1; i < argc; i++)
			{
				std::cout << "-------------------------------------------------\n";
				std::cout << "Opening file \"" << argv[i] << "\"...\n";

				// open file
				std::ifstream inp = setInputStream(argv[i]);

				if (!inp.is_open())
				{
					std::cout << "Fail. Skipping this file.\n";
					continue;
				}

				try
				{
					// try hashing and then outputing results in file in seperate folder
					std::cout << "Beginning hashing...";
					Timer timer;
					Hash hash(readInput(inp));
					std::cout << "Hashing Finished! Took: " << timer.elapsed() << "s\n";

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
			std::cout << "Beginning hashing...";
			Timer timer;
			Hash hash(readInput(inp));
			std::cout << "Hashing Finished! Took: " << timer.elapsed() << "s\n";

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
			string temp = consoleInputString();

			Timer timer;
			std::cout << "Beginning hashing...";
			Hash hash(temp);
			std::cout << "Hashing Finished! Took: " << timer.elapsed() << "s\n";

			string output_file_str = results_dir_ + "\\consoleHash.txt";	// file format "directory\hashX.txt"
			std::ofstream out(output_file_str, std::ifstream::out);

			output(out, hash);
			std::cout << "\nOutput stream succeeded! Please refer outputs to: \"" << output_file_str << "\n";

			printHash(hash);
		}


	}

}

