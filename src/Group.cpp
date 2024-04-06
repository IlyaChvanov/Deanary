//
// Created by user on 31.03.2024.
//
#include "Group.h"
#include "Student.h"
#include <iostream>

struct studentNotFound {
    string what = "Student was not found";
};

void Group::addStudent(Student &newStudent) {
    students.push_back(newStudent);
    newStudent.addToGroup(this);
}

void Group::chooseHead(const Student *newHead) {
    head = newHead;
}

int Group::getAverageMark() const {
    double marksSum = 0.0;
    size_t numOfStudents = students.size();
    for (const auto &st : students) {
        marksSum += st.getAverageMark();
    }

    return marksSum / numOfStudents;
}

const Student &Group::getStudent(const std::string &fio) const {
    for (auto st : students) {
        if (st.getFio() == fio)
            return st;
    }
    throw studentNotFound();
}

const Student &Group::getStudent(size_t id) const {
    for (const auto &st : students) {
        if (st.getId() == id)
            return st;
    }
    throw "Student not found";
}

void Group::removeStudent(Student &st) {
    for (auto it = students.begin(); it != students.end(); it++) {
        if (it->getId() == st.getId()) {
            st.addToGroup(nullptr);
            students.erase(it);
            return;
        }
        throw "Student not found";
    }
}

bool Group::isEmpty() const {
    if (students.empty())
        return true;
    return false;
}

const Student &Group::getHead() const {
    return *head;
}

const string &Group::getTitle() const {
    return title;
}

void Group::printIdOfStudents() const {
    for (const auto& student : students)
        std::cout << student.getId() << std::endl;
}

vector<Student *> Group::getAllStudents() {
    vector<Student *> toReturn;
    for (auto &st : students)
        toReturn.push_back(&st);
    return toReturn;
}



