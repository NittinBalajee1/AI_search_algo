import java.util.*;

public class HillClimbWithHistory {
    public static void main(String[] args) {
        String[] cities = {"S", "A", "B", "C", "D", "E", "G"};

        int[][] graph = {
            {0,3,5,0,0,0,0},
            {3,0,4,0,5,0,0},
            {5,4,0,4,0,0,0},
            {0,0,4,0,0,6,0},
            {0,5,0,0,0,0,3},
            {0,0,0,6,0,0,0},
            {0,0,0,0,3,0,0}
        };

        int[] heuristics = {0, 7, 6, 7, 3, 4, 0};

        String startCit = "S";
        String endCit = "G";

        List<String> path = hillclimbWithHistory(cities, graph, heuristics, startCit, endCit);
        if (path != null) {
            System.out.println(String.join("->", path));
        } else {
            System.out.println("No path found.");
        }
    }

    static List<String> hillclimbWithHistory(String[] cities, int[][] graph, int[] heuristics, String startCit, String endCit) {
        int startin = indexOf(cities, startCit);
        int endin = indexOf(cities, endCit);

        List<String> path = new ArrayList<>();
        boolean[] visited = new boolean[cities.length];

        int current = startin;
        path.add(cities[current]);
        visited[current] = true;

        while (current != endin) {
            int nextCity = -1;
            int bestHeuristic = Integer.MAX_VALUE;

            for (int i = 0; i < cities.length; i++) {
                if (!visited[i] && graph[current][i] > 0) {
                    if (nextCity == -1 || heuristics[i] < bestHeuristic ||
                       (heuristics[i] == bestHeuristic && cities[i].compareTo(cities[nextCity]) < 0)) {
                        bestHeuristic = heuristics[i];
                        nextCity = i;
                    }
                }
            }

            if (nextCity == -1) {
                return null;
            }

            current = nextCity;
            path.add(cities[current]);
            visited[current] = true;
        }
        return path;
    }

    static int indexOf(String[] arr, String index) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(index)) return i;
        }
        return -1;
    }
}
