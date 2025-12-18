#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int vertex;
    Node* next;
};

Node* adjList[20];
bool visited[20];
int v, e;

void createGraph() {
    cout << "\nEnter number of vertices: ";
    cin >> v;
    cout << "Enter number of edges: ";
    cin >> e;

    for (int i = 1; i <= v; i++)
        adjList[i] = NULL;

    cout << "\nEnter edges (src dest):\n";
    for (int i = 1; i <= e; i++) {
        int src, dest;
        cout << "Edge " << i << ": ";
        cin >> src >> dest;

        Node* newNode = new Node{dest, adjList[src]};
        adjList[src] = newNode;

        newNode = new Node{src, adjList[dest]};
        adjList[dest] = newNode;
    }
}

void displayAdjList() {
    cout << "\nAdjacency List Representation:\n";
    for (int i = 1; i <= v; i++) {
        cout << "Vertex " << i << ": ";
        Node* temp = adjList[i];
        while (temp != NULL) {
            cout << temp->vertex << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

void BFS(int start) {
    queue<int> q;
    for (int i = 1; i <= v; i++)
        visited[i] = false;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << current << " ";

        Node* temp = adjList[current];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = true;
                q.push(temp->vertex);
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

void DFSUtil(int vertex) {
    visited[vertex] = true;
    cout << vertex << " ";

    Node* temp = adjList[vertex];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            DFSUtil(temp->vertex);
        temp = temp->next;
    }
}

void DFS(int start) {
    for (int i = 1; i <= v; i++)
        visited[i] = false;

    cout << "DFS Traversal: ";
    DFSUtil(start);
    cout << endl;
}

int main() {
    int choice, start;

    createGraph();

    do {
        cout << "\n=== Graph Traversal Menu ===\n";
        cout << "1. Display Adjacency List\n";
        cout << "2. BFS Traversal\n";
        cout << "3. DFS Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAdjList();
                break;

            case 2:
                cout << "Enter starting vertex: ";
                cin >> start;
                BFS(start);
                break;

            case 3:
                cout << "Enter starting vertex: ";
                cin >> start;
                DFS(start);
                break;

            case 4:
                cout << "Exiting\n";
                break;

            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}
