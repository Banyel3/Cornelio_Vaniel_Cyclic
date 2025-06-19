#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// BFS implementation with proper cycle tracking
bool isCyclicBFS(const vector<vector<int>>& adjMatrix, int start, vector<int>& cycle) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (adjMatrix[current][neighbor] != 0) {  // Edge exists
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
                else if (parent[current] != neighbor) {
                    // Found a cycle, reconstruct the cycle path
                    vector<int> tempCycle;
                    tempCycle.push_back(neighbor);

                    int node = current;
                    while (node != neighbor && node != -1) {
                        tempCycle.push_back(node);
                        node = parent[node];
                    }

                    // Make sure we have a proper cycle (at least 3 distinct nodes)
                    if (tempCycle.size() >= 3) {
                        cycle = tempCycle;
                        reverse(cycle.begin(), cycle.end());
                        cycle.push_back(cycle[0]); // Complete the cycle
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void printMatrix(const vector<vector<int>>& matrix, bool weighted) {
    cout << "\nAdjacency Matrix:\n";
    cout << "   ";
    for (int i = 0; i < matrix.size(); ++i) cout << i << " ";
    cout << "\n";

    for (int i = 0; i < matrix.size(); ++i) {
        cout << i << ": ";
        for (int val : matrix[i]) {
            if (weighted) cout << val << " ";
            else cout << (val != 0 ? "1 " : "0 ");
        }
        cout << "\n";
    }
}

int getIntegerInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                break;
            }
            cout << "Error: Value must be between " << minVal << " and " << maxVal << "\n";
        } else {
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return value;
}

int main() {
    cout << "Graph Cycle Detection (BFS)\n";
    cout << "==========================\n\n";

    // Ask if graph is weighted
    int weightedChoice = getIntegerInput("Is the graph weighted? (1 for Yes, 0 for No): ", 0, 1);
    bool weighted = (weightedChoice == 1);

    int n = getIntegerInput("\nEnter number of vertices (2-100): ", 2, 100);

    // Initialize adjacency matrix
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    // Input adjacency matrix
    cout << "\nEnter adjacency matrix:\n";
    if (weighted) {
        cout << "Enter 0 for no edge, or the weight for existing edges\n";
    } else {
        cout << "Enter 0 for no edge, 1 for existing edge\n";
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string prompt = "Edge " + to_string(i) + " → " + to_string(j) + ": ";
            adjMatrix[i][j] = getIntegerInput(prompt, 0, weighted ? 1000 : 1);
        }
    }

    printMatrix(adjMatrix, weighted);

    // BFS cycle detection
    bool hasCycle = false;
    vector<int> cycle;

    for (int i = 0; i < n; ++i) {
        if (isCyclicBFS(adjMatrix, i, cycle)) {
            hasCycle = true;
            break;
        }
    }

    // Output results
    cout << "\nAll vertices: ";
    for (int i = 0; i < n; ++i) cout << i << " ";
    cout << "\n";

    if (hasCycle) {
        cout << "\nCycle detected using BFS!\n";
        cout << "Vertices forming the cycle: ";
        for (size_t i = 0; i < cycle.size(); ++i) {
            cout << cycle[i];
            if (i != cycle.size() - 1) cout << " → ";
        }
        cout << "\n";

        if (weighted) {
            int totalWeight = 0;
            for (size_t i = 0; i < cycle.size() - 1; ++i) {
                totalWeight += adjMatrix[cycle[i]][cycle[i+1]];
            }
            cout << "Total weight of the cycle: " << totalWeight << "\n";
        }
    }
    else {
        cout << "\nNo cycles found in the graph using BFS.\n";
    }

    return 0;
}
