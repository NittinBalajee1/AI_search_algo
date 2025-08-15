#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

struct Path {
    std::vector<int> nodes;
    int heuristic_cost;
    int total_cost;

    bool operator>(const Path& other) const {
        return heuristic_cost > other.heuristic_cost;
    }
};

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

int getCityIndex(const std::string& city) {
    for (int i = 0; i < cities.size(); ++i) {
        if (cities[i] == city) return i;
    }
    return -1;
}

void printPath(const std::vector<int>& path, int cost) {
    for (int i = 0; i < path.size(); ++i) {
        std::cout << cities[path[i]];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << " | Distance: " << cost << std::endl;
}

void beamSearch(const std::string& start, const std::string& goal, int beamWidth) {
    int startIndex = getCityIndex(start);
    int goalIndex = getCityIndex(goal);

    if (startIndex == -1 || goalIndex == -1) {
        std::cout << "Invalid start or goal city." << std::endl;
        return;
    }

    std::priority_queue<Path, std::vector<Path>, std::greater<Path>> pq;

    Path initialPath;
    initialPath.nodes.push_back(startIndex);
    initialPath.heuristic_cost = heuristics[startIndex];
    initialPath.total_cost = 0;
    pq.push(initialPath);

    while (!pq.empty()) {
        std::vector<Path> nextLevelPaths;

        while (!pq.empty()) {
            Path currentPath = pq.top();
            pq.pop();

            int lastNode = currentPath.nodes.back();

            if (lastNode == goalIndex) {
                printPath(currentPath.nodes, currentPath.total_cost);
                return;
            }

            for (int i = 0; i < graph.size(); ++i) {
                if (graph[lastNode][i] > 0 &&
                    std::find(currentPath.nodes.begin(), currentPath.nodes.end(), i) == currentPath.nodes.end()) {

                    Path newPath = currentPath;
                    newPath.nodes.push_back(i);
                    newPath.heuristic_cost = heuristics[i];
                    newPath.total_cost += graph[lastNode][i];
                    nextLevelPaths.push_back(newPath);
                }
            }
        }

        std::sort(nextLevelPaths.begin(), nextLevelPaths.end(), [](const Path& a, const Path& b) {
            return a.heuristic_cost < b.heuristic_cost;
        });

        for (int i = 0; i < std::min((int)nextLevelPaths.size(), beamWidth); ++i) {
            pq.push(nextLevelPaths[i]);
        }

        if (pq.empty() && startIndex != goalIndex) {
             std::cout << "No path found within the given beam width!" << std::endl;
             return;
        }
    }

    std::cout << "No path found!" << std::endl;
}

int main() {
    beamSearch("S", "G", 2);
    return 0;
}