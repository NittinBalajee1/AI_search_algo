#include <iostream>
#include <vector>
#include <string>
#include <numeric>

int indexOf(const std::vector<std::string>& arr, const std::string& city) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == city) {
            return i;
        }
    }
    return -1;
}

void dfs(const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph, int current, int end, std::vector<bool>& visited, std::string pathSoFar) {
    visited[current] = true;
    pathSoFar += cities[current];

    if (current == end) {
        std::cout << pathSoFar << std::endl;
    } else {
        for (size_t next = 0; next < cities.size(); ++next) {
            if (!visited[next] && graph[current][next] > 0) {
                dfs(cities, graph, next, end, visited, pathSoFar + "->");
            }
        }
    }
    visited[current] = false;
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

    std::string startCity = "S";
    std::string endCity = "G";

    int startIndex = indexOf(cities, startCity);
    int endIndex = indexOf(cities, endCity);

    std::vector<bool> visited(cities.size(), false);

    if (startIndex != -1 && endIndex != -1) {
        std::cout << "All paths from " << startCity << " to " << endCity << ":" << std::endl;
        dfs(cities, graph, startIndex, endIndex, visited, "");
    } else {
        std::cout << "Start or end city not found." << std::endl;
    }

    return 0;
}