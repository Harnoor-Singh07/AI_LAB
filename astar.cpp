#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <limits>
#include <algorithm>

using namespace std;

const int NODES = 10; 
const int INF = numeric_limits<int>::max();

map<char, int> hValue = { {'A', 15}, {'B', 13}, {'C', 13}, {'D', 12}, {'E', 10}, 
                          {'F', 9}, {'G', 7}, {'H', 6}, {'I', 5}, {'J', 0} };

int graph[NODES][NODES] = {
    {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
    {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
    {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
    {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
    {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
    {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
    {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
    {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
    {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
    {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}
};

int getIndex(char c) {
    return c - 'A';
}

void printPath(vector<int>& parent, int node) {
    if (parent[node] == -1) {
        cout << (char)('A' + node) << " ";  
        return;
    }
    printPath(parent, parent[node]);  
    cout << (char)('A' + node) << " ";  
}

void DFS(int start) {
    vector<bool> visited(NODES, false);
    stack<int> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            cout << (char)('A' + node) << " ";
            visited[node] = true;
        }

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                s.push(i);
            }
        }
    }
    cout << endl;
}

void BFS(int start) {
    vector<bool> visited(NODES, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << (char)('A' + node) << " ";

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void BestFirstSearch(int start) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    cout << "Best First Search Traversal: ";
    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        if (!visited[node]) {
            cout << (char)('A' + node) << " ";
            visited[node] = true;
        }

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                pq.push({graph[node][i], i});
            }
        }
    }
    cout << endl;
}

bool DLS(int node, int target, int depth, vector<bool> &visited, vector<int> &path) {
    if (depth == 0 && node == target) {
        path.push_back(node);  // Store the node instead of printing
        return true;
    }

    if (depth > 0) {
        visited[node] = true;
        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                if (DLS(i, target, depth - 1, visited, path)) {
                    path.push_back(node);  // Store the node instead of printing
                    return true;
                }
            }
        }
    }
    return false;
}

void IDDFS(int start, int target) {
    cout << "IDDFS Traversal: ";
    for (int depth = 0; depth < NODES; depth++) {
        vector<bool> visited(NODES, false);
        vector<int> path;  // To store the correct traversal path
        if (DLS(start, target, depth, visited, path)) {
            reverse(path.begin(), path.end());  // Reverse the path to print from A to target
            for (int node : path) {
                cout << (char)('A' + node) << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "Target not reachable" << endl;
}

void BeamSearch(int start, int width) {
    vector<bool> visited(NODES, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    visited[start] = true;

    cout << "Beam Search Traversal: ";
    while (!pq.empty()) {
        vector<pair<int, int>> level;
        for (int i = 0; i < width && !pq.empty(); i++) {
            level.push_back(pq.top());
            pq.pop();
        }

        for (auto &p : level) {
            int node = p.second;
            cout << (char)('A' + node) << " ";
            for (int i = 0; i < NODES; i++) {
                if (graph[node][i] != 0 && !visited[i]) {
                    pq.push({graph[node][i], i});
                    visited[i] = true;
                }
            }
        }
    }
    cout << endl;
}

void AStarSearch(int start, int target) {
    vector<int> g(NODES, INF);
    vector<int> parent(NODES, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    g[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int node = pq.top().second;
        pq.pop();

        if (node == target) {
            cout << "A* Path: ";
            printPath(parent, target);
            cout << endl;
            return;
        }

        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0) {
                int gCost = g[node] + graph[node][i];
                int fCost = gCost + hValue[(char)('A' + i)];
                if (gCost < g[i]) {
                    g[i] = gCost;
                    pq.push({fCost, i});
                    parent[i] = node;
                }
            }
        }
    }
    cout << "No path found" << endl;
}

int main() {
    char startNode = 'A';
    char targetNode = 'J';
    int choice;

    do {
        cout << "\n--- Graph Traversal Menu ---\n";
        cout << "1. Depth First Search without cost\n";
        cout << "2. Breadth First Search without cost\n";
        cout << "3. Best First Search considering only g value\n";
        cout << "4. Iterative Deepening best node first\n";
        cout << "5. Beam Search (Width=2) best node\n";
        cout << "6. A* Search\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                DFS(getIndex(startNode));
                break;
            case 2:
                BFS(getIndex(startNode));
                break;
            case 3:
                BestFirstSearch(getIndex(startNode));
                break;
            case 4:
                IDDFS(getIndex(startNode), getIndex(targetNode));
                break;
            case 5:
                BeamSearch(getIndex(startNode), 2);
                break;
            case 6:
                AStarSearch(getIndex(startNode), getIndex(targetNode));
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
