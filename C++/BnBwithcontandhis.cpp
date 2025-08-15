#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <algorithm>

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
const std::vector<int> heuristics = {0, 7, 6, 7, 3, 4, 0};

struct Node {
    int city;
    int g;
    int h;
    std::vector<int> path;

    int f() const { return g + h; }

    bool operator>(const Node& other) const {
        return f() > other.f();
    }
};

int main() {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    
    pq.push({0, 0, heuristics[0], {0}});
    std::vector<bool> visited(cities.size(), false);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.city == cities.size() - 1) {
            std::cout << "Best Path: ";
            for (size_t i = 0; i < current.path.size(); ++i) {
                std::cout << cities[current.path[i]];
                if (i < current.path.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << "\nBest Cost: " << current.g << std::endl;
            return 0;
        }

        visited[current.city] = true;

        for (size_t i = 0; i < cities.size(); ++i) {
            if (graph[current.city][i] > 0 && !visited[i]) {
                std::vector<int> newPath = current.path;
                newPath.push_back(i);
                pq.push({(int)i, current.g + graph[current.city][i], heuristics[i], newPath});
            }
        }
    }
    
    std::cout << "No path found." << std::endl;

    return 0;
}