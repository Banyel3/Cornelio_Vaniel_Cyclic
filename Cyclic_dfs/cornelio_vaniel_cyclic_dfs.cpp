#include <iostream>
#include <vector>
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
}; // predefined adjacency matrix based on last lecture's given graph

const vector<char> vertices = {'A','B','C','D','E','F','G'};

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

bool dfsCycle(int u, int start, vector<bool>& visited, vector<int>& path, vector<int>& cycle) {
    visited[u] = true;
    path.push_back(u);

    for (int v = 0; v < 7; v++) {
        if (graph[u][v]) {
            if (v == start && path.size() >= 2) { // Found cycle back to start
                cycle = path;
                cycle.push_back(start);
                return true;
            }
            if (!visited[v]) {
                if (dfsCycle(v, start, visited, path, cycle))
                    return true;
            }
        }
    }

    path.pop_back();
    return false;
}

vector<int> findCycleDFS() {
    vector<bool> visited(7, false);
    vector<int> path, cycle;

    // Start from A (0)
    if (dfsCycle(0, 0, visited, path, cycle)) {
        return cycle;
    }
    return {};
}

int main() {
    cout << "Directed Graph Cycle Detection (DFS)\n";
    printMatrix();
    cout << "\n";

    vector<int> cycle = findCycleDFS();

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
