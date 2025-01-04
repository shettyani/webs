#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <stack>
#include <algorithm>

using namespace std;

// Define a pair to represent graph edges (neighbor, weight)
typedef pair<int, int> Edge;

// Function to perform Dijkstra's Algorithm
pair<int, vector<int>> dijkstra(const unordered_map<int, vector<Edge>>& graph, int start, int target) {
    // Min-heap priority queue to store (distance, node)
    priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;
    // Distance vector to store the shortest distance to each node
    unordered_map<int, int> distances;
    // Previous nodes for path reconstruction
    unordered_map<int, int> previous;

    // Initialize distances to infinity
    for (auto& node : graph) {
        distances[node.first] = INT_MAX;
    }
    distances[start] = 0;

    // Push the start node into the priority queue
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        // Get the node with the smallest distance
        int currentDistance = minHeap.top().first;
        int currentNode = minHeap.top().second;
        minHeap.pop();

        // Stop if we reach the target node
        if (currentNode == target) break;

        // Explore neighbors
        for (const auto& neighbor : graph.at(currentNode)) {
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            int newDistance = currentDistance + weight;

            // If a shorter path is found
            if (newDistance < distances[nextNode]) {
                distances[nextNode] = newDistance;
                previous[nextNode] = currentNode;
                minHeap.push({newDistance, nextNode});
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current = target;
    while (previous.find(current) != previous.end()) {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return {distances[target], path};
}

int main() {
    // Number of nodes and edges
    int nodes, edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    unordered_map<int, vector<Edge>> graph;

    // Input edges
    cout << "Enter the edges (format: node1 node2 weight):\n";
    for (int i = 0; i < edges; i++) {
        int node1, node2, weight;
        cin >> node1 >> node2 >> weight;

        // Add edge to the graph
        graph[node1].emplace_back(node2, weight);
        graph[node2].emplace_back(node1, weight); // For undirected graph
    }

    // Input start and target nodes
    int start, target;
    cout << "Enter the start node (ambulance location): ";
    cin >> start;
    cout << "Enter the target node (hospital location): ";
    cin >> target;

    // Call Dijkstra's algorithm
    auto result = dijkstra(graph, start, target);

    // Output the result
    if (result.first == INT_MAX) {
        cout << "No path exists between node " << start << " and node " << target << "." << endl;
    } else {
        cout << "Shortest distance: " << result.first << endl;
        cout << "Path: ";
        for (int node : result.second) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
