#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>

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
const int oracle = 11;
std::string bestPath = "";
int bestCost = std::numeric_limits<int>::max();

struct Node {
    std::string path;
    int city, cost, bound;

    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

void branchAndBound() {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({"S", 0, 0, heuristics[0]});
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.bound > oracle) {
            continue;
        }
        
        if (current.city == cities.size() - 1) {
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
                
                if (bound <= oracle) {
                    pq.push({current.path + " -> " + cities[i], (int)i, newCost, bound});
                }
            }
        }
    }
}

int main() {
    branchAndBound();
    std::cout << "Best Path: " << bestPath << std::endl;
    std::cout << "Best Cost: " << bestCost << std::endl;
    return 0;
}