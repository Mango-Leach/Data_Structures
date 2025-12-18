#include <iostream>
using namespace std;

#define MAX 20
#define INF 9999

struct Node {
    int vertex;
    int weight;
    Node* next;
};

Node* adjList[MAX];
int visited[MAX], distanceArr[MAX];
int vertices, edges;

void createGraph() {
    int i, src, dest, wt;
    cout << "\nEnter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edges;

    for (i = 1; i <= vertices; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
        distanceArr[i] = INF;
    }

    cout << "\nEnter edges (src dest weight):\n";
    for (i = 1; i <= edges; i++) {
        cout << "Edge " << i << ": ";
        cin >> src >> dest >> wt;

        Node* newNode = new Node;
        newNode->vertex = dest;
        newNode->weight = wt;
        newNode->next = adjList[src];
        adjList[src] = newNode;

        newNode = new Node;
        newNode->vertex = src;
        newNode->weight = wt;
        newNode->next = adjList[dest];
        adjList[dest] = newNode;
    }
}

void displayAdjList() {
    cout << "\nAdjacency List Representation:\n";
    for (int i = 1; i <= vertices; i++) {
        cout << "Vertex " << i << ": ";
        Node* temp = adjList[i];
        while (temp != NULL) {
            cout << temp->vertex << "(" << temp->weight << ") -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int findMinVertex() {
    int min = INF, index = -1;
    for (int i = 1; i <= vertices; i++) {
        if (!visited[i] && distanceArr[i] < min) {
            min = distanceArr[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start) {
    distanceArr[start] = 0;

    for (int i = 1; i <= vertices; i++) {
        int u = findMinVertex();
        if (u == -1) break;

        visited[u] = 1;

        Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (!visited[v] && distanceArr[u] + w < distanceArr[v])
                distanceArr[v] = distanceArr[u] + w;

            temp = temp->next;
        }
    }
}

int main() {
    createGraph();
    displayAdjList();

    int start, end;
    cout << "\nEnter source vertex: ";
    cin >> start;
    cout << "Enter destination vertex: ";
    cin >> end;

    dijkstra(start);

    cout << "\nShortest distances from vertex " << start << ":\n";
    for (int i = 1; i <= vertices; i++)
        cout << "To " << i << " = " << distanceArr[i] << endl;

    cout << "\nShortest distance from " << start << " to " << end << " = " << distanceArr[end] << endl;

    return 0;
}
