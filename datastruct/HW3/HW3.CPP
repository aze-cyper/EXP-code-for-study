#include<iostream>
using namespace std;

#define max_vertex 20
int matrix[max_vertex][max_vertex];
int vertexnum = 0;
bool direct = false;

//dir = true 有向图
void init_matrix(int n,bool dir){
    vertexnum = n;
    direct = dir;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            matrix[i][j] = 0;
        }
    }
}

void add_edge_to_matrix(int from,int to,int weight = 1){
    if(from < 0 || from > vertexnum || to < 0 || to > vertexnum){
        cout << "超出范围" << endl;
    }
    else{
        matrix[from][to] = weight; 
        if(!direct && from != to){
            matrix[to][from] = weight;
        }
    }
}

void print_matrix(){
    cout << "  ";
    for(int i = 0;i < vertexnum;i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0;i < vertexnum;i++){
        cout << i << " ";
        for(int j = 0;j < vertexnum;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

struct node{
    int vertex;
    int weight;
    node * next;
};

node init_node(int v,int w){
    node newnode;
    newnode.vertex = v;
    newnode.weight = w;
    newnode.next = nullptr;
}

int main(){
    init_matrix(10,true);
    add_edge_to_matrix(1,2,8);
    print_matrix();
}