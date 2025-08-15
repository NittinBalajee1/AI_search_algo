import java.util.*;

public class BFSwithhis{
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

        String startCit = "S";
        String endCit= "G";

        int startIn = indexOf(cities, startCit);
        int endIn = indexOf(cities, endCit);


        System.out.println("All paths from " + startCit + " to " + endCit + ":");
        bfs(cities, graph, startIn, endIn);
    }
    private static void bfs(String[] cities,int[][] graph,int startIn,int endIn){
        Queue<List<Integer>> queue = new LinkedList<>();
        queue.add(Arrays.asList(startIn));
        
        while(!queue.isEmpty()){
            List<Integer> path = queue.poll();
            int lastnode = path.get(path.size()-1);
            if(lastnode == endIn){
                printpath(path,cities);
            }
            else{
                for(int next = 0;next<cities.length;next++){
                    if(graph[lastnode][next]>0&&!path.contains(next)){
                        List<Integer> newpath = new ArrayList<>(path);
                        newpath.add(next);
                        queue.add(newpath);
                    }
                }
            }
        }
    }
    private static void printpath(List<Integer> path, String[] cities){
        List<String> pathnames = new ArrayList<>();
        
        for(int in:path){
            pathnames.add(cities[in]);
        }
        System.out.println(String.join("->",pathnames));
    }
    
    private static int indexOf(String[] arr,String city){
        for(int i=0;i<arr.length;i++){
            if(arr[i].equals(city)) return i;
        }
        return -1;
    }

}