#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <functional>
#include <numeric> // For iota

using namespace std;

// Prim's Algorithm
pair<vector<tuple<int, int, int>>, int> primMST(vector<vector<pair<int, int>>> &graph, int startNode) {
    int totalCost = 0;
    vector<tuple<int, int, int>> mst;
    vector<bool> visited(graph.size(), false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap;

    // Add starting node to the heap
    minHeap.push({0, startNode, -1}); // {cost, currentNode, previousNode}

    while (!minHeap.empty()) {
        auto [cost, currentNode, previousNode] = minHeap.top();
        minHeap.pop();

        if (visited[currentNode]) continue;

        visited[currentNode] = true;
        totalCost += cost;

        if (previousNode != -1) {
            mst.push_back({previousNode, currentNode, cost});
        }

        for (auto &[neighbor, edgeCost] : graph[currentNode]) {
            if (!visited[neighbor]) {
                minHeap.push({edgeCost, neighbor, currentNode});
            }
        }
    }

    return {mst, totalCost};
}

// Kruskal's Algorithm
pair<vector<tuple<int, int, int>>, int> kruskalMST(vector<tuple<int, int, int>> &edges, int numNodes) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });

    vector<int> parent(numNodes), rank(numNodes, 0);
    iota(parent.begin(), parent.end(), 0); // Initialize parent with node indices

    // Find function with path compression
    function<int(int)> find = [&](int node) -> int {
        if (parent[node] != node) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    };

    // Merge (union) function
    auto merge = [&](int node1, int node2) {
        int root1 = find(node1);
        int root2 = find(node2);
        if (root1 != root2) {
            if (rank[root1] > rank[root2]) {
                parent[root2] = root1;
            } else if (rank[root1] < rank[root2]) {
                parent[root1] = root2;
            } else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    };

    vector<tuple<int, int, int>> mst;
    int totalCost = 0;

    for (auto &[u, v, cost] : edges) {
        if (find(u) != find(v)) {
            merge(u, v);
            mst.push_back({u, v, cost});
            totalCost += cost;
        }
    }

    return {mst, totalCost};
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<pair<int, int>>> graph(numNodes);
    vector<tuple<int, int, int>> edges;

    cout << "Enter the edges (u v cost):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v, cost;
        cin >> u >> v >> cost;
        edges.push_back({u, v, cost});
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost});
    }

    // Run Prim's Algorithm
    auto [primMSTResult, primCost] = primMST(graph, 0);
    cout << "Prim's MST:" << endl;
    for (auto &[u, v, cost] : primMSTResult) {
        cout << u << " -> " << v << " : " << cost << endl;
    }
    cout << "Total Cost (Prim): " << primCost << endl;

    // Run Kruskal's Algorithm
    auto [kruskalMSTResult, kruskalCost] = kruskalMST(edges, numNodes);
    cout << "\nKruskal's MST:" << endl;
    for (auto &[u, v, cost] : kruskalMSTResult) {
        cout << u << " -> " << v << " : " << cost << endl;
    }
    cout << "Total Cost (Kruskal): " << kruskalCost << endl;

    return 0;
}
