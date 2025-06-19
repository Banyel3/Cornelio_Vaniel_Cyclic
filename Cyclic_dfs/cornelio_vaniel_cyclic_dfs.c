#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// DFS implementation with proper cycle tracking
bool isCyclicDFS(const vector<vector<int>>& adjMatrix, vector<bool>& visited,
                int current, int parent, vector<int>& path, vector<int>& cycle) {
    visited[current] = true;
    path.push_back(current);

    for (int neighbor = 0; neighbor < adjMatrix.size(); ++neighbor) {
        if (adjMatrix[current][neighbor] != 0) {  // Edge exists
            if (!visited[neighbor]) {
                if (isCyclicDFS(adjMatrix, visited, neighbor, current, path, cycle)) {
                    return true;
                }
            }
            else if (neighbor != parent) {
                // Found a back edge, cycle detected
                auto it = find(path.begin(), path.end(), neighbor);
                if (it != path.end()) {
                    cycle.assign(it, path.end());
                    cycle.push_back(neighbor); // Complete the cycle
                    return true;
                }
            }
        }
    }

    path.pop_back();
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
    cout << "Graph Cycle Detection (DFS)\n";
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

    // DFS cycle detection
    bool hasCycle = false;
    vector<int> cycle;
    vector<bool> visited(n, false);
    vector<int> path;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (isCyclicDFS(adjMatrix, visited, i, -1, path, cycle)) {
                hasCycle = true;
                break;
            }
        }
    }

    // Output results
    cout << "\nAll vertices: ";
    for (int i = 0; i < n; ++i) cout << i << " ";
    cout << "\n";

    if (hasCycle) {
        cout << "\nCycle detected using DFS!\n";
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
        cout << "\nNo cycles found in the graph using DFS.\n";
    }

    return 0;
}
