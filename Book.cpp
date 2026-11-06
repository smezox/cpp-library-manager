
#include "Book.h"

Book::Book(string id, string bookTitle, string bookAuthor,
           string bookCategory, int publicationYear,
           bool isAvailable, string borrower, string due)
    : bookId(id),
      title(bookTitle),
      author(bookAuthor),
      category(bookCategory),
      year(publicationYear),
      available(isAvailable),
      borrowerId(borrower),
      dueDate(due) {
}

// Getters
string Book::getBookId() const {
    return bookId;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getCategory() const {
    return category;
}

int Book::getYear() const {
    return year;
}

bool Book::isAvailable() const {
    return available;
}

string Book::getBorrowerId() const {
    return borrowerId;
}

string Book::getDueDate() const {
    return dueDate;
}

// Issue a book
bool Book::issueBook(string memberId, string due) {
    if (!available || memberId.empty() || due.empty()) {
        return false;
    }

    available = false;
    borrowerId = memberId;
    dueDate = due;

    return true;
}

// Return a book
bool Book::returnBook() {
    if (available) {
        return false;
    }

    available = true;
    borrowerId.clear();
    dueDate.clear();

    return true;
}