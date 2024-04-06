//
// Created by user on 31.03.2024.
//

#include "Student.h"
#include "Group.h"
#include "iostream"

const string &Student::getFio() const {
    return fio;
}

size_t Student::getId() const {
    return id;
}

void Student::addToGroup(const Group *otherGroupPtr) {
    group = otherGroupPtr;
}

void Student::addMark(int mark) {
    marks.push_back(mark);
}

double Student::getAverageMark() const {
    size_t numOfMarks = marks.size();
    double sum = 0;
    for (int z : marks)
        sum += z;
    return sum / numOfMarks;
}

bool Student::operator==(const Student &other) const {
    if (this->getId() == other.getId())
        return true;
    return false;
}

bool Student::isHeadOfGroup() const {
    if (group->getHead() == *this)
        return true;
    return false;
}

void Student::printMarks() const {
    for (auto mark : marks) {
        std::cout << mark << ' ';
    }
}

const vector<int> &Student::getMarks() const {
    return marks;
}

const string &Student::getGroupName() const {
    return group->getTitle();
}

const Group *Student::getGroup() {
    return group;
}



