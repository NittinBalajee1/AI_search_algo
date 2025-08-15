import java.util.*;

public class AStarOracle {
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
        int city, g, h;
        List<Integer> path;
        Node(int city, int g, int h, List<Integer> path) {
            this.city = city;
            this.g = g;
            this.h = h;
            this.path = path;
        }
        int f() { return g + h; }
        public int compareTo(Node other) { return Integer.compare(this.f(), other.f()); }
    }

    public static void main(String[] args) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        pq.add(new Node(0, 0, heuristics[0], Arrays.asList(0)));
        boolean[] visited = new boolean[cities.length];

        while (!pq.isEmpty()) {
            Node current = pq.poll();
            if (current.city == cities.length - 1) {
                System.out.print("Best Path: ");
                for (int i = 0; i < current.path.size(); i++) {
                    System.out.print(cities[current.path.get(i)]);
                    if (i < current.path.size() - 1) System.out.print(" -> ");
                }
                System.out.println("\nBest Cost: " + current.g);
                return;
            }
            visited[current.city] = true;
            for (int i = 0; i < cities.length; i++) {
                if (graph[current.city][i] > 0 && !visited[i]) {
                    List<Integer> newPath = new ArrayList<>(current.path);
                    newPath.add(i);
                    pq.add(new Node(i, current.g + graph[current.city][i], heuristics[i], newPath));
                }
            }
        }
    }
}
