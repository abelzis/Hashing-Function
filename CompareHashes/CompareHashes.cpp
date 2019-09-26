// CompareHashes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "hash.h"
using std::string;

//converts char to binary string of 8 bits
string charToBinary(char c)
{
	string temp;
	for (int i = 7; i >= 0; --i)
		temp += ((c & (1 << i)) ? '1' : '0');
	return temp;
}


int main(int argc, char* argv[])
{
	std::ifstream inp("hash_list.txt");

	string arg = argv[1];

	if (arg == "0")
	{
		std::vector<string> str_list, hash_list;
		str_list.reserve(1000500);
		hash_list.reserve(1000500);

		int count = 0;

		// read from file
		while (!inp.eof())
		{
			string temp;
			std::getline(inp, temp);
			str_list.push_back(temp);

			try
			{
				Hash hash(temp);
				hash_list.push_back(hash.getHash());
			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << "\n";
			}


			count++;
			if (count % 10000 == 0)
				std::cout << "count = " << count << "\n";

			//if (count % 100000 == 0)
			//	break;
		}

		str_list.shrink_to_fit();
		hash_list.shrink_to_fit();

		// compare hashes
		for (int i = 0; i < count; i++)
		{
			if (i % 100 == 0)
				std::cout << "i = " << i << "\n";

			for (int j = i; j < count; j++)
			{
				if (i != j)
				{
					if (str_list[j] != str_list[i])
					{

						if (hash_list[j] == hash_list[i])
						{
							std::cout << "COLLISION!!!\nSTRING1: " << str_list[j] << "\tHASH: " << hash_list[j] << "\n";
							std::cout << "STRING2: " << str_list[i] << "\tHASH: " << hash_list[i] << "\n";
							system("pause");
						}
					}
				}
			}
		}
	}

	else if (arg == "1")
	{
		int count = 0;

		double long max_dif = 0, min_dif = 1000000, average_dif = 0;
		int long long total_mismatch = 0;


		// read from file
		while (!inp.eof())
		{
			string temp1, temp2;
			std::getline(inp, temp1);
			std::getline(inp, temp2);

			try
			{
				Hash hash1(temp1), hash2(temp2);

				string hash_str1 = hash1.getHash(), hash_str2 = hash2.getHash();
				int mismatch = 0;

				//compare binary representations
				for (int i = 0; i < hash1.getHash().length(); i++)
				{
					string bin1 = charToBinary(hash_str1[i]);
					string bin2 = charToBinary(hash_str2[i]);

					//compare bits
					for (int j = 0; j < bin1.length(); j++)
					{
						if (bin1[j] != bin2[j])
							mismatch++;
					}
				}

				total_mismatch += mismatch;

				double long percent_mismatch = (double long)mismatch / (double long)(8.0 * hash_str1.length());
				if (percent_mismatch > max_dif)
					max_dif = percent_mismatch;

				if (percent_mismatch < min_dif)
					min_dif = percent_mismatch;



			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << "\n";
			}

			count++;
			if (count % 10000 == 0)
				std::cout << "count = " << count << "\n";

			//if (count % 100000 == 0)
			//	break;
		}

		average_dif = (double long)total_mismatch / (double long)(8 * 81 * count);

		std::cout << "Average dif = " << average_dif << "%\n";
		std::cout << "Max dif = " << max_dif << "%\n";
		std::cout << "Min dif = " << min_dif << "%\n";
	}
	else
		std::cout << "Please write a single argument as either \"0\" (compare hash to every other hash) or \"1\" (compare 2 hashes bitwise).\n";

}
