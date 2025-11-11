#include<iostream>
#include"HW3.cpp"
using namespace std;
void test_conversion() {
    
    vertexnum = 4;
    direct = false;
    init_matrix(vertexnum, direct);
    
    add_edge_to_matrix(0, 1, 2);
    add_edge_to_matrix(0, 2, 3);
    add_edge_to_matrix(1, 3, 1);
    add_edge_to_matrix(2, 3, 4);
    
    cout << "原始邻接矩阵：" << endl;
    print_matrix();
    
    matrix_to_list();
    cout << "转换后的邻接表：" << endl;
    print_list();
    
    list_to_matrix();
    cout << "转换回的邻接矩阵：" << endl;
    print_matrix();
}
int main(){
    test_conversion();
}