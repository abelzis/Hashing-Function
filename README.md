# Hashing-Function
Program takes input of a string and outputs a hash of the string.

# How to install?
Download the latest CMake [here](https://cmake.org/download/) and generate new solution from downloaded source code folder. Build or debug desired projects and enjoy!

# What is this and how to use?
There are three different projects in this solution:

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


# Is your hashing algorithm even good?

**tl;dr** It's good, but probably not as good as [SHA-512](https://en.wikipedia.org/wiki/SHA-3) or something familiar.

There are a few rules that describe a hashing algorithm. If every rule is passed, I consider the hashing algorithm as good, however not great. **The rules are:**

### 1) ✓ Input can be any string of any size.

My hash function can take string of any length. However, the length is based on computer memory.

![Random string](https://i.gyazo.com/bb2155f53d7e11a6626e7fec9628d266.png)

### 2) ✓ Output is a fixed size.

I have chosen 324 bit sized hash, which is base-16 with 81 characters.

![Hash](https://i.gyazo.com/9d0a98a82098d3d161f34f7a8d812e49.png)

### 3) ✓ The function is deterministic - which means not random.

### 4) ✓ Hashing has to be done quick.**

My hashing algorithm can hash about 30000 strings per second. Depending on CPU, optimization, length of strings etc.

### 5) ✓ One way - cannot convert the output back into input.

### 6) ✓ Practically, there's no two strings `s1` and `s2` that the following exists: `hash(s1) = hash(s2)`.

Yet no collisions have been found, that two different strings produce same hash.

Over 68,000 * 1,000,000 loops have been made to check 1 million strings if they collide. *Will be updated once the million is finished*.

![Over 68k * 1M loops](https://i.gyazo.com/bfeb57135f07021ac5297a2d445d79a2.png)

### 7) ✓ Changing the input ever so slightly - the output changes overall.

Let the images speak for themselves:

String 1:

![Before hash 1](https://i.gyazo.com/a5a9e6fd0a8b88af986619612ed7ce4f.png)

String 2:

![Before hash 2](https://i.gyazo.com/93673dfba1a9966071918b183cdfe4d4.png)

Hash 1:

![After hash 1](https://i.gyazo.com/14f143b6f9b759290d9497b080fd499b.png)

Hash 2:

![After hash 2](https://i.gyazo.com/ad7adffa01efbcdf56c0bc58a29053d9.png)

---------------------------------------------

In addition to 6th rule, here is how high mismatched hashes are comparing bits, when the strings differ only by 1 character (The higher - the better):

![Percentage](https://i.gyazo.com/45847398892958b881ee0e261b302fe1.png)

On average, about 30% bit difference between each hash is a very good result, considering the maximum is 40%. It is because each hash symbol is 8 bits in length. E.g.: `a` is `01100001` in binary. If we compare all possible bit ranges to each other:

`0` is `00110000`

`9` is `00111001`

`a` is `01100001`

`f` is `01100110`

you can notice that the 1st and 3rd bits are the same. So Only 6 bit difference could be between the possible characters. The average difference is about 2/6 ~ 33% because theres only 16 (4 bits) possible arangements available, therefore the difference between 6 and 4 is 2.
