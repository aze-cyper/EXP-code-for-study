#include<iostream>
#include<vector>
#include<stack>
#include<queue>
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

int vertexnum_list = 0;
bool direct_list = false;//默认无向图


struct node{
    int vertex;
    int weight;
    node * next;    
};

node * list[max_vertex];

node * init_node(int v,int w){
    node * newnode = new node;
    newnode -> vertex = v;
    newnode -> weight = w;
    newnode -> next = nullptr;
    return newnode;
}

void init_list(int n,bool direct){
    vertexnum_list = n;
    direct_list = direct;

    for(int i = 0;i < n;i++){
        list[i] = nullptr;
    }
}

void add_edge_to_list(int from,int to,int weight){
    if(from > vertexnum_list || to > vertexnum_list || from < 0 || to < 0){
        cout << "add failed";
    }
    else{
        node * newnode =init_node(to,weight);
        newnode -> next = list[from];
        list[from] = newnode;
        if(!direct_list && from != to){
            node * reverse_node = init_node(from,weight);
            reverse_node -> next = list[to];
            list[to] = reverse_node;
        } 
    }
}

void print_list(){
    for(int i = 0;i <vertexnum_list;i++){
        cout << i << ":";
        node * current = list[i];
        while(current != nullptr){
            cout << "-> [" << current->vertex << "](w:" << current->weight << ") ";
            current = current -> next;
        }
        cout << "->nullptr" << endl;
    }
}

void matrix_to_list(){
    init_list(vertexnum,direct);

    for(int i = 0;i < vertexnum;i++){
        for(int j = 0;j < vertexnum;j++){
            if(matrix[i][j] != 0){
                add_edge_to_list(i,j,matrix[i][j]);
            }
        }
    }

}

void list_to_matrix(){
    init_matrix(vertexnum_list,direct_list);

    for(int i = 0;i < vertexnum_list;i++){
        node * current = list[i];

        while(list[i] != nullptr){
            add_edge_to_matrix(i,current -> vertex,current -> weight);
            current = current -> next;
        }

    }

}


bool visited[max_vertex];                    
vector<int> dfs_order;                       
vector<int> bfs_order;                       
vector<pair<int, int>> dfs_tree_edges;       
vector<pair<int, int>> bfs_tree_edges;       
int dfn[max_vertex];                         
int bfn[max_vertex];                         
int dfn_count = 0;                           
int bfn_count = 0;                           

void init_visited() {
    for(int i = 0; i < max_vertex; i++) {
        visited[i] = false;
    }
    dfs_order.clear();
    bfs_order.clear();
    dfs_tree_edges.clear();
    bfs_tree_edges.clear();
    dfn_count = 0;
    bfn_count = 0;
}

void dfs_matrix_recursive(int v, int parent = -1) {
    visited[v] = true;
    dfs_order.push_back(v);
    dfn[v] = dfn_count++; 
    
    if(parent != -1) {
        dfs_tree_edges.push_back({parent, v});
    }
    

    for(int i = 0; i < vertexnum; i++) {
        if(matrix[v][i] != 0 && !visited[i]) {
            dfs_matrix_recursive(i, v);
        }
    }
}


void dfs_matrix_non_recursive(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;
    dfn[start] = dfn_count++;
    dfs_order.push_back(start);
    
    while(!st.empty()) {
        int v = st.top();
        bool found = false;
        
        for(int i = 0; i < vertexnum; i++) {
            if(matrix[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                st.push(i);
                dfs_order.push_back(i);
                dfn[i] = dfn_count++;
                dfs_tree_edges.push_back({v, i});
                found = true;
                break;
            }
        }
        
        if(!found) {
            st.pop();
        }
    }
}

void bfs_matrix(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    bfn[start] = bfn_count++;
    bfs_order.push_back(start);
    
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        
        for(int i = 0; i < vertexnum; i++) {
            if(matrix[v][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
                bfs_order.push_back(i);
                bfn[i] = bfn_count++;
                bfs_tree_edges.push_back({v, i});
            }
        }
    }
}

void dfs_list_recursive(int v, int parent = -1) {
    visited[v] = true;
    dfs_order.push_back(v);
    dfn[v] = dfn_count++;
    
    if(parent != -1) {
        dfs_tree_edges.push_back({parent, v});
    }
    
    node* current = list[v];
    while(current != nullptr) {
        if(!visited[current->vertex]) {
            dfs_list_recursive(current->vertex, v);
        }
        current = current->next;
    }
}

void dfs_list_non_recursive(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;
    dfn[start] = dfn_count++;
    dfs_order.push_back(start);
    
    while(!st.empty()) {
        int v = st.top();
        bool found = false;
        
        node* current = list[v];
        while(current != nullptr) {
            if(!visited[current->vertex]) {
                visited[current->vertex] = true;
                st.push(current->vertex);
                dfs_order.push_back(current->vertex);
                dfn[current->vertex] = dfn_count++;
                dfs_tree_edges.push_back({v, current->vertex});
                found = true;
                break;
            }
            current = current->next;
        }
        
        if(!found) {
            st.pop();
        }
    }
}

void bfs_list(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    bfn[start] = bfn_count++;
    bfs_order.push_back(start);
    
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        
        node* current = list[v];
        while(current != nullptr) {
            if(!visited[current->vertex]) {
                visited[current->vertex] = true;
                q.push(current->vertex);
                bfs_order.push_back(current->vertex);
                bfn[current->vertex] = bfn_count++;
                bfs_tree_edges.push_back({v, current->vertex});
            }
            current = current->next;
        }
    }
}

//无向图
void calculate_degree(){
    int degrees[vertexnum_list] = {0};

    for(int i = 0;i < vertexnum_list;i++){
        int degree = 0;
        node * current = list[i];
        while(current != nullptr){
            degree += 1;
            current = current -> next;
        }
        degrees[i] = degree;
        cout << i << "的度为" << degree << endl;
    }
}

int main(){
    init_list(10,true);
    add_edge_to_list(1,2,8);
    print_list();
}