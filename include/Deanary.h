//
// Created by user on 31.03.2024.
//
#ifndef DEANERY_DEANARY_H
#define DEANERY_DEANARY_H

#include <vector>
#include "Group.h"
#include <fstream>
#include <string>

using std::vector, std::string;

class Group;

class Deanary {
 public:
    vector<Group *> getGroups();

    void getStatistics();

    void createGroups(const string & = "..//bd/groups.txt");

    void hireStudents(const string & = "..//bd/students.txt");

    void hireStudents(Student &);

    void addMarksToAll();

    void moveStudents(size_t, Group &);

    void expulsion(size_t);

    void initHeads();

 private:
    void saveStaff(const string &fgroups = "..//bd/groups.txt", const string &fstudents = "..//bd/students.txt");

    vector<Group> groups;

    void bindWGroup();
};

#endif  // DEANERY_DEANARY_H