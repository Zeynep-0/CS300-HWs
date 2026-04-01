#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Author: Zeynep Taskin 33851
//Date: 04.12.2024 
//Purpose: This program checks if a given image is in the memory.


bool isPrime(int n)// function to check if the given integer is a prime number
{
	if (n == 2 || n == 3)
		return true;
	if (n == 1 || n % 2 == 0)
		return false;
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	return true;
}
int nextPrime(int n)// function to get the next closest prime to a number
{
	if (n % 2 == 0)
		n++;
	for (; !isPrime(n); n += 2)
		;
	return n;
}


class HashTable {// class for the data structure hashtable
private:
	enum EntryType { ACTIVE, EMPTY, DELETED };// enumarator to hold possible types of a space in hashtable
	struct HashStruct {// struct to hold hashtable spaces
		string element;// image itself
		EntryType info;// type of the space
		HashStruct(const string& e = string(), EntryType i = EMPTY)// constructor
			: element(e), info(i) { }
	};
	vector<HashStruct> array;// hashtable itself
	const string ITEM_NOT_FOUND;// string to use if an item is not found
	bool isActive(int currentPos) {// function to check if a position is available
		if (array[currentPos].info == ACTIVE) {// if the position is active it is available
			return true;
		}return false;
	};
	int hash(const string& x, int size) {// hash function
		int whiteSum = 0;// integer to hold white pixel number
		for (int i = 0; i < x.length(); i++) {
			while (i < x.length() && x[i] != 'W') {// until finding a white 
				i++;// continue
			}if (x[i - 2] && x[i - 2] != 'W') {// if the number is more than ten
				whiteSum += int(x[i - 2]) * 10;// add the number's decimal digit
			}
			whiteSum += int(x[i - 1]);// add the number

		}
		return (whiteSum % size);// return the mod of white pixel sum by size
	}
	int findPos(const string& x) {// find the position of a string
		int i = 1;// integer to use for linear probing
		int p = hash(x, array.size());// strings position according to hashing
		while (array[p].info == ACTIVE && array[p].element != x) {// linear probing until a position is found
			p += i;// go to the next position
			if (p >= array.size()) {// loop over the list
				p -= array.size();
			}
		}

		return p;// return the position found
	};

public:
	HashTable(const string& notFound, int size)// hashtable constructor
		: ITEM_NOT_FOUND(notFound), array(nextPrime(size))
	{	}

	void insert(const string& x) {// function to insert a string
		int currentPos = findPos(x);// find the position to insert

		if (isActive(currentPos))// if there is no place for this string
			return;

		array[currentPos] = HashStruct(x, ACTIVE);// add the string to the table
	};
	const string find(const string& x) {// function to find a string
		int currentPos = findPos(x);// get the x's position in the hashtable

		if (isActive(currentPos))// check if the position is active
			return array[currentPos].element;// return the found string

		return ITEM_NOT_FOUND;// if not found
	};
	void remove(const string& x) {// function to remove a string from the table
		int currentPos = findPos(x);// find the position of the string

		if (isActive(currentPos))// update the space's type to deleted
			array[currentPos].info = DELETED;
	};
};



string runLengthEncoding(string flat) {// function to encode a string
	string encodedStr;// string to store the encoded image
	char current = flat[0];// get the first character of the string
	int counter = 1;// update the counter
	for (int i = 1; i < flat.length(); i++) {// until the end of the string
		if (flat[i] == current) {// if the next character is the same as the last one
			counter += 1;// update the counter
		}
		else {
			encodedStr += to_string(counter);// add the counter data to the encode string
			if (current == '1') {// if the pixel is 1 
				encodedStr += "W";// add that it is the number of white pixels
			}
			else {
				encodedStr += "B";// add that it is the number of black pixels
			}
			current = flat[i];// update the current to the different pixel
			counter = 1;// restart the counter
		}
	}
	encodedStr += to_string(counter);// add the last number of pixels
	if (current == '1') {// and their color
		encodedStr += "W";
	}
	else {
		encodedStr += "B";
	}
	return encodedStr;// return the encoded string
}

int main() {
	string iN;
	cout << "Enter image number to insert into the hash table (or 'query' to continue): " << endl;// get the image number to insert
	cin >> iN;

	HashTable hashtable("notfound", 100);// create the hashtable to hold the images

	while (iN != "query") {// until the query is called
		fstream imgFile;
		string fileName = "image" + iN + ".txt";
		imgFile.open(fileName, ios::in);//open the image file wanted

		string input;
		string flattenedImage = "";// string to hold flattend image

		while (getline(imgFile, input)) {// until the end of the file
			for (int i = 0; i < 28; i++) {// get each character one by one
				// update the flattened character according to the file's contents to flatten the image
				if (input[i] == '0') {
					flattenedImage += "0";
				}
				else {
					flattenedImage += "1";
				}
			}
		}

		hashtable.insert(runLengthEncoding(flattenedImage));// insert the flattened and encoded image into hashtable
		cout << "Image " << iN << " inserted into the hash table." << endl;

		cout << "Enter image number to insert into the hash table (or 'query' to continue): " << endl;// get the next image
		cin >> iN;
	}

	string qN;
	cout << "Enter image number to query (or 'exit' to quit): " << endl;// get the wanted query
	cin >> qN;

	while (qN != "exit") {// until the user wants to exit
		fstream queryFile;
		string qFileName = "query" + qN + ".txt";
		queryFile.open(qFileName, ios::in);// open the wanted query file

		string query;
		string flattenedQuery = "";

		while (getline(queryFile, query)) {// until the end of the file
			for (int i = 0; i < 28; i++) {// flatten each character
				if (query[i] == '0') {
					flattenedQuery += "0";
				}
				else {
					flattenedQuery += "1";
				}
			}
		}

		string founded = hashtable.find(runLengthEncoding(flattenedQuery));// find the image in the hashtable

		if (founded != "notfound") {// if file is found
			cout << "RLE String for " << qFileName << " found in hash table." << endl;
			for (int j = 0; j < 784; j = j + 28) {// print the image line by line
				for (int i = j; i < j + 28; i++) {
					cout << flattenedQuery[i];
				}cout << endl;
			}
		}
		else {// if file is not found
			cout << "No match for the image with encoding: ";// return the encoded query image
			cout << runLengthEncoding(flattenedQuery) << endl;
		}

		cout << "Enter image number to query (or 'exit' to quit): " << endl;// get the next query
		cin >> qN;
	}
	cout << "Exiting the program!";// end the program
}