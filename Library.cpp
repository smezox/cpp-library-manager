
#include "Library.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

using namespace std;

// Convert text to lowercase
string lowerText(string text) {
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char ch) {
            return static_cast<char>(tolower(ch));
        }
    );

    return text;
}

// Check whether text is empty or contains only spaces
bool blankText(const string& text) {
    return text.find_first_not_of(" \t\r\n") == string::npos;
}

// Parse CSV rows, including quoted fields
vector<string> parseCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char ch = line[i];

        if (ch == '"') {
            if (insideQuotes &&
                i + 1 < line.size() &&
                line[i + 1] == '"') {

                field += '"';
                i++;
            }
            else {
                insideQuotes = !insideQuotes;
            }
        }
        else if (ch == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
        }
        else {
            field += ch;
        }
    }

    if (insideQuotes) {
        return {};
    }

    fields.push_back(field);
    return fields;
}

// Escape CSV values
string escapeCSV(const string& value) {
    string result = "\"";

    for (char ch : value) {
        if (ch == '"') {
            result += "\"\"";
        }
        else {
            result += ch;
        }
    }

    result += "\"";
    return result;
}

// Constructor
Library::Library() : nextLoanNumber(1) {
}

// Find a book using its ID
int Library::findBookIndex(const string& bookId) const {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].getBookId() == bookId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// Find a member using their ID
int Library::findMemberIndex(const string& memberId) const {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].getMemberId() == memberId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// Add a new book
bool Library::addBook(const Book& book) {
    if (blankText(book.getBookId()) ||
        blankText(book.getTitle()) ||
        blankText(book.getAuthor()) ||
        blankText(book.getCategory()) ||
        book.getYear() <= 0 ||
        findBookIndex(book.getBookId()) != -1) {

        return false;
    }

    books.push_back(book);
    return true;
}

// Display all books
void Library::listBooks() const {
    cout << "\n========== BOOK LIST ==========\n";

    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(32) << "Title"
         << setw(20) << "Author"
         << setw(18) << "Category"
         << "Status\n";

    cout << string(95, '-') << "\n";

    for (const Book& book : books) {
        cout << left
             << setw(8) << book.getBookId()
             << setw(32) << book.getTitle()
             << setw(20) << book.getAuthor()
             << setw(18) << book.getCategory()
             << (book.isAvailable() ? "Available" : "Borrowed")
             << "\n";
    }
}

