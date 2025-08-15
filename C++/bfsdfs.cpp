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

struct Node {
    int city;
    int cost;
    std::vector<int> path;
};

std::string formatPath(const std::vector<int>& path) {
    std::string result = "";
    for (size_t i = 0; i < path.size(); ++i) {
        result += cities[path[i]];
        if (i != path.size() - 1) {
            result += " -> ";
        }
    }
    return result;
}

int resultCost = -1;
std::string resultPath = "";

void dfs(int city, int cost, std::vector<int> path, int goal) {
    if (city == goal) {
        if (resultCost == -1 || cost < resultCost) {
            resultCost = cost;
            resultPath = formatPath(path);
        }
        return;
    }

    for (size_t next = 0; next < cities.size(); ++next) {
        if (graph[city][next] > 0 && std::find(path.begin(), path.end(), next) == path.end()) {
            std::vector<int> newPath = path;
            newPath.push_back(next);
            dfs(next, cost + graph[city][next], newPath, goal);
        }
    }
}

int main() {
    int start = 0;
    int goal = 6;

    std::queue<Node> queue;
    queue.push({start, 0, {start}});

    while (!queue.empty()) {
        Node current = queue.front();
        queue.pop();

        if (current.city == goal) {
            if (resultCost == -1 || current.cost < resultCost) {
                resultCost = current.cost;
                resultPath = formatPath(current.path);
            }
        }

        for (size_t next = 0; next < cities.size(); ++next) {
            if (graph[current.city][next] > 0 && std::find(current.path.begin(), current.path.end(), next) == current.path.end()) {
                std::vector<int> newPath = current.path;
                newPath.push_back(next);
                
                queue.push({next, current.cost + graph[current.city][next], newPath});

                dfs(next, current.cost + graph[current.city][next], newPath, goal);
            }
        }
    }

    if (resultCost != -1) {
        std::cout << "Best Path: " << resultPath << std::endl;
        std::cout << "Best Cost: " << resultCost << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}