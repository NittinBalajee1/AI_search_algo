#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <algorithm>

int indexOf(const std::vector<std::string>& arr, const std::string& city) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == city) {
            return i;
        }
    }
    return -1;
}

void printPath(const std::vector<int>& path, const std::vector<std::string>& cities) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << cities[path[i]];
        if (i < path.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << std::endl;
}

void bfs(const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph, int startIn, int endIn) {
    std::queue<std::vector<int>> queue;
    std::vector<int> startPath;
    startPath.push_back(startIn);
    queue.push(startPath);

    while (!queue.empty()) {
        std::vector<int> path = queue.front();
        queue.pop();

        int lastNode = path.back();

        if (lastNode == endIn) {
            printPath(path, cities);
        } else {
            for (size_t next = 0; next < cities.size(); ++next) {
                if (graph[lastNode][next] > 0 &&
                    std::find(path.begin(), path.end(), next) == path.end()) {
                    
                    std::vector<int> newPath = path;
                    newPath.push_back(next);
                    queue.push(newPath);
                }
            }
        }
    }
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

    std::string startCit = "S";
    std::string endCit = "G";

    int startIn = indexOf(cities, startCit);
    int endIn = indexOf(cities, endCit);

    if (startIn != -1 && endIn != -1) {
        std::cout << "All paths from " << startCit << " to " << endCit << ":" << std::endl;
        bfs(cities, graph, startIn, endIn);
    } else {
        std::cout << "Start or end city not found." << std::endl;
    }

    return 0;
}