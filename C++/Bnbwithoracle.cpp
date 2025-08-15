#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
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
    int city, cost, bound;
    std::string path;

    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

void branchAndBoundOracle(int start, int goal) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({start, 0, heuristics[start], cities[start]});
    
    int bestCost = std::numeric_limits<int>::max();
    std::string bestPath = "";
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.bound >= bestCost) {
            continue;
        }

        if (current.city == goal) {
            if (current.cost < bestCost) {
                bestCost = current.cost;
                bestPath = current.path;
            }
            continue;
        }

        for (size_t i = 0; i < cities.size(); ++i) {
            if (graph[current.city][i] > 0 && current.path.find(cities[i]) == std::string::npos) {
                int newCost = current.cost + graph[current.city][i];
                int bound = newCost + heuristics[i];
                
                if (bound < bestCost) {
                    pq.push({(int)i, newCost, bound, current.path + " -> " + cities[i]});
                }
            }
        }
    }
    
    std::cout << "Best Path: " << bestPath << std::endl;
    std::cout << "Best Cost: " << bestCost << std::endl;
}

int main() {
    branchAndBoundOracle(0, 6);
    return 0;
}