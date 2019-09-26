# Hashing-Function
Program takes input of a string and outputs a hash of the string.

# How to install?
Download the latest CMake [here](https://cmake.org/download/) and generate new solution from downloaded source code folder.

# How to use?
There are three different projects in this solution.

### The main project is **HashingApp**, which hashes given strings:

The application takes arguments as filenames and hashes given strings in those files. The results are outputed to `.\Results\` folder.

#### Argument rules: `[mode] filename1 filename2 ... filenameN`

For example: `file1.txt file2.txt`

This set of arguments opens `file1.txt`, hashes it, and outputs to `.\Results\hash1.txt` folder; opens `file2.txt`, hashes it, and outputs to `.\Results\hash2.txt` folder.

Another example: `0 file.txt`

0 is selected as mode (currently only mode) which means that instead of hashing files, program will hash EACH line of the `file.txt`. Output will be placed to `.\Results\hash1.txt`.

Last example: *no arguments*

If no arguments are given, the program will try to open default file named `data.txt` and hash it, otherwise console UI will appear letting the user to write manually desired text. After the user input program hashes given string and outputs to console and `.\Results\consoleHash.txt`.

### Tier 2 project called **RandomStringGenerator** which generates randomized strings based on given character preset:


### And final tier 2 project called **CompareHashes** which can compare strings and hashes for testing purposes:

