#include <bits/stdc++.h>
using namespace std;

class Greedy {
    int v;
    map<int, vector<pair<int, int>>> adjlist;

public:
    Greedy(int vertices) {
        v = vertices;
    }

    void addedge(int u, int v, int w) {
        adjlist[u].push_back({v, w});
    }

    void diskstra(int src) {
        vector<int> dist(v, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto p : adjlist[node]) {
                int ngb = p.first;
                int wt = p.second;
                if (dist[ngb] > dist[node] + wt) {
                    dist[ngb] = dist[node] + wt;
                    pq.push({dist[ngb], ngb});
                }
            }
        }

        cout << "\nShortest distances from node " << src << ":\n";
        for (int i = 0; i < v; ++i) {
            cout << "To node " << i << " = ";
            if (dist[i] == INT_MAX)
                cout << "INF" << endl;
            else
                cout << dist[i] << endl;
        }
    }
};

class Job {
public:
    char id;
    int profit;
    int deadline;

    Job(char id, int deadline, int profit) {
        this->id = id;
        this->deadline = deadline;
        this->profit = profit;
    }
};

void JobScheduler(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
        return a.profit > b.profit;
    });

    int maxdeadline = 0;
    for (auto p : jobs) {
        maxdeadline = max(maxdeadline, p.deadline);
    }

    vector<char> schedule(maxdeadline, '-');
    int totalProfit = 0;

    for (auto j : jobs) {
        for (int d = j.deadline - 1; d >= 0; d--) {
            if (schedule[d] == '-') {
                schedule[d] = j.id;
                totalProfit += j.profit;
                break;
            }
        }
    }

    cout << "\nScheduled Jobs: ";
    for (char jobId : schedule) {
        if (jobId != '-')
            cout << jobId << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    // Dijkstra's Algorithm Input
    int vertices, edges;
    cout << "Enter number of vertices and edges for Dijkstra's algorithm: ";
    cin >> vertices >> edges;

    Greedy g(vertices);
    cout << "Enter edges in format (u v weight):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addedge(u, v, w);
    }

    int src;
    cout << "Enter source vertex for Dijkstra's algorithm: ";
    cin >> src;
    g.diskstra(src);

    // Job Scheduling Input
    int n;
    cout << "\nEnter number of jobs: ";
    cin >> n;

    vector<Job> jobs;
    cout << "Enter jobs in format (id deadline profit):\n";
    for (int i = 0; i < n; ++i) {
        char id;
        int deadline, profit;
        cin >> id >> deadline >> profit;
        jobs.emplace_back(id, deadline, profit);
    }

    JobScheduler(jobs);

    return 0;
}
