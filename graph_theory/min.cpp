#include <bits/stdc++.h>
#include <fstream>
#include "./json-develop/single_include/nlohmann/json.hpp" // Include the JSON library

using json = nlohmann::json;
using namespace std;

class Graph {
public:
    int node;
    vector<vector<int>> capacity; // Matrix for capacities
    vector<vector<int>> adj; // Adjacency list for storing edges

    Graph(int n) : node(n), capacity(n, vector<int>(n, 0)), adj(n) {}

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // Add reverse edge for residual graph
    }

    void printAdjList() {
        for (int i = 0; i < node; i++) {
            cout << i << " -> ";
            for (int j : adj[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

// BFS function to find path with positive capacity
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

// Function to find the minimum cut using the Ford-Fulkerson method
vector<pair<int, int>> minCut(Graph& g, int s, int t) {
    int V = g.node;
    vector<vector<int>> rGraph = g.capacity;
    vector<int> parent(V);
    vector<pair<int, int>> mincut_edges;

    // Augment flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }

    // Find reachable vertices using DFS
    vector<bool> visited(V, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : g.adj[u]) {
            if (rGraph[u][v] > 0 && !visited[v]) {
                dfs(v);
            }
        }
    };

    dfs(s);

    // Identify min-cut edges and store them
    for (int u = 0; u < V; u++) {
        for (int v : g.adj[u]) {
            if (visited[u] && !visited[v] && g.capacity[u][v] > 0) {
                mincut_edges.push_back({u, v});
            }
        }
    }

    // Save min cut edges to a JSON file
    json output;
    for (const auto& edge : mincut_edges) {
        output["mincut_edges"].push_back({edge.first, edge.second});
    }

    ofstream file("path_data.json");
    file << output.dump(4);
    file.close();
    cout << "Min cut edges saved to path_data.json" << endl;

    return mincut_edges;
}

int main() {
    int n, e;
    cout << "Enter number of nodes: "<< endl;
    cin >> n;
    Graph g(n);

    cout << "Enter number of edges: "<< endl;
    cin >> e;
    
    int u, v, cap;
    cout << "Enter the edges (u v capacity):" << endl;
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> cap;
        g.addEdge(u, v, cap);
    }

    int source, dest;
    cout << "Enter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> dest;

    g.printAdjList();
    vector<pair<int, int>> mincut_edges = minCut(g, source, dest);

    // Print the min-cut edges
    cout << "Min Cut Edges:" << endl;
    for (const auto& edge : mincut_edges) {
        cout << edge.first << " - " << edge.second << endl;
    }

    // Execute the Python visualization script
    system("python visualize_min.py");

    return 0;
}
