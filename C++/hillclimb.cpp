#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

std::vector<std::string> cities = {"S", "A", "B", "C", "D", "E", "G"};
std::vector<std::vector<int>> graph = {
    {0, 3, 5, 0, 0, 0, 0},
    {3, 0, 4, 0, 5, 0, 0},
    {5, 4, 0, 4, 0, 0, 0},
    {0, 0, 4, 0, 0, 6, 0},
    {0, 5, 0, 0, 0, 0, 3},
    {0, 0, 0, 6, 0, 0, 0},
    {0, 0, 0, 0, 3, 0, 0}
};
std::vector<int> heuristics = {0, 7, 6, 7, 3, 4, 0};

int indexOf(const std::vector<std::string>& arr, const std::string& city) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == city) {
            return i;
        }
    }
    return -1;
}

std::vector<std::string> hillclimbWithHistory(const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph, const std::vector<int>& heuristics, const std::string& startCit, const std::string& endCit) {
    int startin = indexOf(cities, startCit);
    int endin = indexOf(cities, endCit);

    std::vector<std::string> path;
    std::vector<bool> visited(cities.size(), false);

    int current = startin;
    path.push_back(cities[current]);
    visited[current] = true;

    while (current != endin) {
        int nextCity = -1;
        int bestHeuristic = std::numeric_limits<int>::max();

        for (size_t i = 0; i < cities.size(); ++i) {
            if (!visited[i] && graph[current][i] > 0) {
                if (nextCity == -1 || heuristics[i] < bestHeuristic ||
                    (heuristics[i] == bestHeuristic && cities[i] < cities[nextCity])) {
                    bestHeuristic = heuristics[i];
                    nextCity = i;
                }
            }
        }

        if (nextCity == -1) {
            return {};
        }

        current = nextCity;
        path.push_back(cities[current]);
        visited[current] = true;
    }
    return path;
}

int main() {
    std::vector<std::string> path = hillclimbWithHistory(cities, graph, heuristics, "S", "G");
    
    if (!path.empty()) {
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i < path.size() - 1) {
                std::cout << "->";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}