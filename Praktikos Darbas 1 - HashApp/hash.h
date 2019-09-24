#pragma once

#include <string>
using std::string;


class Hash
{
private:
	static const size_t hash_length = 81;	//324/4 = 81

	string hash;
	//324 bit length
	string default_string = "abbcccddddeeeeeffffffggggggghhhhhhhhiiiiiiiiijjjjjjjjjjkkkkkkkkkkkllllllllllllmmmmmmmmmmmmmnnnnnnnnnnnnnnooooooooooooooopppppppppppppppprrrrrrrrrrrrrrrrrsssssssssssssssssstttttttttttttttttttuuuuuuuuuuuuuuuuuuuuvvvvvvvvvvvvvvvvvvvvvwwwwwwwwwwwwwwwwwwwwwwyyyyyyyyyyyyyyyyyyyyyyyyyyyyzzzzzzzzzzzzzzzzzzzzzzzz";


	void hashingAlgorithm(string str)
	{
		string copy_default_string = default_string;

		//hashing
		for (unsigned int i = 0; i < str.length(); i++)
			for (unsigned int j = 0; j < hash_length; j++)
			{
				int a = 0;
				do
				{
					//hash formula
					copy_default_string[j] = (copy_default_string[j] + 13 * str[i] * str[i] + a*i*j + a*a + a + j + ((copy_default_string[(i*j + str[i])%copy_default_string.length()] * str[i] + str[0]) ^ (default_string[i * str[i] % (hash_length - 1)]))) % 128;
					
					//a += (i + j)%41;
					a = (a + i + j)%89;
				} while (copy_default_string[j] < '0' || (copy_default_string[j] > '9' && (copy_default_string[j] < 'a' || copy_default_string[j] > 'f')));	//limit to 0-9 + a-f
			}
		// copy values to hash string
		for (int i = 0; i < hash_length; i++)
			hash += copy_default_string[i];
	}

public:

	//UI

	Hash(string str) { hashingAlgorithm(str); }

	Hash() { }

	string getHash() const { return hash; }

	inline void setHash(string str) { hashingAlgorithm(str); }
};