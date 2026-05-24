#include <iostream>
#include <string>
using namespace std;
struct student{
    public:
    string name;
    int age;    
    float marks;
    public:
    void display(){
        cout<<"name"<<name<<endl;
        cout<<"age"<<age<<endl;
        cout<<"marks"<<marks<<endl;
    }
    void input(){
        cout<<"enter name"<<endl;
        getline(cin, name);
        cout<<"enter age"<<endl;
        cin>>age;
        cout<<"enter marks"<<endl;
        cin>>marks;

    }
};
int main(){
    student s;
    s.input();
    s.display();
}