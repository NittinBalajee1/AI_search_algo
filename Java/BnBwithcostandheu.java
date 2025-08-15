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

    static class Node {
        int city;
        int costSoFar;
        int estimatedTotal;
        String path;
        Node(int city, int costSoFar, int estimatedTotal, String path) {
            this.city = city;
            this.costSoFar = costSoFar;
            this.estimatedTotal = estimatedTotal;
            this.path = path;
        }
    }

    public static void main(String[] args) {
        boolean[] visited = new boolean[cities.length];
        branchAndBound(0, visited);
    }

    static void branchAndBound(int start, boolean[] visited) {
        java.util.PriorityQueue<Node> pq = new java.util.PriorityQueue<>(
            java.util.Comparator.comparingInt(n -> n.estimatedTotal)
        );

        pq.add(new Node(start, 0, heuristics[start], cities[start]));
        visited[start] = true;

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            if (current.city == cities.length - 1) {
                System.out.println("Best Path: " + current.path);
                System.out.println("Best Cost: " + current.costSoFar);
                return;
            }
            for (int i = 0; i < cities.length; i++) {
                if (graph[current.city][i] > 0 && !visited[i]) {
                    int newCost = current.costSoFar + graph[current.city][i];
                    int estimate = newCost + heuristics[i];
                    if (estimate <= oracle) {
                        visited[i] = true;
                        pq.add(new Node(i, newCost, estimate, current.path + " -> " + cities[i]));
                        visited[i] = false;
                    }
                }
            }
        }
    }
}
