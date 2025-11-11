#include<iostream>
#include"class1.cpp"
using namespace std;
int main(){
    algorithm a = {6};
    algorithm b = {3};
    a = a + b;
    a.show_result();
}