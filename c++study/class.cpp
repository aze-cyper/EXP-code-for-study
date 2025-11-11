#include<iostream>
using namespace std;
class student{
private:
   // static const int a = 114514;
    int weight;
    int height;
public:
    student() : weight(0), height(0) {}
    student(int w,int h){weight = w;height = h;}
    void change_weight(int w){weight = w;}
    void show_weight(){cout << weight << endl;}
    student Sum(const student & s) const;
    student operator+(const student & s) const;
};
student student::Sum(const student & s) const{
    student stu;
    stu.weight =weight + s.weight;
    return stu;
}
student student::operator+(const student & s) const{
    student stu;
    stu.height =height + s.height;
    return stu;
}
int main(){
    student lbe{100,100};
    student a{900,900};
    a=a.Sum(lbe);
    a.show_weight();
}
