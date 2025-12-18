#include <iostream>
#include <queue>
using namespace std;

#define MAX 20

int adj[MAX][MAX];
bool visited[MAX];
int v, e;

void createGraph() {
    int src, dest;
    cout << "\nEnter graph details:\n";
    cout << "Number of vertices: ";
    cin >> v;
    cout << "Number of edges: ";
    cin >> e;

    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            adj[i][j] = 0;

    cout << "\nEnter edges (src dest):\n";
    for (int i = 1; i <= e; i++) {
        cout << "Edge " << i << ": ";
        cin >> src >> dest;
        adj[src][dest] = 1;
        adj[dest][src] = 1;
    }
}

void displayMatrix() {
    cout << "\nAdjacency Matrix:\n ";
    for (int i = 1; i <= v; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 1; i <= v; i++) {
        cout << i << " ";
        for (int j = 1; j <= v; j++)
            cout << adj[i][j] << " ";
        cout << endl;
    }
}

void BFS(int start) {
    queue<int> q;
    for (int i = 1; i <= v; i++)
        visited[i] = false;

    visited[start] = true;
    q.push(start);

    cout << "\nBFS Traversal: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int i = 1; i <= v; i++) {
            if (adj[node][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

void DFSUtil(int node) {
    visited[node] = true;
    cout << node << " ";
    for (int i = 1; i <= v; i++) {
        if (adj[node][i] && !visited[i])
            DFSUtil(i);
    }
}

void DFS(int start) {
    for (int i = 1; i <= v; i++)
        visited[i] = false;

    cout << "\nDFS Traversal: ";
    DFSUtil(start);
    cout << endl;
}

int main() {
    int choice, start;
    createGraph();

    do {
        cout << "\n=== Graph Traversal Menu ===\n";
        cout << "1. Display Adjacency Matrix\n";
        cout << "2. BFS Traversal\n";
        cout << "3. DFS Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMatrix();
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
