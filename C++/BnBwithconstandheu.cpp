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

struct Node {
    int city;
    int costSoFar;
    int estimatedTotal;
    std::string path;

    bool operator>(const Node& other) const {
        return estimatedTotal > other.estimatedTotal;
    }
};

void branchAndBound(int start) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    
    pq.push({start, 0, heuristics[start], cities[start]});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.city == cities.size() - 1) {
            std::cout << "Best Path: " << current.path << std::endl;
            std::cout << "Best Cost: " << current.costSoFar << std::endl;
            return;
        }
        
        for (size_t i = 0; i < cities.size(); ++i) {
            if (graph[current.city][i] > 0 && current.path.find(cities[i]) == std::string::npos) {
                int newCost = current.costSoFar + graph[current.city][i];
                int estimate = newCost + heuristics[i];
                
                if (estimate <= oracle) {
                    std::string newPath = current.path + " -> " + cities[i];
                    pq.push({(int)i, newCost, estimate, newPath});
                }
            }
        }
    }
    
    std::cout << "No path found within the oracle bound." << std::endl;
}

int main() {
    branchAndBound(0);
    return 0;
}