#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

struct edge{
    int To;
    int weight;
};

edge init(int t,int w){
    edge newedge;
    newedge.To = t;
    newedge.weight = w;
    return newedge;
}

void printgraph(const vector<vector<edge>> & graph,const vector<string> node){
    int n = graph.size();
    cout << "graph" << endl;
    for(int i = 0;i < n;i++){
        cout << node[i] << "->";
        for(int j = 0;j < graph[i].size();j++){
            cout << node[graph[i][j].To] << '(' << graph[i][j].weight << ')'; 
        }
        cout << endl;
    }
}

void dijkstra(const vector<vector<edge>> & graph,int start,vector<int> & dist,vector<int> & pre){
    int n = graph.size();
    vector<bool> visit(n,false);
    dist.assign(n,INT_MAX);
    pre.assign(n,-1);
    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visit[j] && (u == -1 || dist[j] < dist[u])) {
            u = j;
            }
        }
        if (dist[u] == INT_MAX) break;
        visit[u] = true;
    

        for (const edge & e : graph[u]) {
            int v = e.To;
            int newDist = dist[u] + e.weight;

            if(newDist < dist[v]){
                dist[v] = newDist;
                pre[v] = u;
            }
        }
    }
}
vector<int> get_path(vector<int> & pre,int target){
    vector<int> path;

    for(int i = target;i != -1;i = pre[i]){
        path.push_back(i);
    }

    reverse(path.begin(),path.end());
    return path;
}

void print_dijkstra_result(const vector<int> & dist,vector<int> & pre,const vector<string> & node,int start){
    for(int i = 0;i < dist.size();i++){

        if(dist[i] == INT_MAX){
            cout << node[i] << "false" << endl;
        }

        else{
            cout << node[i] << " " <<"distance:" << " " << dist[i] << " ";
            vector<int> path = get_path(pre,i);
            
            for(int j = 0;j < path.size();j++){
                cout << node[path[j]];
                if(j < path.size() - 1){cout << "->";}
            }

            cout << endl;
        }
    }
}

void floyd(const vector<vector<edge>> & graph,vector<vector<int>> & dist,vector<vector<int>> & next){
    int n = graph.size();
    dist.assign(n,vector<int>(n,INT_MAX));
    for(int i = 0;i < n;i++){dist[i][i] = 0;}
    next.assign(n,vector<int>(n,-1));

    for(int i = 0;i < n;i++){
        for(const edge & e : graph[i]){
            int j = e.To;
            dist[i][j] = e.weight;
        }
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            next[i][j] = j;
        }
    }

    for(int k = 0;k < n;k++){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX){
                    if(dist[i][j] > dist[i][k] + dist[k][j]){
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }

}

vector<int> get_floyd_path(const vector<vector<int>> & next,int start,int end){
    vector<int> path;
    if(next[start][end] == -1){
        return path;
    }
    else{
        path.push_back(start); 
        int current = start;
        while(current != end){
            current = next[current][end];
            path.push_back(current);
        }
        return path;
    }
}

void print_floyd_result(const vector<vector<int>> & dist,const vector<vector<int>> & next,const vector<string> & node){
    for(int i = 0;i < dist.size();i++){
        cout << node[i];
        for(int j = 0;j < dist.size();j++){
            if(dist[i][j] == INT_MAX){
                cout << "flase ";
            }
            else{
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0;i < dist.size();i++){
        for(int j = 0;j < dist.size();j++){
            if(i != j && dist[i][j] != INT_MAX){
                vector<int> path = get_floyd_path(next,i,j);
                cout << node[i] << "->" << node[j] << " distance: " << dist[i][j] << " path: ";
                for(int k = 0;k < path.size();k++){
                    cout << node[path[k]];
                    if(k < path.size() - 1){
                        cout << "->";
                    }
                }
                cout << endl;
            }
        }
    }
}

int main(){
    vector<string> node = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    vector<vector<edge>> graph(10);
    vector<int> dist_dijkstra;
    vector<int> pre_dijkstra;
    vector<vector<int>> dist_floyd;
    vector<vector<int>> next_floyd;
    int start = 0;

    graph[0].push_back(init(1, 4));  // A->B
    graph[0].push_back(init(2, 2));  // A->C
    graph[1].push_back(init(0, 4));  // B->A  
    graph[1].push_back(init(2, 1));  // B->C
    graph[1].push_back(init(3, 5));  // B->D
    graph[2].push_back(init(3, 8));  // C->D
    graph[2].push_back(init(4, 10)); // C->E
    graph[3].push_back(init(4, 2));  // D->E
    graph[3].push_back(init(5, 6));  // D->F
    graph[4].push_back(init(5, 3));  // E->F
    graph[4].push_back(init(6, 5));  // E->G
    graph[5].push_back(init(6, 1));  // F->G
    graph[5].push_back(init(7, 7));  // F->H
    graph[6].push_back(init(7, 4));  // G->H

    dijkstra(graph, start, dist_dijkstra, pre_dijkstra);
    print_dijkstra_result(dist_dijkstra, pre_dijkstra, node, start);
    
    //floyd(graph,dist_floyd,next_floyd);
    //print_floyd_result(dist_floyd,next_floyd,node);
    return 0;
}