/*
 * Book.cpp
 *
 *  Created on: Sep 30, 2017
 *      Author: abhineet
 */

#include "Book.h"

using namespace std;

Book::Book():isbn(""),lastName (""),firstName(""),bookTitle(""),bookCategory(Category::NONE){

}

Book::Book (string isbn, string last, string first, string title, Category category):
		isbn(isbn),lastName (last),firstName(first),bookTitle(title),bookCategory(category){

}

Book ::Book(string isbn, string last, string first, string title, string category){

	this->isbn = isbn;
	this->lastName = last;
	this->firstName = first;
	this->bookTitle = title;
	this->setBookCategory(category);
}

Book::~Book(){

}


  string Book :: getIsbn (){

    return this->isbn;
  }

  string Book :: getLastName (){

      return this->lastName;
    }

  string Book :: getFirstName (){

        return this->firstName;
      }

  string Book :: getBookTitle (){

        return this->bookTitle;
      }

  string Book :: getBookCategory (){

      if (bookCategory == Category::TECHNICAL){
    	  return "technical";
      }else if (bookCategory == Category::FICTION){
    	  return "fiction";
      }else if (bookCategory == Category::HISTORY){
    	 return "history";
      }else if (bookCategory == Category::NONE){
         return "none";
      }
    return "";
  }

   void Book :: setBookCategory(string& str){

	   if(str == "technical"){
	   bookCategory = Category::TECHNICAL;
	   }else if (str == "fiction")
	   {
		   bookCategory = Category::FICTION;
	   }else if (str == "history"){

		   bookCategory = Category::HISTORY;
	   }else if (str == "none")
		   bookCategory = Category::NONE;
   }

istream& operator >>(istream& istream, Book& catalog) {

    string cat;
	std::getline(istream,catalog.isbn,',');
    std::getline(istream,catalog.lastName,',');
    std::getline(istream,catalog.firstName,',');
    std::getline(istream,catalog.bookTitle,',');
    std::getline(istream,cat,'\n');
    catalog.setBookCategory(cat);
	return istream;
}

ostream& operator <<(ostream& ostream, Book& midBook) {

	ostream
				<< "Book{ISBN=" + midBook.getIsbn() + ", last="
						+ midBook.getLastName() + ", first="
						+ midBook.getFirstName() + ", title="
						+ midBook.getBookTitle() + ", category="
						+ midBook.getBookCategory() + "}";

	return ostream;
}
