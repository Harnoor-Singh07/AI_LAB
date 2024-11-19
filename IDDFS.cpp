#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(const vector<vector<int>>& graph, int node, int depth, unordered_set<int>& visited) {
    if (depth == 0) {
        return;
    }
    visited.insert(node);
    cout << node << " ";
    for (int neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs(graph, neighbor, depth - 1, visited);
        }
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    vector<vector<int>> graph(numNodes);

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (node1 node2):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Assuming the graph is undirected
    }

    int starting_node;
    cout << "Enter the starting node: ";
    cin >> starting_node;

    // Iteratively call DFS for depths 1 to 3
    for (int depth = 1; depth <= 3; ++depth) {
        cout << "\nDFS with depth " << depth << ":\n";
        unordered_set<int> visited;
        dfs(graph, starting_node, depth, visited);
        cout << endl;
    }

    return 0;
}