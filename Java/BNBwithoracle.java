import java.util.*;

public class BranchAndBoundOracle {
    static String[] cities = {"S", "A", "B", "C", "D", "E", "G"};
    static int[][] graph = {
        {0, 3, 5, 0, 0, 0, 0},
        {3, 0, 4, 0, 5, 0, 0},
        {5, 4, 0, 4, 0, 0, 0},
        {0, 0, 4, 0, 0, 6, 0},
        {0, 5, 0, 0, 0, 0, 3},
        {0, 0, 0, 6, 0, 0, 0},
        {0, 0, 0, 0, 3, 0, 0}
    };
    static int[] heuristics = {0, 7, 6, 7, 3, 4, 0};

    static class Node implements Comparable<Node> {
        int city, cost, bound;
        String path;
        Node(int c, int co, int b, String p) {
            city = c; cost = co; bound = b; path = p;
        }
        public int compareTo(Node o) {
            return Integer.compare(bound, o.bound);
        }
    }

    public static void main(String[] args) {
        branchAndBoundOracle(0, 6);
    }

    static void branchAndBoundOracle(int start, int goal) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(start, 0, heuristics[start], cities[start]));
        int bestCost = Integer.MAX_VALUE;
        String bestPath = "";
        while (!pq.isEmpty()) {
            Node current = pq.poll();
            if (current.bound >= bestCost) continue;
            if (current.city == goal) {
                if (current.cost < bestCost) {
                    bestCost = current.cost;
                    bestPath = current.path;
                }
                continue;
            }
            for (int i = 0; i < cities.length; i++) {
                if (graph[current.city][i] > 0 && !current.path.contains(cities[i])) {
                    int newCost = current.cost + graph[current.city][i];
                    int bound = newCost + heuristics[i];
                    if (bound < bestCost) {
                        pq.add(new Node(i, newCost, bound, current.path + " -> " + cities[i]));
                    }
                }
            }
        }
        System.out.println("Best Path: " + bestPath);
        System.out.println("Best Cost: " + bestCost);
    }
}
