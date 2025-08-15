import java.util.*;

public class BeamSearch {
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

    public static void beamSearch(String start, String goal, int beamWidth) {
        int startIndex = getCityIndex(start);
        int goalIndex = getCityIndex(goal);

        Queue<List<Integer>> queue = new LinkedList<>();
        queue.add(Arrays.asList(startIndex));

        while (!queue.isEmpty()) {
            List<List<Integer>> nextLevel = new ArrayList<>();

            while (!queue.isEmpty()) {
                List<Integer> path = queue.poll();
                int lastNode = path.get(path.size() - 1);

                if (lastNode == goalIndex) {
                    printPath(path);
                    return;
                }

                for (int i = 0; i < graph.length; i++) {
                    if (graph[lastNode][i] > 0 && !path.contains(i)) {
                        List<Integer> newPath = new ArrayList<>(path);
                        newPath.add(i);
                        nextLevel.add(newPath);
                    }
                }
            }

            nextLevel.sort(Comparator.comparingInt(p -> heuristics[p.get(p.size() - 1)]));
            queue.addAll(nextLevel.subList(0, Math.min(beamWidth, nextLevel.size())));
        }

        System.out.println("No path found!");
    }

    static int getCityIndex(String city) {
        for (int i = 0; i < cities.length; i++) {
            if (cities[i].equals(city)) return i;
        }
        return -1;
    }

    static void printPath(List<Integer> path) {
        for (int i = 0; i < path.size(); i++) {
            System.out.print(cities[path.get(i)]);
            if (i < path.size() - 1) System.out.print(" -> ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        beamSearch("S", "G", 2); 
    }
}
