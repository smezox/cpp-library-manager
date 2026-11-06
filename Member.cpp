
#include "Member.h"

Member::Member(string id, string memberName)
    : memberId(id), name(memberName) {
}

string Member::getMemberId() const {
    return memberId;
}

string Member::getName() const {
    return name;
}