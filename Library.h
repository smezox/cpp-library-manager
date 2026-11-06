
#pragma once

#include <vector>
#include <string>

#include "Book.h"
#include "Member.h"
#include "Loan.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Loan> loans;

    int nextLoanNumber;

    int findBookIndex(const string& bookId) const;
    int findMemberIndex(const string& memberId) const;

public:
    Library();

    // Book management
    bool addBook(const Book& book);
    void listBooks() const;
    void searchBook(const string& keyword) const;
    void checkAvailability(const string& bookId) const;

    // Member management
    bool addMember(const Member& member);
    void listMembers() const;

    // Loan management
    bool issueBook(
        const string& bookId,
        const string& memberId,
        const string& issueDate,
        const string& dueDate
    );

    bool returnBook(const string& bookId);

    // CSV import and file persistence
    bool importSeedCsv(const string& filename);
    bool saveData() const;
    bool loadData(const string& seedFilename);
};