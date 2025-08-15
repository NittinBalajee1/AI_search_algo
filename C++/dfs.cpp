#include <iostream>
#include <vector>
#include <string>
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

void printPath(const std::vector<std::string>& path, int distance) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << " | distance = " << distance << std::endl;
}

int calcDis(const std::vector<std::string>& path, const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph) {
    int total = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int from = indexOf(cities, path[i]);
        int to = indexOf(cities, path[i + 1]);
        if (from != -1 && to != -1) {
            total += graph[from][to];
        }
    }
    return total;
}

void dfs(const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph, int current, int end, std::vector<bool>& visited, std::vector<std::string>& path) {
    visited[current] = true;
    path.push_back(cities[current]);

    if (current == end) {
        int distance = calcDis(path, cities, graph);
        printPath(path, distance);
    } else {
        for (size_t next = 0; next < cities.size(); ++next) {
            if (!visited[next] && graph[current][next] > 0) {
                dfs(cities, graph, next, end, visited, path);
            }
        }
    }

    visited[current] = false;
    path.pop_back();
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
        std::vector<bool> visited(cities.size(), false);
        std::vector<std::string> path;

        std::cout << "All paths from " << startcit << " to " << endcit << ":" << std::endl;
        dfs(cities, graph, startin, endin, visited, path);
    } else {
        std::cout << "Start or end city not found." << std::endl;
    }

    return 0;
}