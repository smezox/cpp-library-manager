
#pragma once

#include <string>
using namespace std;

class Loan {
private:
    string loanId;
    string bookId;
    string memberId;
    string issueDate;
    string dueDate;
    bool returned;

public:
    // Constructor
    Loan(string id, string book, string member,
         string issued, string due);

    // Getters
    string getLoanId() const;
    string getBookId() const;
    string getMemberId() const;
    string getIssueDate() const;
    string getDueDate() const;
    bool isReturned() const;

    // Return operation
    void markReturned();
};