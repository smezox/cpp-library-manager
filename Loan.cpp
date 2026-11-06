
#include "Loan.h"

Loan::Loan(string id, string book, string member,
           string issued, string due)
    : loanId(id),
      bookId(book),
      memberId(member),
      issueDate(issued),
      dueDate(due),
      returned(false) {
}

string Loan::getLoanId() const {
    return loanId;
}

string Loan::getBookId() const {
    return bookId;
}

string Loan::getMemberId() const {
    return memberId;
}

string Loan::getIssueDate() const {
    return issueDate;
}

string Loan::getDueDate() const {
    return dueDate;
}

bool Loan::isReturned() const {
    return returned;
}

void Loan::markReturned() {
    returned = true;
}