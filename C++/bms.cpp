#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

// Function to find the index of a city
int indexOf(const std::vector<std::string>& arr, const std::string& city) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == city) {
            return i;
        }
    }
    return -1;
}

// Function to print a path and its distance
void printPath(const std::vector<std::string>& path, int distance) {
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << "->";
        }
    }
    std::cout << "| distance = " << distance << std::endl;
}

// Function to calculate the total distance of a path
int calcDistance(const std::vector<std::string>& path, const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph) {
    int total = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int from = indexOf(cities, path[i]);
        int to = indexOf(cities, path[i + 1]);
        if (from != -1 && to != -1) {
            total += graph[from][to];
        }
    }
    return total;
}

// Function to validate if a path is connected in the graph
bool pathValid(const std::vector<std::string>& path, const std::vector<std::string>& cities, const std::vector<std::vector<int>>& graph) {
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int from = indexOf(cities, path[i]);
        int to = indexOf(cities, path[i + 1]);
        if (from == -1 || to == -1 || graph[from][to] == 0) {
            return false;
        }
    }
    return true;
}

// Recursive function to generate all permutations of a list
void perm(std::vector<std::string>& arr, int index, std::vector<std::vector<std::string>>& results) {
    if (index == arr.size()) {
        results.push_back(arr);
        return;
    }
    for (size_t i = index; i < arr.size(); ++i) {
        std::swap(arr[i], arr[index]);
        perm(arr, index + 1, results);
        std::swap(arr[i], arr[index]);
    }
}

// Wrapper function for permutations
std::vector<std::vector<std::string>> genPerm(const std::vector<std::string>& list) {
    std::vector<std::vector<std::string>> results;
    if (list.empty()) {
        results.push_back({});
        return results;
    }
    std::vector<std::string> arr = list;
    perm(arr, 0, results);
    return results;
}

// Recursive function to generate subsets of a given size
void genSubHelp(const std::vector<std::string>& list, int k, size_t start, std::vector<std::string>& current, std::vector<std::vector<std::string>>& result) {
    if (current.size() == k) {
        result.push_back(current);
        return;
    }
    for (size_t i = start; i < list.size(); ++i) {
        current.push_back(list[i]);
        genSubHelp(list, k, i + 1, current, result);
        current.pop_back();
    }
}

// Wrapper function for subset generation
std::vector<std::vector<std::string>> genSub(const std::vector<std::string>& list, int k) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> current;
    genSubHelp(list, k, 0, current, result);
    return result;
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

    std::string startcit = "S";
    std::string endcit = "G";

    std::vector<std::string> middle;
    for (const std::string& city : cities) {
        if (city != startcit && city != endcit) {
            middle.push_back(city);
        }
    }
    
    std::cout << "All valid paths from " << startcit << " to " << endcit << std::endl;
    
    for (size_t size = 0; size <= middle.size(); ++size) {
        std::vector<std::vector<std::string>> subsets = genSub(middle, size);
        for (const auto& subset : subsets) {
            std::vector<std::vector<std::string>> midpaths = genPerm(subset);
            
            for (const auto& midpath : midpaths) {
                std::vector<std::string> fullpath;
                fullpath.push_back(startcit);
                fullpath.insert(fullpath.end(), midpath.begin(), midpath.end());
                fullpath.push_back(endcit);
                
                if (pathValid(fullpath, cities, graph)) {
                    int distance = calcDistance(fullpath, cities, graph);
                    printPath(fullpath, distance);
                }
            }
        }
    }

    return 0;
}