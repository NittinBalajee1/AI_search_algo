import java.util.*;

public class BMS{
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

        List<String> middle = new ArrayList<>();
        for(String city : cities){
            if(!city.equals(startcit) && !city.equals(endcit)){
                middle.add(city);
            }
        }
        
        System.out.println("All valid paths from "+startcit+" to "+endcit);
        
        for(int size =0;size<=middle.size();size++){
            List<List<String>> subsets = gensub(middle,size);
            for(List<String> subset : subsets){
                List<List<String>> midpaths = Genperm(subset);
        
                for(List<String>midpath:midpaths)
                {
                    List<String> fullpath = new ArrayList<>();
                    fullpath.add(startcit);
                    fullpath.addAll(midpath);
                    fullpath.add(endcit);
        
                    if(Pathvalid(fullpath,cities,graph)){
                        int distance = calcdistance(fullpath,cities,graph);
                        printpath(fullpath,distance);
                    }
                }
            }
        }
    }
    private static List<List<String>> gensub(List<String> list,int k){
        List<List<String>> result = new ArrayList<>();
        gensubhelp(list,k,0,new ArrayList<>(),result);
        return result;
    }
    private static void gensubhelp(List<String> list,int k,int start,List<String> current, List<List<String>> result){
        if(current.size()==k){
            result.add(new ArrayList<>(current));
            return;
        }
        for (int i = start; i < list.size(); i++) {
            current.add(list.get(i));
            gensubhelp(list, k, i + 1, current, result);
            current.remove(current.size() - 1);
        }
    }
    private static List<List<String>> Genperm(List<String> list){
        List<List<String>> results=new ArrayList<>();
        perm(list,0,results);
        return results;
    }
    private static void perm(List<String> arr,int index,List<List<String>> results)
    {
        if(index == arr.size()-1){
            results.add(new ArrayList<>(arr));
            return;
        }
        for(int i=index;i<arr.size();i++){
            Collections.swap(arr,i,index);
            perm(arr,index+1,results);
            Collections.swap(arr,i,index);
        }
    }
    private static boolean Pathvalid(List<String> path,String[] cities,int[][] graph){
        for(int i=0;i<path.size()-1;i++){
            int from = indexOf(cities,path.get(i));
            int to = indexOf(cities,path.get(i+1));
            if(graph[from][to]==0)return false;
        }
        return true;
    }
    private static int calcdistance(List<String> path,String[] cities,int[][] graph){
        int total = 0;
        for(int i=0;i<path.size()-1;i++){
            int from = indexOf(cities,path.get(i));
            int to = indexOf(cities,path.get(i+1));
            total += graph[from][to]; 
        }
        return total;
    }
    private static int indexOf(String[] arr,String city){
        for(int i=0;i<arr.length;i++){
            if(arr[i].equals(city)) return i;
        }
        return -1;
    }

    private static void printpath(List<String> path,int distance){
        System.out.println(String.join("->",path)+"| distance = "+distance);
    }
}