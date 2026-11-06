
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

#include "Library.h"

using namespace std;

// Read non-empty text
string readText(const string& message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (value.find_first_not_of(" \t\r\n") != string::npos) {
            return value;
        }

        cout << "Input cannot be empty. Try again.\n";
    }
}

// Read a valid publication year
int readYear() {
    string input;

    while (true) {
        cout << "Enter publication year: ";
        getline(cin, input);

        stringstream ss(input);
        int year;
        char extra;

        if ((ss >> year) &&
            !(ss >> extra) &&
            year > 0 &&
            year <= 9999) {

            return year;
        }

        cout << "Invalid year! Enter a positive year.\n";
    }
}

// Validate date format YYYY-MM-DD
bool isValidDate(const string& date) {
    if (date.size() != 10 ||
        date[4] != '-' ||
        date[7] != '-') {
        return false;
    }

    for (size_t i = 0; i < date.size(); i++) {
        if (i == 4 || i == 7) continue;

        if (!isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    bool leapYear =
        (year % 400 == 0) ||
        (year % 4 == 0 && year % 100 != 0);

    if (leapYear) {
        daysInMonth[1] = 29;
    }

    return day >= 1 && day <= daysInMonth[month - 1];
}

// Read and validate a date
string readDate(const string& message) {
    while (true) {
        string date = readText(message);

        if (isValidDate(date)) {
            return date;
        }

        cout << "Invalid date! Use YYYY-MM-DD format "
             << "and enter a real calendar date.\n";
    }
}

// Display application menu
void displayMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "       LIBRARY MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "1. Add New Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Search Book\n";
    cout << "4. Register Member\n";
    cout << "5. Display All Members\n";
    cout << "6. Issue Book\n";
    cout << "7. Return Book\n";
    cout << "8. Check Book Availability\n";
    cout << "9. Exit\n";
    cout << "========================================\n";
}

// Add a book
void addNewBook(Library& library) {
    cout << "\n--- ADD NEW BOOK ---\n";

    string id = readText("Enter book ID: ");
    string title = readText("Enter book title: ");
    string author = readText("Enter author name: ");
    string category = readText("Enter category: ");
    int year = readYear();

    Book book(id, title, author, category, year, true);

    if (library.addBook(book)) {
        cout << "Book added successfully!\n";
    }
    else {
        cout << "Unable to add book. Check the details "
             << "or duplicate ID.\n";
    }
}

// Register a member
void registerMember(Library& library) {
    cout << "\n--- REGISTER MEMBER ---\n";

    string id = readText("Enter member ID: ");
    string name = readText("Enter member name: ");

    Member member(id, name);

    if (library.addMember(member)) {
        cout << "Member registered successfully!\n";
    }
    else {
        cout << "Unable to register member. "
             << "The ID may already exist.\n";
    }
}

// Search for a book
void searchBookMenu(const Library& library) {
    cout << "\n--- SEARCH BOOK ---\n";

    string keyword = readText("Enter book ID or title: ");

    library.searchBook(keyword);
}

// Issue a book
void issueBookMenu(Library& library) {
    cout << "\n--- ISSUE BOOK ---\n";

    string bookId = readText("Enter book ID: ");
    string memberId = readText("Enter member ID: ");

    string issueDate = readDate(
        "Enter issue date (YYYY-MM-DD): "
    );

    string dueDate;

    while (true) {
        dueDate = readDate(
            "Enter due date (YYYY-MM-DD): "
        );

        if (dueDate >= issueDate) {
            break;
        }

        cout << "Due date cannot be earlier than issue date.\n";
    }

    library.issueBook(
        bookId,
        memberId,
        issueDate,
        dueDate
    );
}

// Return a book
void returnBookMenu(Library& library) {
    cout << "\n--- RETURN BOOK ---\n";

    string bookId = readText("Enter book ID: ");

    library.returnBook(bookId);
}

// Check availability
void availabilityMenu(const Library& library) {
    cout << "\n--- CHECK BOOK AVAILABILITY ---\n";

    string bookId = readText("Enter book ID: ");

    library.checkAvailability(bookId);
}

// Main function
int main() {
    Library library;

    cout << "========================================\n";
    cout << " Welcome to Library Management System!\n";
    cout << "========================================\n";

    cout << "\nLoading library records...\n";

    if (!library.loadData(
        "data/library-records-sample.csv"
    )) {
        cout << "Unable to load library records.\n";
        return 1;
    }

    string choice;

    while (true) {
        displayMenu();

        cout << "Enter your choice (1-9): ";
        getline(cin, choice);

        if (choice == "1") {
            addNewBook(library);
        }
        else if (choice == "2") {
            library.listBooks();
        }
        else if (choice == "3") {
            searchBookMenu(library);
        }
        else if (choice == "4") {
            registerMember(library);
        }
        else if (choice == "5") {
            library.listMembers();
        }
        else if (choice == "6") {
            issueBookMenu(library);
        }
        else if (choice == "7") {
            returnBookMenu(library);
        }
        else if (choice == "8") {
            availabilityMenu(library);
        }
        else if (choice == "9") {
            cout << "\nSaving library records...\n";

            if (!library.saveData()) {
                cout << "Warning: Saving failed!\n";
                cout << "Please check your data folder.\n";
                return 1;
            }

            cout << "Thank you for using "
                 << "Library Management System!\n";

            break;
        }
        else {
            cout << "Invalid choice! "
                 << "Please enter a number from 1 to 9.\n";
        }

        // Automatically save records after each operation
        if (!library.saveData()) {
            cout << "Warning: Changes could not be saved!\n";
        }
    }

    return 0;
}