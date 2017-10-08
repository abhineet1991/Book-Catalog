/**
 * Assignment 6. Implementing Book Catalog
 *
 * CMPE 180-92 Data Structures and Algorithms in C++
 * Fall 2017
 *
 * Author: Abhineet Gupta
 *         Software Engineering
 *         San Jose State University
 */

#include "Book.h"
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

// Status codes.
enum class StatusCode {
	OK, DUPLICATE, NOT_FOUND, INVALID_COMMAND
};

/**
 * Find the book in the catalog with the given ISBN.
 * Use a binary search.
 * @param isbn the ISBN.
 * @param catalog the vector of book records.
 * @return the vector index of the book if found, else return -1.
 */
int find(const string isbn, const vector<Book>& catalog);
/**
 * Find the book in catalog with given author or category name.
 * Using Linear Search
 * @param searchType searchType.
 * @param catalog the vector of book records
 */
void findLinear(const string searchType, const string search,
		const vector<Book>& catalog);

/**
 * Remove the book with the given isbn from the catalog
 * @param isbn
 * @param catalog the vector of book records
 */
void removeBook(const string isbn, vector<Book>& catalog);

const string INPUT_FILE_NAME = "commands.in";

/**
 * The main. Open the command input file and loop to process commands.
 */
int main() {
	// Open the input file.
	ifstream input;
	input.open(INPUT_FILE_NAME.c_str(), ios_base::in);
	if (input.fail()) {
		cout << "Failed to open " << INPUT_FILE_NAME << endl;
		return -1;
	}

	vector<Book> catalog;  // book catalog

	char command;
	input >> command;  // read the first command
	int count = 0;
	string empty;
	/**
	 * Loop to read commands until the end of file.
	 */
	while (!input.fail()) {
		if (count != 0) {
			input >> command;
		}
		cout << endl << command << " ";

		if (command == '+') {
			std::getline(input, empty, ' ');
			Book book;
			input >> book;

			string isbn = book.getIsbn();
			vector<Book>::iterator it;
			int index = 0;
			bool existFlag = false;
			for (it = catalog.begin(); it != catalog.end(); it++, index++) {

				Book book = *it;
				if (isbn < book.getIsbn()) {
					break;
				} else if (isbn == book.getIsbn()) {
					existFlag = true;
					break;
				}
			}
			cout << " Inserted at index " << index << ": ";
			cout<<book;
			cout<<endl;
			if (existFlag) {
				cout << "*** Duplicate ISDN ***" << endl;
			} else {
				catalog.insert(catalog.begin() + index, book);
			}
		} else if (command == '?') {
			string stringType, search;
			std::getline(input, stringType, '\n');
			if (!stringType.empty()) {
				search = stringType.substr(stringType.find('=') + 1,
						stringType.length());
				stringType = stringType.substr(1, stringType.find('=') - 1);

				if (stringType == "isbn") {
					int index = find(search, catalog);   //perform Binary Search
					cout << "Book with ISBN " + search + ":" << endl;
					if (index != -1) {
						Book search = catalog[index];
						cout<<search;
						cout<<endl;
					}
					count++;
					continue;
				} else {
					if (stringType == "author") {
						cout << "Books by " + stringType + " " + search + ":"
								<< endl;
					} else if (stringType == "category") {
						cout << "Books in " + stringType + " " + search + ":"
								<< endl;
					}
				}
			} else {
				cout << "All books in the catalog:" << endl;
			}
			findLinear(stringType, search, catalog);
		} else if (command == '-') {
			std::getline(input, empty, ' ');
			string isbn = "";
			std::getline(input, isbn);
			removeBook(isbn, catalog);
		} else {
			std::getline(input, empty, '\n');
			if (!empty.empty())
				cout << "*** Invalid command ***" << endl;
		}
		count++;
		command = '\0';
	}

	return 0;
}

void removeBook(const string isbn, vector<Book>& catalog) {

	std::vector<Book>::iterator iterator;
	unsigned int index = 0;
	iterator = catalog.begin();
	for (; index < catalog.size(); iterator++, index++) {

		Book book = *iterator;
		if (isbn == book.getIsbn()) {
			cout << "Removed ";
			cout<<book;
			cout<<endl;
			break;
		}
	}
	if (index != catalog.size()) {
		catalog.erase(catalog.begin() + index);
	} else {
		Book notFound(isbn, "", "", "", "none");
		cout << "Removed ";
		cout<<notFound;
		cout<<endl;
		cout << "*** Book not found ***" << endl;
	}

}

void findLinear(const string searchType, const string searchstr,
		const vector<Book>& catalog) {

	unsigned int startIndex = 0;
	vector<Book> bookFound;
	while (startIndex <= catalog.size() - 1) {

		Book midBook = catalog[startIndex];

		if (searchType == "author") {

			if (midBook.getLastName() == searchstr) {
				cout<<midBook;
				cout<<endl;
			}

		} else if (searchType == "category") {

			if (midBook.getBookCategory() == searchstr) {
				cout<<midBook;
				cout<<endl;
			}
		} else if (searchType.empty()) {
			cout<<midBook;
			cout<<endl;
		}
		startIndex++;
	}

}

int find(const string isbn, const vector<Book>& catalog) {

	int endIndex = catalog.size() - 1;

	int startIndex = 0, midIndex;

	while (startIndex <= endIndex && endIndex >= 0) {

		midIndex = (startIndex + endIndex) / 2;

		Book midBook = catalog[midIndex];

		if (midBook.getIsbn() > isbn) {
			startIndex = midIndex + 1;
		} else if (midBook.getIsbn() < isbn) {
			endIndex = midIndex - 1;
		} else {
			return midIndex;
		}

	}

	return -1;
}
