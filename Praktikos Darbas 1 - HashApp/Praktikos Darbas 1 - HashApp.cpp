// Praktikos Darbas 1 - HashApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "hash.h"

int main()
{
	std::ifstream inp;
	string text;

	Hash hash;

	inp.open("data.txt", std::fstream::in);

	//in file
	if (inp.is_open())
	{
		while (!inp.eof())
		{
			//read text
			string temp;
			inp >> temp;
			text += temp;
		}

		if (text.empty())
			inp.close();
		if (!text.empty())
		{
			hash.setHash(text);

			std::ofstream out("hash.txt");
			out << hash.getHash();
		}
	}
	//by hand in console
	if (!inp.is_open())
	{
		std::cout << "Please input text to hash: ";
		std::getline(std::cin, text);
		while (text.empty())
			std::getline(std::cin, text);

		hash.setHash(text);

		std::cout << hash.getHash() << "\n";
	}


}

