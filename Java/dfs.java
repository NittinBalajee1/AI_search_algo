import java.util.*;

public class DFSpath{
    public static void main(String[] args){
        String[] cities = {"S","A","B","C","D","E","G"};

        int[][] graph = {
            {0,1,1,0,0,0,0},
            {1,0,1,0,1,0,0},
            {1,1,0,1,0,0,0},
            {0,0,1,0,0,1,0},
            {0,1,0,0,0,0,1},
            {0,0,0,1,0,0,0},
            {0,0,0,0,1,0,0}
        };

        String startcit = "S";
        String endcit = "G";
        
        int startin = indexOf(cities,startcit);
        int endin = indexOf(cities,endcit);
        
        boolean[] visited = new boolean[cities.length];
        List<String> path = new ArrayList<>();
        
        System.out.println("All paths from "+ startcit+" to "+endcit+":");
        dfs(cities,graph,startin,endin,visited,path);
        }
        private static void dfs(String[] cities, int[][] graph, int current,int end,boolean[] visited, List<String> path){
            visited[current]=true;
            path.add(cities[current]);
            if(current == end){
                int distance = calcdis(path,cities,graph);
                printpath(path,distance);
            }
            else{
                for(int next=0;next<cities.length;next++){
                    if(!visited[next] && graph[current][next]>0){
                    dfs(cities,graph,next,end,visited,path);
                    }
                }
            }
            
            visited[current]=false;
            path.remove(path.size()-1);
        }
        
        private static int calcdis(List<String> path,String[] cities,int[][] graph){
            int total=0;
            for(int i=0;i<path.size()-1;i++){
                int from = indexOf(cities,path.get(i));
                int to = indexOf(cities,path.get(i+1));
                total+= graph[from][to];
            }
            return total;
        }
        
        private static void printpath(List<String> path,int distance){
            System.out.println(String.join("->",path)+ "| distance = "+distance);
        }
        private static int indexOf(String[] arr, String city){
            for(int i=0;i<arr.length;i++){
                if(arr[i].equals(city)) return i;
            }
            return -1;
        }
}