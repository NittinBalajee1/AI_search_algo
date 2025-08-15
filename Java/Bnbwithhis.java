import java.util.*;

public class BranchBoundOracle {
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
    static int oracle = 11;
    static String bestPath = "";
    static int bestCost = Integer.MAX_VALUE;

    static class Node implements Comparable<Node> {
        String path;
        int city, cost, bound;
        Node(String path, int city, int cost, int bound) {
            this.path = path;
            this.city = city;
            this.cost = cost;
            this.bound = bound;
        }
        public int compareTo(Node o) {
            return Integer.compare(this.bound, o.bound);
        }
    }

    static void branchAndBound() {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node("S", 0, 0, heuristics[0]));
        while (!pq.isEmpty()) {
            Node current = pq.poll();
            if (current.bound > oracle) continue;
            if (current.city == cities.length - 1) {
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
                    if (bound <= oracle) {
                        pq.add(new Node(current.path + " -> " + cities[i], i, newCost, bound));
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        branchAndBound();
        System.out.println("Best Path: " + bestPath);
        System.out.println("Best Cost: " + bestCost);
    }
}
