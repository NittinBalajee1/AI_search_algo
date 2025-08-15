import java.util.*;

public class DFSPathNoList {
    public static void main(String[] args) {
        String[] cities = {"S", "A", "B", "C", "D", "E", "G"};

        int[][] graph = {
            {0,1,1,0,0,0,0},
            {1,0,1,0,1,0,0},
            {1,1,0,1,0,0,0},
            {0,0,1,0,0,1,0},
            {0,1,0,0,0,0,1},
            {0,0,0,1,0,0,0},
            {0,0,0,0,1,0,0}
        };

        String startCity = "S";
        String endCity = "G";

        int startIndex = indexOf(cities, startCity);
        int endIndex = indexOf(cities, endCity);

        boolean[] visited = new boolean[cities.length];

        System.out.println("All paths from " + startCity + " to " + endCity + ":");
        dfs(cities, graph, startIndex, endIndex, visited, "");
    }

    private static void dfs(String[] cities, int[][] graph, int current, int end, boolean[] visited, String pathSoFar) {
        visited[current] = true;
        pathSoFar += cities[current];
        if (current == end) {
            System.out.println(pathSoFar);
        } else {
            for (int next = 0; next < cities.length; next++) {
                if (!visited[next] && graph[current][next] > 0) {
                    dfs(cities, graph, next, end, visited, pathSoFar + "->");
                }
            }
        }
        visited[current] = false;
    }

    private static int indexOf(String[] arr, String city) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i].equals(city)) return i;
        }
        return -1;
    }
}
