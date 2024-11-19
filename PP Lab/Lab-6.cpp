#include <iostream>
#include <vector>
#include <queue>
#include "/opt/homebrew/Cellar/libomp/18.1.8/include/omp.h"
#include <chrono>


void parallelBFS(const std::vector<std::vector<int>>& graph, int start) {
    int n = graph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int levelSize = q.size();
        std::vector<int> currentLevel;

        for (int i = 0; i < levelSize; ++i) {
            int node = q.front();
            q.pop();
            currentLevel.push_back(node);
            std::cout << node << " ";

            // Enqueue all unvisited neighbors
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        
        #pragma omp parallel for
        for (int i = 0; i < currentLevel.size(); ++i) {
            int node = currentLevel[i];
            #pragma omp critical
            std::cout << node << std::endl;
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
    parallelBFS(graph, startNode);
    
    // Stop timing
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    // Output execution time
    std::cout << "\nExecution Time: " << duration.count() << " seconds" << std::endl;

    return 0;
}