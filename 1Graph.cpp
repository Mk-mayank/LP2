#include <bits/stdc++.h>
using namespace std;

class graph {
    map<int, vector<int>> adjlist;

public:
    void addedge(int u, int v) {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    void displayAdjList() {
        for (auto p : adjlist) {
            cout << "Edge: " << p.first << " --> ";
            for (auto x : p.second) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    void dfs(int src, vector<bool>& visited) {
        visited[src] = true;
        cout << src << " ";

        for (auto ngb : adjlist[src]) {
            if (!visited[ngb]) {
                dfs(ngb, visited);
            }
        }
    }

    void bfs(int src, vector<bool>& visited2) {
        queue<int> q;
        q.push(src);
        q.push(-1);
        visited2[src] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == -1) {
                cout << endl;
                if (!q.empty()) q.push(-1);
                continue;
            }

            cout << node << " ";
            for (auto p : adjlist[node]) {
                if (!visited2[p]) {
                    q.push(p);
                    visited2[p] = true;
                }
            }
        }
    }
};

int main() {
    graph g;
    int n ;
    cout<<"Number of vertices :";
    cin >> n;


    g.addedge(0, 1);
    g.addedge(0, 2);
    g.addedge(1, 3);
    g.addedge(2, 3);
    g.addedge(3, 4);

    cout << "Adjacency List:" << endl;
    g.displayAdjList();

    vector<bool> visited(n, false);
    cout << "\nDFS starting from node 0: ";

    for(int i = 0 ; i < n ; i++){
        if(!visited[i])g.dfs(i, visited);
    }
    
    vector<bool> visited2(n, false);
    cout << "\n\nBFS starting from node 0:\n";
    
    for(int i = 0 ; i < n ; i++){
        if(!visited2[i])g.bfs(i, visited2);

    }


    return 0;
}
