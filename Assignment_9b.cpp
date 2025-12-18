#include <iostream>
using namespace std;

struct EdgeNode {
    int dest;
    int cost;
    EdgeNode* link;
};

EdgeNode* graph[20];
int mark[20], lowCost[20], parentNode[20];
int nodes, links;

void buildGraph() {
    int i, u, v, w;

    cout << "\nEnter total vertices: ";
    cin >> nodes;
    cout << "Enter total edges: ";
    cin >> links;

    for (i = 1; i <= nodes; i++) {
        graph[i] = NULL;
        mark[i] = 0;
        parentNode[i] = 0;
        lowCost[i] = 9999; // Large value
    }

    cout << "\nEnter edges as (Vertex1 Vertex2 Weight):\n";
    for (i = 1; i <= links; i++) {
        cout << "Edge " << i << ": ";
        cin >> u >> v >> w;

        EdgeNode* temp = new EdgeNode;
        temp->dest = v;
        temp->cost = w;
        temp->link = graph[u];
        graph[u] = temp;

        temp = new EdgeNode;
        temp->dest = u;
        temp->cost = w;
        temp->link = graph[v];
        graph[v] = temp;
    }
}

void showGraph() {
    cout << "\nAdjacency List Representation:\n";
    for (int i = 1; i <= nodes; i++) {
        cout << "Vertex " << i << " -> ";
        EdgeNode* temp = graph[i];
        while (temp != NULL) {
            cout << temp->dest << "(" << temp->cost << ") -> ";
            temp = temp->link;
        }
        cout << "NULL\n";
    }
}

void findMST_Prim() {
    int current = 1, visitedCount = 1, totalWeight = 0;
    EdgeNode* temp;

    lowCost[current] = 0;
    mark[current] = 1;

    while (visitedCount < nodes) {
        temp = graph[current];
        while (temp != NULL) {
            if (!mark[temp->dest] && lowCost[temp->dest] > temp->cost) {
                lowCost[temp->dest] = temp->cost;
                parentNode[temp->dest] = current;
            }
            temp = temp->link;
        }

        int nextVertex = -1, minEdge = 9999;
        for (int i = 1; i <= nodes; i++) {
            if (!mark[i] && lowCost[i] < minEdge) {
                minEdge = lowCost[i];
                nextVertex = i;
            }
        }

        mark[nextVertex] = 1;
        current = nextVertex;
        visitedCount++;
    }

    for (int i = 1; i <= nodes; i++)
        totalWeight += lowCost[i];

    cout << "\nMinimum Spanning Tree (Prim’s Algorithm):\n";
    for (int i = 2; i <= nodes; i++)
        cout << parentNode[i] << " --> " << i << "  (Weight: " << lowCost[i] << ")\n";

    cout << "Total Minimum Cost: " << totalWeight << endl;
}

int main() {
    int option;

    buildGraph();

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Display Graph (Adjacency List)\n";
        cout << "2. Find MST using Prims Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> option;

        switch (option) {
            case 1:
                showGraph();
                break;
            case 2:
                findMST_Prim();
                break;
            case 3:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (option != 3);

    return 0;
}
