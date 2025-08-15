#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <numeric>

const std::vector<std::string> cities = {"S", "A", "B", "C", "D", "E", "G"};
const std::vector<std::vector<int>> graph = {
    {0, 3, 5, 0, 0, 0, 0},
    {3, 0, 4, 0, 5, 0, 0},
    {5, 4, 0, 4, 0, 0, 0},
    {0, 0, 4, 0, 0, 6, 0},
    {0, 5, 0, 0, 0, 0, 3},
    {0, 0, 0, 6, 0, 0, 0},
    {0, 0, 0, 0, 3, 0, 0}
};

int selectMinCostNode(const std::vector<int>& cost, const std::vector<bool>& visited) {
    int min = std::numeric_limits<int>::max();
    int minIndex = -1;

    for (size_t i = 0; i < cost.size(); ++i) {
        if (!visited[i] && cost[i] < min) {
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void printRecursivePath(const std::vector<int>& parent, int start, int node) {
    if (node == -1) return;
    if (node != start) {
        printRecursivePath(parent, start, parent[node]);
    }
    std::cout << cities[node];
    if (node != start) {
        std::cout << " -> ";
    }
}

void printPath(const std::vector<int>& parent, int start, int goal) {
    if (parent[goal] == -1 && goal != start) {
        std::cout << "No path found." << std::endl;
        return;
    }
    std::cout << "Path: ";
    std::vector<int> path;
    int current = goal;
    while(current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    std::reverse(path.begin(), path.end());
    for(size_t i = 0; i < path.size(); ++i) {
        std::cout << cities[path[i]];
        if(i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}


void costBasedOracleSearch(int start, int goal) {
    size_t n = graph.size();
    std::vector<bool> visited(n, false);
    std::vector<int> cost(n, std::numeric_limits<int>::max());
    std::vector<int> parent(n, -1);

    cost[start] = 0;

    for (size_t count = 0; count < n - 1; ++count) {
        int u = selectMinCostNode(cost, visited);
        if (u == -1) break;
        visited[u] = true;

        if (u == goal) break;

        for (size_t v = 0; v < n; ++v) {
            if (graph[u][v] > 0 && !visited[v]) {
                int newCost = cost[u] + graph[u][v];
                if (newCost < cost[v]) {
                    cost[v] = newCost;
                    parent[v] = u;
                }
            }
        }
    }
    
    std::cout << "Path: ";
    std::vector<std::string> finalPath;
    int current = goal;
    while(current != -1) {
        finalPath.push_back(cities[current]);
        current = parent[current];
    }
    std::reverse(finalPath.begin(), finalPath.end());
    
    if (finalPath.front() == cities[start]) {
        for(size_t i = 0; i < finalPath.size(); ++i) {
            std::cout << finalPath[i];
            if(i < finalPath.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    std::cout << "Total Cost: " << (cost[goal] == std::numeric_limits<int>::max() ? -1 : cost[goal]) << std::endl;
}


int main() {
    costBasedOracleSearch(0, 6);
    return 0;
}