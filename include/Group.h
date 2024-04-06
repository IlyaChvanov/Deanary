//
// Created by user on 31.03.2024.
//

#ifndef DEANERY_GROUP_H
#define DEANERY_GROUP_H

#include "..//include/Student.h"
#include "Student.h"
#include <vector>
#include <string>

using std::vector, std::string;

class Student;

class Deanary;

class Group {
public:
    Group(const string &title) : title(title) {};

    int getAverageMark() const;

    const Student &getStudent(const string &) const;

    const Student &getStudent(size_t) const;

    vector<Student *> getAllStudents();

    void printIdOfStudents() const;

    const string &getTitle() const;

    void addStudent(Student &);

    void chooseHead(const Student *);

    void removeStudent(Student &);

    bool isEmpty() const;

    const Student &getHead() const;

private:
    string title;
    string spec;
    vector<Student> students;
    const Student *head = nullptr;

};

#endif //DEANERY_GROUP_H