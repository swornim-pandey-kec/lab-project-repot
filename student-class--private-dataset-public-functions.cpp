#include<iostream>
#include<string>
using namespace std;
class student{
    string name;
    int age;
    float marks;
    public:
    void input(){
        cout<<"enter name\n";
        getline(cin,name);
        cout<<"enter age\n";
        cin>>age;
        cout << "enter marks\n";
        cin >> marks;
        cin.ignore(); // To ignore the newline character left by cin

    }
    void display(){
        cout<<"name: "<<name<<endl;
        cout<<"age: "<<age<<endl;
        cout<<"marks: "<<marks<<endl;
        
    }
};
int main(){
    student s;
    s.input();
    s.display();
    return 0;
    
}