#include <fstream>
#include <iostream>

#include "..//include//Deanary.h"
#include "..//include/Student.h"
#include "..//include/Group.h"

using std::vector, std::string, std::endl, std::cout;

int main() {
    Deanary HSE;
    HSE.createGroups("..//bd/groups.txt");

    for (const auto &x : HSE.getGroups()) {
        cout << "Avarage mark in group " << x->getTitle() << " is " << x->getAverageMark() << endl;
    }
    HSE.addMarksToAll();
    cout << '\n';

    HSE.getStatistics();
    cout << endl << "Deleting everyone " << endl;;
    for (size_t i = 0; i < 92; i++)
        HSE.expulsion(i);

    cout<<"Adding new student"<<endl<<endl;
    Student student92(92, "Lobanov Eduard Vadimovich");
    student92.addMark(-10);
    student92.addToGroup(HSE.getGroups()[0]);
    HSE.hireStudents(student92);
    HSE.getStatistics();
    return 0;
}
