#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>
#include <algorithm>

int indexOf(const std::vector<std::string>& arr, const std::string& city) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == city) {
            return i;
        }
    }
    return -1;
}

void printPath(const std::vector<std::string>& cities, const std::vector<int>& parent, int start, int end, const std::vector<std::vector<int>>& graph) {
    std::vector<int> path;
    for (int at = end; at != -1; at = parent[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    int distance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        distance += graph[path[i]][path[i + 1]];
    }

    std::cout << "Shortest path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << cities[path[i]];
        if (i < path.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << " | distance = " << distance << std::endl;
}

void bfs(const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph, int start, int end) {
    std::queue<int> queue;
    std::vector<bool> visited(cities.size(), false);
    std::vector<int> parent(cities.size(), -1);

    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        if (current == end) {
            printPath(cities, parent, start, end, graph);
            return;
        }

        for (size_t next = 0; next < cities.size(); ++next) {
            if (graph[current][next] > 0 && !visited[next]) {
                visited[next] = true;
                parent[next] = current;
                queue.push(next);
            }
        }
    }
    std::cout << "No path found." << std::endl;
}

int main() {
    std::vector<std::string> cities = {"S", "A", "B", "C", "D", "E", "G"};
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    std::string startcit = "S";
    std::string endcit = "G";

    int startin = indexOf(cities, startcit);
    int endin = indexOf(cities, endcit);

    if (startin != -1 && endin != -1) {
        bfs(cities, graph, startin, endin);
    } else {
        std::cout << "Start or end city not found." << std::endl;
    }

    return 0;
}