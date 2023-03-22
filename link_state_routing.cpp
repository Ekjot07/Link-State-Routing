#include <bits/stdc++.h>
// #include <vector>
// #include <queue>
// #include <climits>
using namespace std;

// Class to represent a node in the network
class Node {
public:
    int id;             // ID of the node
    vector<pair<Node*, int>> neighbors;    // List of neighbors and their link costs

    Node(int id) : id(id) {}
};

// Class to represent the network
class Network {
public:
    vector<Node*> nodes;    // List of nodes in the network

    // Method to add a new node to the network
    void addNode(int id) {
        Node* node = new Node(id);
        nodes.push_back(node);
    }

    // Method to add a link between two nodes
    void addLink(int id1, int id2, int cost) {
        Node* node1 = getNode(id1);
        Node* node2 = getNode(id2);
        node1->neighbors.push_back(make_pair(node2, cost));
        node2->neighbors.push_back(make_pair(node1, cost));
    }

    // Method to get a node by its ID
    Node* getNode(int id) {
        for (Node* node : nodes) {
            if (node->id == id) {
                return node;
            }
        }
        return nullptr;
    }

    // Method to print the shortest path from source to destination
    void printShortestPath(int src, int dest) {
        Node* source = getNode(src);
        Node* destination = getNode(dest);

        // Create a priority queue to store the nodes with their tentative distances
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;

        // Set the tentative distance of all nodes to infinity, except for the source node which is 0
        for (Node* node : nodes) {
            node->id == src ? pq.push(make_pair(0, node)) : pq.push(make_pair(INT_MAX, node));
        }

        // Create an array to store the distances of all nodes from the source node
        int dist[nodes.size()];
        for (int i = 0; i < nodes.size(); i++) {
            dist[i] = INT_MAX;
        }
        dist[src] = 0;

        // Create an array to store the previous node in the shortest path to each node
        int prev[nodes.size()];
        for (int i = 0; i < nodes.size(); i++) {
            prev[i] = -1;
        }

        // Use Dijkstra's algorithm to find the shortest path
        while (!pq.empty()) {
            Node* node = pq.top().second;
            pq.pop();

            for (pair<Node*, int> neighbor : node->neighbors) {
                int alt = dist[node->id] + neighbor.second;
                if (alt < dist[neighbor.first->id]) {
                    dist[neighbor.first->id] = alt;
                    prev[neighbor.first->id] = node->id;
                    pq.push(make_pair(alt, neighbor.first));
                }
            }
        }

        // Print the shortest path
        cout << "Shortest path from node " << src << " to node " << dest << ":" << endl;
        if (dist[dest] == INT_MAX) {
            cout << "No path found" << endl;
        }
        else {
            vector<int> path;
            int node = dest;
            while (node != src) {
                path.push_back(node);
                node = prev[node];
            }
            path.push_back(src);

            // Reverse the path to print it from source to destination
            reverse(path.begin(), path.end());

            // Print the path
            for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
            cout << " -> ";
            }
            }
            cout << endl;
        }
    }
};
int main() {
    Network network;

    // Add nodes to the network
    network.addNode(1);
    network.addNode(2);
    network.addNode(3);
    network.addNode(4);
    network.addNode(5);

    // Add links between nodes
    network.addLink(1, 2, 1);
    network.addLink(1, 3, 4);
    network.addLink(2, 3, 2);
    network.addLink(2, 4, 5);
    network.addLink(3, 4, 1);
    network.addLink(3, 5, 3);
    network.addLink(4, 5, 2);

    // Find the shortest path from node 1 to node 5
    network.printShortestPath(1, 5);

    return 0;
}
