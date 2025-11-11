#include<iostream>
using namespace std;
class algorithm{
private:
    int num;
public:
    algorithm(){}
    algorithm(int n){num = n;}
    algorithm operator+(const algorithm & n){
        algorithm n1;
        n1.num =114514; 
        return n1;
    }
    void show_result(){cout << num;}
};