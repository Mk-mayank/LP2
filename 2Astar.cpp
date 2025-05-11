#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class aStar {
    vector<int> dx = {-1, 1, 0, 0, -1, -1, 1, 1};
    vector<int> dy = {0, 0, -1, 1, -1, 1, -1, 1};
    map<pair<int, int>, bool> visited;
    map<pair<int, int>, int> gScore;
    map<pair<int, int>, pair<int, int>> parent;
    vector<vector<int>> matrix;

public:
    aStar(int n) {
        vector<int> temp(n, 0);
        for (int i = 0; i < n; i++) {
            matrix.push_back(temp);
        }
    }

    void makeWall(int i, int j) {
        matrix[i][j] = -1;
    }

    bool isvalid(pair<int, int> p) {
        int r = p.first;
        int c = p.second;
        if (r < 0 || r >= matrix.size() || c < 0 || c >= matrix.size() || matrix[r][c] == -1)
            return false;
        return true;
    }

    int heuristic(pair<int, int> p) {
        int goalX = matrix.size() - 1;
        int goalY = matrix.size() - 1;
        return abs(goalX - p.first) + abs(goalY - p.second);
    }

    void PrintPath() {
        vector<pair<int, int>> path;
        pair<int, int> curr = {matrix.size() - 1, matrix.size() - 1};
        while (curr.first != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (auto node : path) {
            cout << "{" << node.first << "," << node.second << "} ==> ";
        }
        cout << "END\n";
    }

    void Solve() {
        int goalX = matrix.size() - 1;
        int goalY = matrix.size() - 1;
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

        pq.push({heuristic({0, 0}), {0, 0}});
        parent[{0, 0}] = {-1, -1};
        gScore[{0, 0}] = 0;

        while (!pq.empty()) {
            int f = pq.top().first;
            pair<int, int> curr = pq.top().second;
            pq.pop();
            visited[curr] = true;

            if (curr.first == goalX && curr.second == goalY) {
                PrintPath();
                return;
            }

            for (int i = 0; i < 8; i++) {
                pair<int, int> ngb = {curr.first + dx[i], curr.second + dy[i]};
                if (!isvalid(ngb)) continue;

                int newGscore = gScore[curr] + 1;
                if (visited.count(ngb)) {
                    if (gScore[ngb] > newGscore)
                        visited.erase(ngb);
                    else
                        continue;
                }

                gScore[ngb] = newGscore;
                pq.push({heuristic(ngb) + newGscore, ngb});
                parent[ngb] = curr;
            }
        }
    }
};

int main() {
    aStar obj(5);
    obj.makeWall(1, 2);
    obj.makeWall(2, 2);
    obj.Solve();
    return 0;
}
