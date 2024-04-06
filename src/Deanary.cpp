//
// Created by user on 31.03.2024.
//
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Deanary.h"
#include "Group.h"
#include "Student.h"


class Student;

class Group;

using std::find;

size_t getId(const string &student) {
    string sId;
    for (char c : student) {
        if (c == ' ')
            break;
        sId.push_back(c);
    }
    return stoull(sId);
}

string getFio(const string &student) {
    string fio;
    size_t numOfSpaces = 0;
    for (char c : student) {
        if (c == ' ')
            numOfSpaces++;
        if (numOfSpaces < 1)
            continue;
        if (numOfSpaces == 4)
            break;

        fio.push_back(c);
    }
    return fio.erase(0, 1);
}

vector<Group *> Deanary::getGroups() {
    vector<Group *> toReturn;
    toReturn.reserve(groups.size());
    for (auto &x : groups)
        toReturn.push_back(&x);
    return toReturn;
}

string getGroup(const string &student) {
    string group;
    size_t numOfSpaces = 0;
    for (char c : student) {
        if (c == ' ')
            numOfSpaces++;
        if (numOfSpaces < 4)
            continue;
        if (numOfSpaces == 4) {
            group.push_back(c);
        }
    }
    return group.erase(0, 1);
}


void pushMarks(std::vector<int>& marks, const string &student) {
    size_t numOfSpaces = 0;
    string currentMark;

    for (char c : student) {
        if (currentMark == "23cst5" || currentMark == "23cst6" || currentMark == "23cst7") {
            currentMark.erase();
            continue;
        }
        if (c == ' ') {
            numOfSpaces++;
            if (!currentMark.empty())
                marks.push_back(stoi(currentMark));
            currentMark.erase();
            continue;
        }
        if (numOfSpaces < 4)
            continue;

        currentMark.push_back(c);
    }
    if (!currentMark.empty())
        marks.push_back(stoi(currentMark));
}

void Deanary::bindWGroup() {
    for (auto &group : groups)
        for (auto student : group.getAllStudents())
            student->addToGroup(&group);
}


using std::endl;

void printToGroups(Deanary &deanary, const string &fgroups = "..//bd/groups.txt") {
    std::ofstream outGroups;
    outGroups.open(fgroups);
    for (Group *gr : deanary.getGroups()) {
        outGroups << gr->getTitle() << endl;
        for (const auto &st : gr->getAllStudents()) {
            outGroups << st->getId() << ' ' << st->getFio() << ' ';
            for (auto m : st->getMarks())
                outGroups << m << ' ';
            outGroups << endl;
        }
        outGroups << endl;
    }
}

void printToStudents(Deanary &deanary, const string &fstudents = "..//bd/students.txt") {
    std::ofstream outStudents;
    outStudents.open(fstudents);
    for (Group *gr : deanary.getGroups()) {
        for (const auto &st : gr->getAllStudents()) {
            outStudents << st->getId() << ' ' << st->getFio() << ' ' << st->getGroupName() << ' ';
            for (auto m : st->getMarks())
                outStudents << m << ' ';
            outStudents << endl;
        }
    }
}

void Deanary::saveStaff(const string &fgroups, const string &fstudents) {
    printToGroups(*this, fgroups);
    printToStudents(*this, fstudents);
}

void Deanary::createGroups(const string &path) {
    std::ifstream fileGroups(path);

    while (!fileGroups.eof()) {
        string groupTitle;

        getline(fileGroups, groupTitle);
        Group newGroup = Group(groupTitle);

        while (true) {
            string student;
            getline(fileGroups, student);
            if (student.empty())
                break;

            size_t id = getId(student);
            string fio = getFio(student);
            vector<int> marks;
            pushMarks(marks, student);

            Student newStudent(id, fio);
            for (auto z : marks)
                newStudent.addMark(z);

            newGroup.addStudent(newStudent);
        }
        groups.push_back(std::move(newGroup));
    }
    bindWGroup();
}


void Deanary::hireStudents(const std::string &path) {
    std::ifstream fileStudents(path);
    while (!fileStudents.eof()) {
        string student;
        getline(fileStudents, student);
        if (student.empty())
            break;

        size_t id = getId(student);
        string fio = getFio(student);
        vector<int> marks;
        pushMarks(marks, student);

        auto *newStudent = new Student(id, fio);
        for (auto z : marks)
            newStudent->addMark(z);

        string group = getGroup(student);
        for (auto &gr : this->groups) {
            if (gr.getTitle() == group) {
                newStudent->addToGroup(&gr);
                gr.addStudent(*newStudent);
                break;
            }
        }
    }
    saveStaff();
}

void Deanary::addMarksToAll() {
    for (auto &group : groups)
        for (auto &student : group.getAllStudents())
            student->addMark(rand() % 10);
    saveStaff();
}

void Deanary::getStatistics() {
    for (auto &group : groups) {
        if (!group.isEmpty()) {
            std::cout << "Group " << group.getTitle() << " marks:" << '\n';
            std::cout << "Avarage mark: " << group.getAverageMark();
        } else {
            std::cout << "Group " << group.getTitle() << " is empty" << '\n';
        }
        for (auto &student : group.getAllStudents()) {
            std::cout << std::endl;
            std::cout << student->getFio() << ':';
            student->printMarks();
        }
        std::cout << std::endl << "-----------" << std::endl;
    }
}

void Deanary::moveStudents(size_t id, Group &to) {
    for (auto &group : groups) {
        for (auto &student : group.getAllStudents()) {
            if (student->getId() == id) {
                to.addStudent(*student);
                group.removeStudent(*student);
                saveStaff();
                return;
            }
        }
    }
}

void Deanary::expulsion(size_t id) {
    for (auto &group : groups) {
        for (auto &student : group.getAllStudents()) {
            if (student->getId() == id) {
                group.removeStudent(*student);
                saveStaff();
                return;
            }
        }
    }
}

void Deanary::initHeads() {
    for (auto &group : groups) {
        double maxAvarageMark = -10;
        for (auto &student : group.getAllStudents()) {
            maxAvarageMark = std::max(maxAvarageMark, student->getAverageMark());
        }
        for (auto &student : group.getAllStudents()) {
            if (student->getAverageMark() == maxAvarageMark) {
                group.chooseHead(student);
                break;
            }
        }
    }
}


void Deanary::hireStudents(Student &student) {
    for (auto group : this->getGroups()) {
        if (group->getTitle() == student.getGroupName()) {
            group->addStudent(student);
            break;
        }
    }
    saveStaff();
}

