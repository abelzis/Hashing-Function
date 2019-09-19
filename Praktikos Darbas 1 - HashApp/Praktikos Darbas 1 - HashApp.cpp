// Praktikos Darbas 1 - HashApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <fstream>
#include "hash.h"

//read from file and write to file
void output(std::ifstream& inp, Hash hash)
{
	string text;
	while (!inp.eof())// && !text.empty())
	{
		//read text
		string temp;
		inp >> temp;
		text += temp;
	}

	if (text.empty())
	{
		std::cout << "\nFile is empty. Please retry.\n";
		inp.close();
		return;
	}

	if (!text.empty())
	{
		std::cout << "\n\nText: " << text;
		hash.setHash(text);

		std::ofstream out("hash.txt");
		
		out << hash.getHash();
		std::cout << "\nHash: " << hash.getHash() << "\n";

		return;
	}
}


int main()
{
	std::ifstream inp;
	string text;

	Hash hash;

	inp.open("data.txt", std::fstream::in);

	//in file
	if (inp.is_open())
	{
		std::cout << "Default text file \"data.txt\" is opened. Trying to read file...\n";

		output(inp, hash);
	}


	//by hand in console
	if (!inp.is_open())
	{
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
					std::cout << "\nError: " << ex.what();
				}


			}
			// if not accept, insert string in console
			else if (condition_char == 'N' || condition_char == 'n')
			{
				try
				{
					//get text
					std::cout << "Please input text to hash: ";
					std::getline(std::cin, text);
					while (text.empty())
						std::getline(std::cin, text);
					if (!text.empty())
					{
						hash.setHash(text);

						std::cout << "Hash: " << hash.getHash() << "\n";
						break;
					}
				}
				catch (std::exception ex)
				{
					std::cout << "\nError: " << ex.what();
					continue;
				}
			}
			else
				std::cout << "\nInvalid symbol. ";
		}
	}


}

