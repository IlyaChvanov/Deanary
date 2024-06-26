//
// Created by user on 31.03.2024.
//

#ifndef DEANERY_GROUP_H
#define DEANERY_GROUP_H

#include <vector>
#include <string>
#include "..//include/Student.h"
#include "Student.h"

using std::vector, std::string;

class Student;

class Deanary;

class Group {
 public:
    explicit Group(const string &title) : title(title) {}

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
    vector<Student> students;// I couldn't use pointers((
    const Student *head = nullptr;
};

#endif  // DEANERY_GROUP_H
