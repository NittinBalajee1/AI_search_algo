#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

struct Path {
    std::vector<int> nodes;
    int heuristic_cost;
    int total_cost;
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

void printPath(const std::vector<int>& path, int cost) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << cities[path[i]];
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << " | Distance: " << cost << std::endl;
}

void beamSearch(int start, int goal, int beamWidth) {
    std::vector<Path> beam;
    
    Path initialPath;
    initialPath.nodes.push_back(start);
    initialPath.heuristic_cost = heuristics[start];
    initialPath.total_cost = 0;
    beam.push_back(initialPath);

    while (!beam.empty()) {
        std::vector<Path> nextLevelCandidates;

        for (const auto& currentPath : beam) {
            int lastNode = currentPath.nodes.back();

            if (lastNode == goal) {
                printPath(currentPath.nodes, currentPath.total_cost);
                return;
            }

            for (size_t i = 0; i < graph[lastNode].size(); ++i) {
                if (graph[lastNode][i] > 0 &&
                    std::find(currentPath.nodes.begin(), currentPath.nodes.end(), i) == currentPath.nodes.end()) {

                    Path newPath = currentPath;
                    newPath.nodes.push_back(i);
                    newPath.heuristic_cost = heuristics[i];
                    newPath.total_cost += graph[lastNode][i];
                    nextLevelCandidates.push_back(newPath);
                }
            }
        }
        
        std::sort(nextLevelCandidates.begin(), nextLevelCandidates.end(), [](const Path& a, const Path& b) {
            return a.heuristic_cost < b.heuristic_cost;
        });

        beam.clear();
        for (size_t i = 0; i < std::min((size_t)beamWidth, nextLevelCandidates.size()); ++i) {
            beam.push_back(nextLevelCandidates[i]);
        }
    }
    
    std::cout << "No path found" << std::endl;
}

int main() {
    beamSearch(0, 6, 2);
    return 0;
}