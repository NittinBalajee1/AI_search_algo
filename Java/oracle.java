public class CostBasedOracle {
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

    public static void main(String[] args) {
        costBasedOracleSearch(0, 6);
    }

    public static void costBasedOracleSearch(int start, int goal) {
        int n = graph.length;
        boolean[] visited = new boolean[n];
        int[] cost = new int[n];
        int[] parent = new int[n];

        for (int i = 0; i < n; i++) {
            cost[i] = Integer.MAX_VALUE;
            parent[i] = -1;
        }

        cost[start] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = selectMinCostNode(cost, visited);
            if (u == -1) break;
            visited[u] = true;

            if (u == goal) break;

            for (int v = 0; v < n; v++) {
                if (graph[u][v] > 0 && !visited[v]) {
                    int newCost = cost[u] + graph[u][v];
                    if (newCost < cost[v]) {
                        cost[v] = newCost;
                        parent[v] = u;
                    }
                }
            }
        }

        printPath(parent, start, goal);
        System.out.println("\nTotal Cost: " + cost[goal]);
    }

    private static int selectMinCostNode(int[] cost, boolean[] visited) {
        int min = Integer.MAX_VALUE;
        int minIndex = -1;

        for (int i = 0; i < cost.length; i++) {
            if (!visited[i] && cost[i] < min) {
                min = cost[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    private static void printPath(int[] parent, int start, int goal) {
        if (goal == -1) {
            System.out.println("No path found.");
            return;
        }
        System.out.print("Path: ");
        printRecursivePath(parent, start, goal);
    }

    private static void printRecursivePath(int[] parent, int start, int node) {
        if (node == -1) return;
        if (node != start) {
            printRecursivePath(parent, start, parent[node]);
        }
        System.out.print(cities[node] + " ");
    }
}