// Search books by ID or title
void Library::searchBook(const string& keyword) const {
    if (blankText(keyword)) {
        cout << "Search keyword cannot be empty.\n";
        return;
    }

    string search = lowerText(keyword);
    bool found = false;

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (const Book& book : books) {
        string id = lowerText(book.getBookId());
        string title = lowerText(book.getTitle());

        if (id.find(search) != string::npos ||
            title.find(search) != string::npos) {

            cout << "\nBook ID: " << book.getBookId();
            cout << "\nTitle: " << book.getTitle();
            cout << "\nAuthor: " << book.getAuthor();
            cout << "\nCategory: " << book.getCategory();
            cout << "\nYear: " << book.getYear();

            cout << "\nStatus: "
                 << (book.isAvailable() ? "Available" : "Borrowed");

            if (!book.isAvailable()) {
                cout << "\nBorrower: " << book.getBorrowerId();
                cout << "\nDue date: " << book.getDueDate();
            }

            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

// Check book availability
void Library::checkAvailability(const string& bookId) const {
    int index = findBookIndex(bookId);

    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    const Book& book = books[index];

    cout << "\nBook: " << book.getTitle();

    if (book.isAvailable()) {
        cout << "\nStatus: Available\n";
    }
    else {
        cout << "\nStatus: Borrowed\n";
        cout << "Borrower: " << book.getBorrowerId() << "\n";
        cout << "Due date: " << book.getDueDate() << "\n";
    }
}

// Register a member
bool Library::addMember(const Member& member) {
    if (blankText(member.getMemberId()) ||
        blankText(member.getName()) ||
        findMemberIndex(member.getMemberId()) != -1) {

        return false;
    }

    members.push_back(member);
    return true;
}

// Display all members
void Library::listMembers() const {
    cout << "\n========== MEMBER LIST ==========\n";

    if (members.empty()) {
        cout << "No members registered.\n";
        return;
    }

    for (const Member& member : members) {
        cout << "Member ID: " << member.getMemberId()
             << " | Name: " << member.getName() << "\n";
    }
}

// Issue a book
bool Library::issueBook(
    const string& bookId,
    const string& memberId,
    const string& issueDate,
    const string& dueDate
) {
    int bookIndex = findBookIndex(bookId);
    int memberIndex = findMemberIndex(memberId);

    if (bookIndex == -1) {
        cout << "Book not found.\n";
        return false;
    }

    if (memberIndex == -1) {
        cout << "Member not found.\n";
        return false;
    }

    if (blankText(issueDate) || blankText(dueDate) ||
        dueDate < issueDate) {

        cout << "Invalid issue date or due date.\n";
        return false;
    }

    Book& book = books[bookIndex];

    if (!book.issueBook(memberId, dueDate)) {
        cout << "Book is already borrowed.\n";
        return false;
    }

    string loanId = "L" + to_string(nextLoanNumber++);

    loans.emplace_back(
        loanId,
        bookId,
        memberId,
        issueDate,
        dueDate
    );

    cout << "Book issued successfully!\n";
    return true;
}

// Return a book
bool Library::returnBook(const string& bookId) {
    int bookIndex = findBookIndex(bookId);

    if (bookIndex == -1) {
        cout << "Book not found.\n";
        return false;
    }

    Book& book = books[bookIndex];

    if (book.isAvailable()) {
        cout << "This book is already available.\n";
        return false;
    }

    bool found = false;

    for (Loan& loan : loans) {
        if (loan.getBookId() == bookId &&
            !loan.isReturned()) {

            loan.markReturned();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Active loan record not found.\n";
        return false;
    }

    book.returnBook();

    cout << "Book returned successfully!\n";
    return true;
}

// Import the supplied seed CSV
bool Library::importSeedCsv(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open seed CSV file: "
             << filename << "\n";
        return false;
    }

    string line;

    if (!getline(file, line)) {
        cout << "CSV file is empty.\n";
        return false;
    }

    vector<string> header = parseCSVLine(line);

    const vector<string> expected = {
        "book_id", "title", "author", "category",
        "year", "status", "borrower_id", "due_date"
    };

    if (header != expected) {
        cout << "Invalid CSV header format.\n";
        return false;
    }

    int imported = 0;
    int skipped = 0;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        vector<string> row = parseCSVLine(line);

        if (row.size() != 8) {
            cout << "Malformed CSV row skipped.\n";
            skipped++;
            continue;
        }

        try {
            string id = row[0];
            string title = row[1];
            string author = row[2];
            string category = row[3];

            size_t position = 0;
            int year = stoi(row[4], &position);

            if (position != row[4].size()) {
                throw invalid_argument("Invalid year");
            }

            string status = lowerText(row[5]);
            string borrower = row[6];
            string due = row[7];

            if (blankText(id) ||
                blankText(title) ||
                blankText(author) ||
                blankText(category) ||
                year <= 0 ||
                (status != "available" &&
                 status != "borrowed")) {

                throw invalid_argument("Invalid record");
            }

            if (findBookIndex(id) != -1) {
                cout << "Duplicate book skipped: " << id << "\n";
                skipped++;
                continue;
            }

            bool available = (status == "available");

            if (!available &&
                (blankText(borrower) || blankText(due))) {

                throw invalid_argument("Missing borrower information");
            }

            Book book(
                id, title, author, category,
                year, available, borrower, due
            );

            books.push_back(book);

            if (!available) {
                if (findMemberIndex(borrower) == -1) {
                    members.emplace_back(
                        borrower,
                        "Existing Borrower " + borrower
                    );
                }

                string loanId = "L" +
                    to_string(nextLoanNumber++);

                loans.emplace_back(
                    loanId, id, borrower, "Unknown", due
                );
            }

            imported++;
        }
        catch (const exception&) {
            cout << "Invalid CSV record skipped.\n";
            skipped++;
        }
    }

    cout << "\nCSV import completed!\n";
    cout << "Books imported: " << imported << "\n";
    cout << "Rows skipped: " << skipped << "\n";

    return true;
}

// Save all records
bool Library::saveData() const {
    ofstream bookFile("data/books.csv");
    ofstream memberFile("data/members.csv");
    ofstream loanFile("data/loans.csv");

    if (!bookFile.is_open() ||
        !memberFile.is_open() ||
        !loanFile.is_open()) {

        cout << "Error: Could not open data files for saving.\n";
        return false;
    }

    // Save books
    bookFile
        << "book_id,title,author,category,year,status,borrower_id,due_date\n";

    for (const Book& book : books) {
        bookFile
            << escapeCSV(book.getBookId()) << ","
            << escapeCSV(book.getTitle()) << ","
            << escapeCSV(book.getAuthor()) << ","
            << escapeCSV(book.getCategory()) << ","
            << book.getYear() << ","
            << (book.isAvailable() ? "available" : "borrowed") << ","
            << escapeCSV(book.getBorrowerId()) << ","
            << escapeCSV(book.getDueDate()) << "\n";
    }

    // Save members
    memberFile << "member_id,name\n";

    for (const Member& member : members) {
        memberFile
            << escapeCSV(member.getMemberId()) << ","
            << escapeCSV(member.getName()) << "\n";
    }

    // Save loans
    loanFile
        << "loan_id,book_id,member_id,issue_date,due_date,returned\n";

    for (const Loan& loan : loans) {
        loanFile
            << escapeCSV(loan.getLoanId()) << ","
            << escapeCSV(loan.getBookId()) << ","
            << escapeCSV(loan.getMemberId()) << ","
            << escapeCSV(loan.getIssueDate()) << ","
            << escapeCSV(loan.getDueDate()) << ","
            << (loan.isReturned() ? "true" : "false") << "\n";
    }

    bookFile.close();
    memberFile.close();
    loanFile.close();

    if (bookFile.fail() ||
        memberFile.fail() ||
        loanFile.fail()) {

        cout << "Error: Could not write all records.\n";
        return false;
    }

    cout << "Library records saved successfully.\n";
    return true;
}

// Load records from saved files
bool Library::loadData(const string& seedFilename) {
    ifstream bookFile("data/books.csv");

    // Import original CSV on first startup
    if (!bookFile.is_open()) {
        cout << "No saved records found.\n";
        cout << "Importing original library dataset...\n";

        if (!importSeedCsv(seedFilename)) {
            return false;
        }

        return saveData();
    }

    books.clear();
    members.clear();
    loans.clear();

    nextLoanNumber = 1;

    string line;

    // Load books
    if (!getline(bookFile, line) ||
        parseCSVLine(line) != vector<string>{
            "book_id", "title", "author", "category",
            "year", "status", "borrower_id", "due_date"
        }) {

        cout << "Invalid books.csv header.\n";
        return false;
    }

    while (getline(bookFile, line)) {
        if (line.empty()) continue;

        vector<string> row = parseCSVLine(line);

        if (row.size() != 8) continue;

        try {
            size_t position = 0;
            int year = stoi(row[4], &position);

            if (position != row[4].size() ||
                year <= 0 ||
                blankText(row[0]) ||
                blankText(row[1]) ||
                blankText(row[2]) ||
                blankText(row[3]) ||
                findBookIndex(row[0]) != -1) {
                continue;
            }

            string status = lowerText(row[5]);

            if (status != "available" && status != "borrowed") {
                continue;
            }

            bool available = (status == "available");

            if (!available &&
                (blankText(row[6]) || blankText(row[7]))) {
                continue;
            }

            books.emplace_back(
                row[0], row[1], row[2], row[3],
                year, available, row[6], row[7]
            );
        }
        catch (const exception&) {
            cout << "Invalid saved book row skipped.\n";
        }
    }

    bookFile.close();

    // Load members
    ifstream memberFile("data/members.csv");

    if (memberFile.is_open()) {
        getline(memberFile, line);

        while (getline(memberFile, line)) {
            if (line.empty()) continue;

            vector<string> row = parseCSVLine(line);

            if (row.size() != 2 ||
                blankText(row[0]) ||
                blankText(row[1]) ||
                findMemberIndex(row[0]) != -1) {
                continue;
            }

            members.emplace_back(row[0], row[1]);
        }

        memberFile.close();
    }

    // Ensure all current borrowers have member records
    for (const Book& book : books) {
        if (!book.isAvailable() &&
            findMemberIndex(book.getBorrowerId()) == -1) {

            members.emplace_back(
                book.getBorrowerId(),
                "Existing Borrower " + book.getBorrowerId()
            );
        }
    }

    // Load loan history
    ifstream loanFile("data/loans.csv");

    if (loanFile.is_open()) {
        getline(loanFile, line);

        while (getline(loanFile, line)) {
            if (line.empty()) continue;

            vector<string> row = parseCSVLine(line);

            if (row.size() != 6 ||
                blankText(row[0]) ||
                blankText(row[1]) ||
                blankText(row[2]) ||
                (row[5] != "true" && row[5] != "false")) {
                continue;
            }

            Loan loan(
                row[0], row[1], row[2], row[3], row[4]
            );

            if (row[5] == "true") {
                loan.markReturned();
            }

            loans.push_back(loan);

            if (row[0].size() > 1 && row[0][0] == 'L') {
                try {
                    size_t position = 0;
                    int number = stoi(row[0].substr(1), &position);

                    if (position == row[0].size() - 1 &&
                        number >= 0) {

                        nextLoanNumber = max(
                            nextLoanNumber, number + 1
                        );
                    }
                }
                catch (const exception&) {
                    // Ignore loan IDs without numeric suffixes
                }
            }
        }

        loanFile.close();
    }

    // Rebuild missing active loans for borrowed books
    for (const Book& book : books) {
        if (!book.isAvailable()) {
            bool activeLoanFound = false;

            for (const Loan& loan : loans) {
                if (loan.getBookId() == book.getBookId() &&
                    !loan.isReturned()) {

                    activeLoanFound = true;
                    break;
                }
            }

            if (!activeLoanFound) {
                string loanId = "L" +
                    to_string(nextLoanNumber++);

                loans.emplace_back(
                    loanId,
                    book.getBookId(),
                    book.getBorrowerId(),
                    "Unknown",
                    book.getDueDate()
                );
            }
        }
    }

    cout << "\nSaved library records loaded successfully!\n";
    cout << "Books: " << books.size() << "\n";
    cout << "Members: " << members.size() << "\n";
    cout << "Loans: " << loans.size() << "\n";

    return true;
}