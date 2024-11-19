#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>


void normalBFS(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        std::cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };

    int startNode = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::cout << "Breadth-First Search (BFS) Traversal Order: " << std::endl;
    normalBFS(graph, startNode);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    std::cout << "\nExecution Time: " << std::fixed << std::setprecision(8) 
              << duration.count() << " seconds" << std::endl;

    return 0;
}