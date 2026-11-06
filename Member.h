
#pragma once

#include <string>
using namespace std;

class Member {
private:
    string memberId;
    string name;

public:
    // Constructor
    Member(string id, string memberName);

    // Getters
    string getMemberId() const;
    string getName() const;
};