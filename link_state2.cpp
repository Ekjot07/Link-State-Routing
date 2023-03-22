#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Node {
public:
    int id;
    unordered_map<Node*, int> neighbors;

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
        node1->neighbors[node2] = cost;
        node2->neighbors[node1] = cost;
    }

    Node* getNode(int id) {
        for (Node* node : nodes) {
            if (node->id == id) {
                return node;
            }
        }
        return nullptr;
    }

    void removeNode(int id) {
        Node* node = getNode(id);
        if (!node) return;

        for (Node* neighbor : node->neighbors) {
            neighbor->neighbors.erase(node);
        }

        nodes.erase(remove(nodes.begin(), nodes.end(), node), nodes.end());
        delete node;
    }

    void removeLink(int id1, int id2) {
        Node* node1 = getNode(id1);
        Node* node2 = getNode(id2);
        if (!node1 || !node2) return;

        node1->neighbors.erase(node2);
        node2->neighbors.erase(node1);
    }

    void printRoutingTable(int id) {
        Node* source = getNode(id);
        if (!source) return;

        // Create a priority queue to store the nodes with their tentative distances
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> pq;

        // Create an array to store the distances of all nodes from the source node
        int dist[nodes.size()];
        for (int i = 0; i < nodes.size(); i++) {
            dist[i] = INT_MAX;
        }
        dist[source->id - 1] = 0;

        // Create an array to store the previous node in the shortest path to each node
        int prev[nodes.size()];
        for (int i = 0; i < nodes.size(); i++) {
            prev[i] = -1;
        }

        // Use Dijkstra's algorithm to find the shortest path to all nodes from the source node
        pq.push(make_pair(0, source));
        while (!pq.empty()) {
            Node* node = pq.top().second;
            pq.pop();

            for (pair<Node*, int> neighbor : node->neighbors) {
                int alt = dist[node->id - 1] + neighbor.second;
                if (alt < dist[neighbor.first->id - 1]) {
                    dist[neighbor.first->id - 1] = alt;
                    prev[neighbor.first->id - 1] = node->id;
                    pq.push(make_pair(alt, neighbor.first));
                }
            }
        }

        // Print the routing table for the source node
        cout << "Routing table for node " << source->id << ":" << endl;
        cout << "Destination\tCost\tNext hop" << endl;
        for (Node* node : nodes) {
            if (node == source) continue;
            if (dist[node->id - 1] == INT_MAX) {
                cout << node->id << "\t\t" << "INF" << "\t\t" << "-" << endl;
            }
            else{
                cout << node->id << "\t\t" << dist[node->id - 1] << "\t\t" << prev[node->id - 1] << endl;
            }
        }
        cout << endl;
    }
};

