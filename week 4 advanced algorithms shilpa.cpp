#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
using namespace std;

// Structure to represent graph edges
struct Edge {
    int dest;
    int weight;
};

// Function to reverse the path
vector<int> reverse(const vector<int>& arr) {
    vector<int> rev;
    for (int i = arr.size() - 1; i >= 0; i--) {
        rev.push_back(arr[i]);
    }
    return rev;
}

class Graph {
private:
    int V; // Number of vertices
    vector<vector<Edge>> adj; // Adjacency list

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(vertices);
    }

    // Add edge to graph
    void addEdge(int src, int dest, int weight) {
        Edge edge;
        edge.dest = dest;
        edge.weight = weight;
        adj[src].push_back(edge);
    }

    // Dijkstra's algorithm implementation
    pair<int, vector<int>> shortestPath(int start, int end) {
        // Priority queue to store {distance, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance vector
        vector<int> dist(V, numeric_limits<int>::max());
        
        // Parent vector to store the path
        vector<int> parent(V, -1);
        
        // Distance to start vertex is 0
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Check all adjacent vertices
            for (const Edge& edge : adj[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Construct path
        vector<int> path;
        if (dist[end] != numeric_limits<int>::max()) {
            for (int v = end; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            path = reverse(path);  // Reverse to get correct order
        }

        return {dist[end], path};
    }
};

int main() {
    // Create a sample graph
    Graph g(6);  // Graph with 6 vertices (0 to 5)

    // Add edges (hardcoded example)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    int start, end;
    cout << "Enter start node (0-5): ";
    cin >> start;
    cout << "Enter end node (0-5): ";
    cin >> end;

    // Validate input
    if (start < 0 || start > 5 || end < 0 || end > 5) {
        cout << "Invalid input! Nodes must be between 0 and 5." << endl;
        return 1;
    }

    // Find shortest path
    auto result = g.shortestPath(start, end);
    int shortestDist = result.first;
    vector<int> path = result.second;

    // Print results
    if (shortestDist == numeric_limits<int>::max()) {
        cout << "No path exists between nodes " << start << " and " << end << endl;
    } else {
        cout << "Shortest distance: " << shortestDist << endl;
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}