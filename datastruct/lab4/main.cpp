#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class sorted{
private:

    int count = 0;
    vector <int> data;
    bool isSorted = false;

public:

    sorted(const string & filename);
    void Merge_sort();
    void Quick_sort();
    void Select_sort();
    void Insert_sort();

    void printData() const;
    bool is_sorted() const;
};

sorted::sorted(const string & filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "无法打开文件" << endl;
    }
    else{
        file >> count;
        data.resize(count);
        for(int i = 0;i < count;i++){
            file >> data[i];
        }
    }
}

void sorted::printData() const{
    if(count == 0){
        cout << "data无内容" << endl;
    }
    else{
        for(int i = 0;i < count;i++){
            cout << data[i] << " ";
        }
    }
}

void sorted::Merge_sort(){

}

void sorted::Quick_sort(){

}

void sorted::Insert_sort(){

}

void sorted::Select_sort(){
    
}

int main(){
    string filename = "D:\\EXP-code-for-study\\datastruct\\lab4\\test.txt";
    sorted s1(filename);
    s1.printData();
}


