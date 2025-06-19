#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const vector<vector<int>> graph = {
    {0,0,1,0,0,0,0}, // A→C
    {0,0,0,0,0,0,0}, // B
    {0,1,0,0,1,1,1}, // C→B,E,F,G
    {1,0,0,0,0,0,0}, // D→A
    {1,0,0,0,0,0,0}, // E→A
    {0,1,0,0,0,0,0}, // F→B
    {0,0,0,0,0,0,0}  // G
};
const vector<char> vertices = {'A','B','C','D','E','F','G'};

vector<int> findCycleBFS(int start) {
    vector<int> parent(7, -1);
    vector<bool> visited(7, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < 7; v++) {
            if (graph[u][v]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
                else if (v == start && parent[u] != start) {
                    // Reconstruct cycle
                    vector<int> cycle;
                    int node = u;
                    while (node != -1) {
                        cycle.push_back(node);
                        node = parent[node];
                    }
                    reverse(cycle.begin(), cycle.end());
                    cycle.push_back(start); // Complete cycle
                    return cycle;
                }
            }
        }
    }
    return {};
}

void printMatrix() {
    cout << "Adjacency Matrix:\n";
    cout << "  ";
    for (char v : vertices) cout << v << " ";
    cout << "\n";

    for (int i = 0; i < 7; i++) {
        cout << vertices[i] << " ";
        for (int val : graph[i]) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "Directed Graph Cycle Detection\n";
    printMatrix();
    cout << "\n";

    // Find cycle starting from A (0)
    vector<int> cycle = findCycleBFS(0);

    if (!cycle.empty()) {
        cout << "Cycle found: ";
        for (int i = 0; i < cycle.size(); i++) {
            cout << vertices[cycle[i]];
            if (i < cycle.size() - 1) cout << " - ";
        }
        cout << endl;
    } else {
        cout << "No cycle found\n";
    }

    return 0;
}
