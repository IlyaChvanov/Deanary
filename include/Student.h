//
// Created by user on 31.03.2024.
//

#ifndef DEANERY_STUDENT_H
#define DEANERY_STUDENT_H

#include "..//include/Group.h"
#include <utility>
#include <vector>
#include <string>

using std::vector, std::string;

class Group;

class Student {
public:
    Student(size_t id, string fio) : id(id), fio(std::move(fio)) {}

    size_t getId() const;

    const string &getFio() const;

    const vector<int> &getMarks() const;

    const string &getGroupName() const;

    const Group *getGroup();

    bool operator==(const Student &) const;

    void addToGroup(const Group *);

    void addMark(int);

    double getAverageMark() const;

    bool isHeadOfGroup() const;

    void printMarks() const;

private:
    size_t id = 0;
    string fio;
    const Group *group = nullptr;
    vector<int> marks;
};


#endif //DEANERY_STUDENT_H
