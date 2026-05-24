#include <iostream>
using namespace std;
struct student
{
    int id;
    char name[20];
    float marks;
};
int main()
{
    student s1;
    cout << "Enter student id: ";
    cin >> s1.id;
    cout << "Enter student name: ";
    cin >> s1.name;
    cout << "Enter student marks: ";
    cin >> s1.marks;

    cout << "Student Details:" << endl;
    cout << "ID: " << s1.id << endl;
    cout << "Name: " << s1.name << endl;
    cout << "Marks: " << s1.marks << endl;

    return 0;
}