#include <iostream>
using namespace std;

struct Edge {
    int src;
    int dest;
    int weight;
};

int parent[20], nodes, links;
Edge edges[50], mst[20];

int findParent(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int a = findParent(i);
    int b = findParent(j);
    parent[a] = b;
}

void createGraph() {
    cout << "\nEnter number of vertices: ";
    cin >> nodes;
    cout << "Enter number of edges: ";
    cin >> links;

    for (int i = 1; i <= links; i++) {
        cout << "\nEnter details for Edge " << i << ":\n";
        cout << "Source: ";
        cin >> edges[i].src;
        cout << "Destination: ";
        cin >> edges[i].dest;
        cout << "Weight: ";
        cin >> edges[i].weight;
    }
}

void sortEdges() {
    for (int i = 1; i <= links; i++) {
        for (int j = i + 1; j <= links; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

void kruskalMST() {
    int edgeCount = 0, minCost = 0, i = 1;

    for (int k = 1; k <= nodes; k++)
        parent[k] = k;

    sortEdges();

    while (edgeCount < nodes - 1 && i <= links) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int setU = findParent(u);
        int setV = findParent(v);

        if (setU != setV) {
            mst[edgeCount++] = edges[i];
            minCost += edges[i].weight;
            unionSets(setU, setV);
        }
        i++;
    }

    cout << "\nEdges in the Minimum Spanning Tree:\n";
    for (int k = 0; k < edgeCount; k++)
        cout << mst[k].src << " --> " << mst[k].dest << "  (Weight: " << mst[k].weight << ")\n";

    cout << "Total Minimum Cost: " << minCost << endl;
}

void displayAdjList() {
    cout << "\nAdjacency List Representation:\n";
    for (int i = 1; i <= links; i++) {
        cout << edges[i].src << " -> " << edges[i].dest << " (" << edges[i].weight << ")\n";
        cout << edges[i].dest << " -> " << edges[i].src << " (" << edges[i].weight << ")\n";
    }
}

int main() {
    int choice;

    createGraph();

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Display Adjacency List\n";
        cout << "2. Find MST using Kruskals Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAdjList();
                break;
            case 2:
                kruskalMST();
                break;
            case 3:
                cout << "Exiting\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 3);

    return 0;
}
