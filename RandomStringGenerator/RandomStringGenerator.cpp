// RandomStringGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "RandomEngine.h"
using std::string;


string generateString(const string& preset, const size_t& length)
{
	RandomEngine re;

	std::uniform_int_distribution<int> dist = re.uni_int_distr(0, (int)preset.length());

	string temp;
	temp.reserve(length);
	for (int i = 0; i < length; i++)
		temp += preset[dist(re.mt)];


	return temp;
}

string generateSimilarString(const string& str, const string& preset)
{
	RandomEngine re;
	
	std::uniform_int_distribution<int> dist = re.uni_int_distr(0, (int)preset.length()), dist2 = re.uni_int_distr(0, (int)str.length());

	string str2 = str;
	while (str2 == str)
		str2[dist2(re.mt)] = preset[dist(re.mt)];

	return str2;
}

int main(int argc, char* argv[])
{
	// utf-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	if (argc <= 3)
	{
		std::cout << "Error: there have to be 3 arguments - Character preset, Number of characters per string, number of strings.\n";
	}
	if (argc > 3)
	{
		string preset = argv[1];
		std::size_t length = std::stoi(argv[2]);
		std::size_t num_of_strings = std::stoi(argv[3]);

		std::ofstream out("generated_strings.txt");
		//const char utf8BOM[] = { 0xEF,0xBB,0xBF };
		//out.write(utf8BOM, sizeof(utf8BOM));
		for (int i = 0; i < num_of_strings; i++)
		{
			string str1, str2;
			str1 = generateString(preset, length);
			out << str1 << "\n";

			//OPTIONAL TO GENERATE SIMILAR STRINGS:
			str2 = generateSimilarString(str1, preset);
			out << str2 << "\n";
		}

		out.close();
	}
}