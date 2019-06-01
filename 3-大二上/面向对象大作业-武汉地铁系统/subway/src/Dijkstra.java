/* [Deprecated]

    What does not kill me, makes me stronger.

    弃用原因：Dijkstra算法不满足不后效性，
            无法胜任寻找"最少换乘"路径的任务，
            考虑到Floyd算法基于动态规划，
            动态规划算法天生具有无后效性，
            故采用Floyd.
*/

import java.util.*;

public class Dijkstra
{
    private Queue<Integer> visited;
    private ArrayList<Double> dis;
    private HashMap<String, Route> routes;
    private HashMap<Integer, ArrayList<Link>> adjList;

    public Dijkstra(HashMap<Integer, ArrayList<Link>> adjList, HashMap<String, Route> routes)
    {
        this.adjList = adjList;
        this.routes = routes;
    }


    private int getMin()
    {
        int k = -1;
        double min_dist = Double.MAX_VALUE;
        for (int i = 0; i < dis.size(); i++)
        {
            if (!visited.contains(i) && dis.get(i) < min_dist)
            {
                min_dist = dis.get(i);
                k = i;
            }
        }
        return k;
    }

    private static int penalty(int l, int r)
    {
        return l == r ? 0 : 1000;
    }

    public PathPair shortesPath(int begin, int end, String mode)
    {
        visited = new LinkedList<>();
        dis = new ArrayList<>(Collections.nCopies(adjList.size(), Double.MAX_VALUE));
        HashMap<Integer, ArrayList<Link>> path;
        path = new HashMap<>();
        for (int i = 0; i < adjList.size(); i++)
        {
            path.put(i, new ArrayList<>());
        }

        for (Link l : adjList.get(begin))
        {
            dis.set(l.getTo_id(), l.getDist());
            path.get(l.getTo_id()).add(l);
        }
        dis.set(begin, 0.0);
        while (visited.size() < adjList.size())
        {
            int k = getMin();
            visited.add(k);
            if (k != -1)
            {
                System.out.println("For " + k);
                for (Link l : adjList.get(k))
                {
                    // 换乘惩罚，在最少换乘模式下使用
                    int pen = 0;
                    if (mode.equals("least"))
                    {
                        pen = penalty(l.getBelong_id(), path.get(k).size() == 0 ?
                                l.getBelong_id() : path.get(k).get(path.get(k).size() - 1).getBelong_id());
//                        System.out.println(l.getBelong_id() + " : "
//                                + (path.get(k).size() == 0 ? l.getBelong_id() :
//                                path.get(k).get(path.get(k).size() - 1).getBelong_id())
//                                + " : " + pen);
                    }

                    if (dis.get(l.getTo_id()) > dis.get(k) + l.getDist() + pen)
                    {
                        dis.set(l.getTo_id(), dis.get(k) + l.getDist() + pen);
                        path.put(l.getTo_id(), new ArrayList<>(path.get(k)));
                        path.get(l.getTo_id()).add(l);
                    }
                }
                allPath(path);
            }
        }
        if (dis.get(end) != Integer.MAX_VALUE)
        {
//            System.out.format("%s -> %s : %f", begin, end, dis.get(end) % 1000);
//            System.out.println(dis.get(129));
            return new PathPair(path.get(end), dis.get(end));
        }
        else
        {
            return null;
        }
    }

    public static void allPath(HashMap<Integer, ArrayList<Link>> path)
    {
        for (HashMap.Entry<Integer, ArrayList<Link>> e : path.entrySet())
        {
            System.out.println(e.getKey() + " : " + e.getValue());
        }
    }

    public static void add(HashMap<Integer, ArrayList<Link>> al, int from, int to, int belong, double dist)
    {
        al.get(from).add(new Link(from, to, belong, dist));
        al.get(to).add(new Link(to, from, belong, dist));
    }

    public static void main(String[] args)
    {
        HashMap<String, Route> routes = new HashMap<>();
        ArrayList<Integer> path1 = new ArrayList<>();
        path1.add(0);
        path1.add(1);
        path1.add(2);
        routes.put("000", new Route(0, "000", path1));
        ArrayList<Integer> path2 = new ArrayList<>();
        path2.add(0);
        path2.add(3);
        path1.add(1);
        routes.put("111", new Route(1, "111", path2));
        HashMap<Integer, ArrayList<Link>> adjList = new HashMap<>();
        for (int i = 0; i <= 3; i++)
        {
            adjList.put(i, new ArrayList<>());
        }
        add(adjList, 0, 1, 0, 5);
        add(adjList, 1, 2, 0, 3);
        add(adjList, 0, 3, 1, 1);
        add(adjList, 3, 1, 1, 1);
        Dijkstra dij = new Dijkstra(adjList, routes);
        PathPair res = dij.shortesPath(0, 2, "least");
        System.out.println(res.getPath());
        System.out.println(res.getDist());
    }
}