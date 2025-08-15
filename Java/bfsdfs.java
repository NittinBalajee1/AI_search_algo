import java.util.*;

public class DFSBFSCombo {
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

    static class Node {
        int city;
        int cost;
        List<Integer> path;
        Node(int city, int cost, List<Integer> path) {
            this.city = city;
            this.cost = cost;
            this.path = new ArrayList<>(path);
        }
    }

    public static void main(String[] args) {
        int start = 0; 
        int goal = 6;  
        String resultPath = "";
        int resultCost = Integer.MAX_VALUE;

       
        Queue<Node> queue = new LinkedList<>();
        queue.add(new Node(start, 0, Arrays.asList(start)));

        while (!queue.isEmpty()) {
            Node current = queue.poll();

            if (current.city == goal && current.cost < resultCost) {
                resultCost = current.cost;
                resultPath = formatPath(current.path);
            }

            for (int next = 0; next < cities.length; next++) {
                if (graph[current.city][next] > 0 && !current.path.contains(next)) {
                    List<Integer> newPath = new ArrayList<>(current.path);
                    newPath.add(next);

                    queue.add(new Node(next, current.cost + graph[current.city][next], newPath));

                    dfs(next, current.cost + graph[current.city][next], newPath, goal);
                }
            }
        }

        System.out.println("Best Path: " + resultPath);
        System.out.println("Best Cost: " + resultCost);
    }

    static void dfs(int city, int cost, List<Integer> path, int goal) {
        if (city == goal) return;
        for (int next = 0; next < cities.length; next++) {
            if (graph[city][next] > 0 && !path.contains(next)) {
                List<Integer> newPath = new ArrayList<>(path);
                newPath.add(next);
                dfs(next, cost + graph[city][next], newPath, goal);
            }
        }
    }

    static String formatPath(List<Integer> path) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < path.size(); i++) {
            sb.append(cities[path.get(i)]);
            if (i != path.size() - 1) sb.append(" -> ");
        }
        return sb.toString();
    }
}
