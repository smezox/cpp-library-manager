
#pragma once

#include <string>
using namespace std;

class Book {
private:
    string bookId;
    string title;
    string author;
    string category;
    int year;
    bool available;
    string borrowerId;
    string dueDate;

public:
    // Constructor
    Book(string id, string bookTitle, string bookAuthor,
         string bookCategory, int publicationYear,
         bool isAvailable, string borrower = "",
         string due = "");

    // Getters
    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    int getYear() const;
    bool isAvailable() const;
    string getBorrowerId() const;
    string getDueDate() const;

    // Book operations
    bool issueBook(string memberId, string due);
    bool returnBook();
};