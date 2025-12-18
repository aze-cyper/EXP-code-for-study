#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;
    
    BSTNode* insertHelper(BSTNode* node, int val) {
        if (node == nullptr) {
            return new BSTNode(val);
        }
        
        if (val < node->data) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->data) {
            node->right = insertHelper(node->right, val);
        }
        
        return node;
    }
    
    BSTNode* searchHelper(BSTNode* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (val == node->data) {
            return node;
        } else if (val < node->data) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }
    
    BSTNode* findMin(BSTNode* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    BSTNode* deleteHelper(BSTNode* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (val < node->data) {
            node->left = deleteHelper(node->left, val);
        } else if (val > node->data) {
            node->right = deleteHelper(node->right, val);
        } else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            
            BSTNode* minRight = findMin(node->right);
            node->data = minRight->data;
            node->right = deleteHelper(node->right, minRight->data);
        }
        
        return node;
    }
    
    void inorderHelper(BSTNode* node, vector<int>& result) {
        if (node == nullptr) {
            return;
        }
        
        inorderHelper(node->left, result);
        result.push_back(node->data);
        inorderHelper(node->right, result);
    }
    
    void destroyHelper(BSTNode* node) {
        if (node == nullptr) {
            return;
        }
        
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }
    
public:
    BST() : root(nullptr) {}
    
    ~BST() {
        destroyHelper(root);
    }
    
    // 插入
    void insert(int val) {
        root = insertHelper(root, val);
    }
    
    // 查找
    bool search(int val) {
        return searchHelper(root, val) != nullptr;
    }
    
    // 删除
    void deleteNode(int val) {
        root = deleteHelper(root, val);
    }
    
    vector<int> getSorted() {
        vector<int> result;
        inorderHelper(root, result);
        return result;
    }
};

bool binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

// 生成测试数据
vector<int> generateTestData1() {
    vector<int> data;
    for (int i = 1; i <= 2048; i += 2) {
        data.push_back(i);
    }
    return data;
}

vector<int> generateTestData2(const vector<int>& sorted_data) {
    vector<int> data = sorted_data;
    random_shuffle(data.begin(), data.end());
    return data;
}

int main() {
    cout << "========== BST查找 vs 折半查找性能比较 ==========" << endl << endl;
    
    // 生成测试数据
    cout << "生成测试数据..." << endl;
    vector<int> testData1 = generateTestData1();
    vector<int> testData2 = generateTestData2(testData1);
    
    cout << "第1组数据：已排序列表，n = " << testData1.size() << endl;
    cout << "第2组数据：随机列表，n = " << testData2.size() << endl << endl;
    
    // 测试数据1：已排序
    cout << "========== 第1组测试数据（已排序）==========" << endl;
    
    // 建立BST
    auto start1 = chrono::high_resolution_clock::now();
    BST bst1;
    for (int val : testData1) {
        bst1.insert(val);
    }
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "BST建立时间: " << duration1 << " μs" << endl;
    
    // BST查找测试
    vector<int> searchTargets1 = {5, 100, 500, 1000, 2047, 2048};
    long long bstSearchTime1 = 0;
    
    for (int target : searchTargets1) {
        auto start = chrono::high_resolution_clock::now();
        bool found = bst1.search(target);
        auto end = chrono::high_resolution_clock::now();
        bstSearchTime1 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    cout << "BST查找6个目标总耗时: " << bstSearchTime1 << " ns" << endl;
    
    // 折半查找测试
    long long binarySearchTime1 = 0;
    
    for (int target : searchTargets1) {
        auto start = chrono::high_resolution_clock::now();
        bool found = binarySearch(testData1, target);
        auto end = chrono::high_resolution_clock::now();
        binarySearchTime1 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    cout << "折半查找6个目标总耗时: " << binarySearchTime1 << " ns" << endl;
    
    auto start_sort1 = chrono::high_resolution_clock::now();
    vector<int> sorted1 = bst1.getSorted();
    auto end_sort1 = chrono::high_resolution_clock::now();
    auto duration_sort1 = chrono::duration_cast<chrono::microseconds>(end_sort1 - start_sort1).count();
    cout << "BST排序耗时: " << duration_sort1 << " μs" << endl << endl;
    
    // 建立BST
    auto start2 = chrono::high_resolution_clock::now();
    BST bst2;
    for (int val : testData2) {
        bst2.insert(val);
    }
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "BST建立时间: " << duration2 << " μs" << endl;
    
    // BST查找测试
    long long bstSearchTime2 = 0;
    
    for (int target : searchTargets1) {
        auto start = chrono::high_resolution_clock::now();
        bool found = bst2.search(target);
        auto end = chrono::high_resolution_clock::now();
        bstSearchTime2 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    cout << "BST查找6个目标总耗时: " << bstSearchTime2 << " ns" << endl;
    
    // 折半查找测试（需要先排序）
    vector<int> testData2Sorted = testData2;
    sort(testData2Sorted.begin(), testData2Sorted.end());
    
    long long binarySearchTime2 = 0;
    
    for (int target : searchTargets1) {
        auto start = chrono::high_resolution_clock::now();
        bool found = binarySearch(testData2Sorted, target);
        auto end = chrono::high_resolution_clock::now();
        binarySearchTime2 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    cout << "折半查找6个目标总耗时: " << binarySearchTime2 << " ns" << endl;
    
    if (bstSearchTime2 > 0) {
        cout << "性能比（折半/BST）: " << fixed << setprecision(2) 
             << (double)binarySearchTime2 / bstSearchTime2 << endl;
    }
    
    // BST排序
    auto start_sort2 = chrono::high_resolution_clock::now();
    vector<int> sorted2 = bst2.getSorted();
    auto end_sort2 = chrono::high_resolution_clock::now();
    auto duration_sort2 = chrono::duration_cast<chrono::microseconds>(end_sort2 - start_sort2).count();
    cout << "BST排序耗时: " << duration_sort2 << " μs" << endl << endl;
    
    // 总结
    cout << "========== 性能分析总结 ==========" << endl;
    cout << "数据组" << setw(15) << "BST建立(μs)" << setw(15) << "BST查找(ns)" 
         << setw(15) << "折半查找(ns)" << setw(15) << "排序(μs)" << endl;
    cout << "第1组(已排序)" << setw(15) << duration1 << setw(15) << bstSearchTime1 
         << setw(15) << binarySearchTime1 << setw(15) << duration_sort1 << endl;
    cout << "第2组(随机)" << setw(15) << duration2 << setw(15) << bstSearchTime2 
         << setw(15) << binarySearchTime2 << setw(15) << duration_sort2 << endl;
    
    cout << "\n结论分析：" << endl;
    cout << "1. BST在随机数据下构建时间较长，在已排序数据下构建时间最长（退化为链表）" << endl;
    cout << "2. 折半查找在有序数据上性能优异，查找复杂度为O(log n)" << endl;
    cout << "3. BST查找在平衡树时性能也为O(log n)，但在退化情况下为O(n)" << endl;
    cout << "4. BST的排序通过中序遍历可直接得到，时间复杂度为O(n)" << endl;
    
    return 0;
}
