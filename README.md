# Hashing-Function
Program takes input of a string and outputs a hash of the string.

# How to install?
Download the latest CMake [here](https://cmake.org/download/) and generate new solution from downloaded source code folder.

# What is this and how to use?
There are three different projects in this solution.

### The main project is **HashingApp**, which hashes given strings:

The application takes arguments as filenames and hashes given strings in those files. The results are outputed to `.\Results\` folder.

#### Argument rules: `[mode] filename1 filename2 ... filenameN`

----------------------------------------------------
For example: `file1.txt file2.txt`

This set of arguments opens `file1.txt`, hashes it, and outputs to `.\Results\hash1.txt` folder; opens `file2.txt`, hashes it, and outputs to `.\Results\hash2.txt` folder.

----------------------------------------------------
Another example: `0 file.txt`

0 is selected as mode (currently only mode) which means that instead of hashing files, program will hash EACH line of the `file.txt`. Output will be placed to `.\Results\hash1.txt`.

----------------------------------------------------
Last example: *no arguments*

If no arguments are given, the program will try to open default file named `data.txt` and hash it, otherwise console UI will appear letting the user to write manually desired text. After the user input program hashes given string and outputs to console and `.\Results\consoleHash.txt`.

----------------------------------------------------

### Tier 2 project called **RandomStringGenerator** which generates randomized strings based on given character preset:

This application takes 3 arguments: character preset, length of strings and quantity of strings. Then generates random strings and outputs to `generated_strings.txt`. Unicode is available to some extent.

#### Argument rules: `characterPreset lengthOfEachString stringCount`

----------------------------------------------------
For example: `abcdefghijklmnopqrstuvwxyz 5 100`

This argument list will generate 100 strings length of 5 containing `abcdefghijklmnopqrstuvwxyz` characters.



### And final tier 2 project called **CompareHashes** which can compare strings and hashes for testing purposes:

#### Argument list: `0`

This program takes 1 argument as either `0` or `1`. If argument is 0, it will try to read strings from file `hash_list.txt`, hash them and then compare every hash with every other hash in order to prove, that the hashing algorithm is good quality and proves important hashing rule: `hash(string1) =/= hash(string2)`, when string1 =/= string2.

----------------------------------------------------
#### Argument list: `1`

If the argument is 1, the program will try to read strings 2 at a time from file `hash_lists.txt`, hash them and compare bitwise. The outputs are average mismatches, minimum mismatches and maximum mismatches. *In general - higher percentage - better.*


