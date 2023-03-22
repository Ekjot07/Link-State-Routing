#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int id;
    vector<pair<Node*, int>> neighbors;

    Node(int id) : id(id) {}
};

class Network {
public:
    vector<Node*> nodes;

    void addNode(int id) {
        Node* node = new Node(id);
        nodes.push_back(node);
    }

    void addLink(int id1, int id2, int cost) {
        Node* node1 = getNode(id1);
        Node* node2 = getNode(id2);
        node1->neighbors.push_back(make_pair(node2, cost));
        node2->neighbors.push_back(make_pair(node1, cost));
    }

    Node* getNode(int id) {
        for (Node* node : nodes) {
            if (node->id == id) {
                return node;
            }
        }
        return nullptr;
    }

    void printShortestPath(int src, int dest) {
        // code for Dijkstra's algorithm
        Node* source = getNode(src);
        Node* destination = getNode(dest);

        // Create a priority queue to store the nodes with their tentative distances
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;

        // Set the tentative distance of all nodes to infinity, except for the source node which is 0
        for (Node* node : nodes) {
            node->id == src ? pq.push(make_pair(0, node)) : pq.push(make_pair(INT_MAX, node));
        }

        // Create an array to store the distances of all nodes from the source node
        vector<int> dist;
        for (int i = 0; i < nodes.size(); i++) {
            if(i==src) dist.push_back(0);
            else dist.push_back(INT_MAX);
        }

        // Create an array to store the previous node in the shortest path to each node
        vector<int> prev;
        for (int i = 0; i < nodes.size(); i++) {
            prev.push_back(-1);
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

    void printRoutingTable(int src) {
        cout << "Routing table for node " << src << ":" << endl;
        for (Node* node : nodes) {
            if (node->id != src) {
                printShortestPath(src, node->id);
            }
        }
    }
};
int main(){

    Network network;
    // add nodes
    network.addNode(0);
    network.addNode(1);
    network.addNode(2);
    network.addNode(3);
    network.addNode(4);
    network.addNode(5);

    // add links
    network.addLink(0, 1, 6);
    network.addLink(0, 2, 3);
    network.addLink(1, 2, 2);
    network.addLink(1, 3, 7);
    network.addLink(2, 4, 9);
    network.addLink(3, 4, 1);
    network.addLink(3, 5, 8);
    network.addLink(4, 5, 4);

    // print routing table for each node
    for (Node* node : network.nodes) {
        network.printRoutingTable(node->id);
        cout << endl;
    }

return 0;

}