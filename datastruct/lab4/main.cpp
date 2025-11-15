#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class sorted{
private:

    int count = 0;
    vector <int> data;
    bool isSorted = false;
    
    void insertSortHelper(){
        int n = data.size();
        for (int i = 1; i < n; i++) {
            int key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }

    void selectionSortHelper(){
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (data[j] < data[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(data[i], data[minIndex]);
            }
        }
    }

    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSortHelper(low, pi - 1);
            quickSortHelper(pi + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = data[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (data[j] <= pivot) {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return i + 1;
    }

    void mergeSortHelper(int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSortHelper(left, mid);
        mergeSortHelper(mid + 1, right);
        merge(left, mid, right);
    }
    
    void merge(int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            if (data[i] <= data[j]) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
            }
        }
        
        while (i <= mid) temp[k++] = data[i++];
        while (j <= right) temp[k++] = data[j++];
        
        for (int p = 0; p < k; p++) {
            data[left + p] = temp[p];
        }
    }

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
        cout << endl;
    }
}

void sorted::Merge_sort(){
    if (data.empty() || isSorted) return;
    mergeSortHelper(0, data.size() - 1);
    isSorted = true;
}

void sorted::Quick_sort(){
    if (data.empty() || isSorted) return;
    quickSortHelper(0, data.size() - 1);
    isSorted = true;
}

void sorted::Insert_sort(){
    if (data.empty() || isSorted) return;
    insertSortHelper();
    isSorted = true;
}

void sorted::Select_sort(){
    if (data.empty() || isSorted) return;
    selectionSortHelper();
    isSorted = true;
}

int main(){
    string filename = "D:\\EXP-code-for-study\\datastruct\\lab4\\test2.txt";
    sorted s1(filename);
    s1.printData();
    s1.Merge_sort();
    s1.printData();
}


