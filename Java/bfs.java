import java.util.*;

public class BFSpath{
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
        

        bfs(cities,graph,startin,endin);
        }
        private static void bfs(String[] cities, int[][] graph, int start,int end){
            Queue<Integer> queue = new LinkedList<>();
            boolean[] visited = new boolean[cities.length];
            int[] parent = new int[cities.length];
            Arrays.fill(parent,-1);
            
            queue.add(start);
            visited[start]=true;
            
            while(!queue.isEmpty()){
                int current= queue.poll();
                
                if(current == end){
                    printpath(cities,parent,start,end,graph);
                    return;
                }
                for(int next=0;next<cities.length;next++){
                    if(graph[current][next]>0 && !visited[next]){
                        visited[next]=true;
                        parent[next]=current;
                        queue.add(next);
                    }
                }
            }
        }
        private static void printpath(String[] cities,int[] parent,int start,int end,int[][] graph){
            List<Integer> path = new ArrayList<>();
            for(int at = end; at!=-1;at=parent[at]){
                path.add(at);
            }
            Collections.reverse(path);
            
            int distance = 0;
            for(int i=0;i<path.size()-1;i++){
                distance+=graph[path.get(i)][path.get(i+1)];
            }
            
            List<String> names = new ArrayList<>();
            for(int idx:path){
                names.add(cities[idx]);
            }
            System.out.println("Shortest path: "+String.join("->",names)+" | distance = "+distance);
        }
        private static int indexOf(String[] arr,String city){
            for(int i=0;i< arr.length;i++){
                if(arr[i].equals(city)) return i;
            }
            return -1;
        }
}    
      