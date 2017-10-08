#ifndef BOOK_H_
#define BOOK_H_

#include <string>
#include <stdlib.h>
using namespace std;


/**
 * The Book class.
 */
class Book
{
public:
    /**
     * Book categories.
     */
    enum class Category { FICTION, HISTORY, TECHNICAL, NONE };

    /**
     * Default constructor.
     */
    Book();

    /**
     * Constructor.
     */
    Book(string isbn, string last, string first, string title, Category category);
    Book(string isbn, string last, string first, string title, string category);

    /**
     * Destructor.
     */
    ~Book();

    string getIsbn();
    string getLastName();
    string getFirstName ();
    string getBookTitle();
    string getBookCategory();
    void setBookCategory(string& str);
    friend istream& operator >>(istream& ifstream,Book& str);
    friend ostream& operator <<(ostream& ostream,Book&str);

private:

    string isbn;
    string lastName;
    string firstName;
    string bookTitle;
    Category bookCategory;
};

#endif /* EMPLOYEE_H_ */
