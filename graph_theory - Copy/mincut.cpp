#include <bits/stdc++.h>
#include <fstream>
#include "./json-develop/single_include/nlohmann/json.hpp" // Include the JSON library

using json = nlohmann::json;
using namespace std;

class graph {
public:
    int node;
    int edges;
    unordered_map<int, list<pair<int, int>>> adj;

    void addEdge(int u, int v, int d) {
        adj[u].push_back(make_pair(v, d));
        adj[v].push_back(make_pair(u, d)); // If undirected
    }

    void printAdjList() {
        for (auto k : adj) {
            cout << k.first << "->";
            for (auto m : k.second) {
                cout << "[" << m.first << "," << m.second << "], ";
            }
            cout << endl;
        }
    }
};

void findAllPathsDFS(int current, int destination, unordered_map<int, list<pair<int, int>>>& adj, vector<bool>& visited, vector<int>& path, vector<vector<int>>& allPaths) {
    visited[current] = true;
    path.push_back(current);

    if (current == destination) {
        allPaths.push_back(path);
    } else {
        for (auto neighbor : adj[current]) {
            if (!visited[neighbor.first]) {
                findAllPathsDFS(neighbor.first, destination, adj, visited, path, allPaths);
            }
        }
    }

    path.pop_back();
    visited[current] = false;
}

vector<pair<int, int>> findMinCutEdges(const vector<vector<int>>& allPaths) {
    unordered_map<pair<int, int>, int, hash<pair<int, int>>> edgeCount;
    
    // Count the occurrence of each edge in all paths
    for (const auto& path : allPaths) {
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            edgeCount[{u, v}]++;
            edgeCount[{v, u}]++; // For undirected graph
        }
    }

    // Identify edges that are present in all paths
    vector<pair<int, int>> mincut_edges;
    for (const auto& [edge, count] : edgeCount) {
        if (count == allPaths.size()) { // Appears in every path
            mincut_edges.push_back(edge);
        }
    }

    return mincut_edges;
}

int main() {
    graph g;
    int n;
    cout << "Enter number of nodes: " << endl;
    cin >> n;
    g.node = n;

    cout << "Enter number of edges: " << endl;
    cin >> n;
    g.edges = n;
    int u, v, d;
    cout << "Enter the adjacency list (u v d):" << endl;
    for (int i = 0; i < g.edges; i++) {
        cin >> u >> v >> d;
        g.addEdge(u, v, d);
    }
    cout << "Adjacency List:" << endl;
    g.printAdjList();

    int source, desti;
    cout << "Enter the source node: " << endl;
    cin >> source;
    cout << "Enter the destination node: " << endl;
    cin >> desti;

    vector<vector<int>> allPaths;
    vector<int> path;
    vector<bool> visited(g.node, false);

    // Find all paths using DFS
    findAllPathsDFS(source, desti, g.adj, visited, path, allPaths);

    // Print all paths found
    cout << "All Paths from " << source << " to " << desti << ":" << endl;
    for (const auto& p : allPaths) {
        for (int node : p) {
            cout << node << " ";
        }
        cout << endl;
    }

    // Find min cut edges
    vector<pair<int, int>> mincut_edges = findMinCutEdges(allPaths);

    // Print min cut edges
    cout << "Min Cut Edges:" << endl;
    for (const auto& edge : mincut_edges) {
        cout << edge.first << " - " << edge.second << endl;
    }

    // Save the paths and min cut edges to a JSON file
    json output;
    output["paths"] = allPaths;
    for (const auto& edge : mincut_edges) {
        output["mincut_edges"].push_back({edge.first, edge.second});
    }

    ofstream file("path_data.json");
    file << output.dump(4); // Pretty-print JSON with an indentation of 4 spaces
    file.close();

    cout << "Paths and min cut edges saved to path_data.json" << endl;

    // Execute the Python visualization script
    system("python visualize_graph.py");

    return 0;
}
