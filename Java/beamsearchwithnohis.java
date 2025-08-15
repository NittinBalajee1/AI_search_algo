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

    public static void beamSearch(int start, int goal, int beamWidth) {
        Queue<List<Integer>> beam = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();
        List<Integer> startPath = new ArrayList<>();
        startPath.add(start);
        beam.add(startPath);

        while (!beam.isEmpty()) {
            List<List<Integer>> candidates = new ArrayList<>();
            while (!beam.isEmpty()) {
                List<Integer> path = beam.poll();
                int lastNode = path.get(path.size() - 1);
                if (lastNode == goal) {
                    printPath(path);
                    return;
                }
                visited.add(lastNode);
                for (int i = 0; i < graph[lastNode].length; i++) {
                    if (graph[lastNode][i] > 0 && !visited.contains(i)) {
                        List<Integer> newPath = new ArrayList<>(path);
                        newPath.add(i);
                        candidates.add(newPath);
                    }
                }
            }
            candidates.sort(Comparator.comparingInt(p -> heuristics[p.get(p.size() - 1)]));
            beam.clear();
            for (int i = 0; i < Math.min(beamWidth, candidates.size()); i++) {
                beam.add(candidates.get(i));
            }
        }
        System.out.println("No path found");
    }

    static void printPath(List<Integer> path) {
        for (int i = 0; i < path.size(); i++) {
            System.out.print(cities[path.get(i)]);
            if (i < path.size() - 1) System.out.print(" -> ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        beamSearch(0, 6, 2);
    }
}
