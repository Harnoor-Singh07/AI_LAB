#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

using namespace std;

vector<int> bfs(const vector<vector<int>>& adjMatrix, int start) {
    vector<int> visited;
    queue<int> q;
    unordered_set<int> visited_set;

    q.push(start);
    visited_set.insert(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        visited.push_back(node);

        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[node][i] == 1 && visited_set.find(i) == visited_set.end()) {
                q.push(i);
                visited_set.insert(i);
            }
        }
    }

    return visited;
}

vector<int> dfs(const vector<vector<int>>& adjMatrix, int start) {
    vector<int> visited;
    stack<int> s;
    unordered_set<int> visited_set;

    s.push(start);
    visited_set.insert(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        visited.push_back(node);

        for (int i = 0; i < adjMatrix.size(); ++i) {
            if (adjMatrix[node][i] == 1 && visited_set.find(i) == visited_set.end()) {
                s.push(i);
                visited_set.insert(i);
            }
        }
    }

    return visited;
}

int main() {
    int V; 
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> adjMatrix(V, vector<int>(V, 0));

    int E; 
    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges (format: u v for an edge between vertices u and v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; 
    }

    int start_node;
    cout << "Enter the starting node (0-" << V-1 << "): ";
    cin >> start_node;

    string option;
    cout << "Enter 'BFS' for Breadth-First Search or 'DFS' for Depth-First Search: ";
    cin >> option;

    vector<int> result;
    if (option == "BFS") {
        result = bfs(adjMatrix, start_node);
        cout << "BFS Traversal Order: ";
    } else if (option == "DFS") {
        result = dfs(adjMatrix, start_node);
        cout << "DFS Traversal Order: ";
    } else {
        cout << "Invalid option. Please enter 'BFS' or 'DFS'." << endl;
        return 1;
    }

    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
