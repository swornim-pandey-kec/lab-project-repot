#include <iostream>

using namespace std;

struct s
{
private:
    int num;
    
public:
    void setData(int n)
    {
        num = 10;
    }

    void getData()
    {
        cout << num << endl;
    }
};
int main()
{
    s student;
    student.setData(10);

    student.getData();
    

    return 0;
}