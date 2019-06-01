import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Floyd
{
    private ArrayList<ArrayList<Double>> dis_shortest;
    private HashMap<Integer, HashMap<Integer, ArrayList<Link>>> path_shortest;

    private ArrayList<ArrayList<Double>> dis_least;
    private HashMap<Integer, HashMap<Integer, ArrayList<Link>>> path_least;

    private HashMap<Integer, ArrayList<Link>> adjList;


    public Floyd(HashMap<Integer, ArrayList<Link>> adjList)
    {
        this.adjList = adjList;

        dis_shortest = new ArrayList<>();
        path_shortest = new HashMap<>();

        dis_least = new ArrayList<>();
        path_least = new HashMap<>();

        System.out.println("Precomputing path system...");
        build_all();
        System.out.println("==>Path system done!");
    }

    private static boolean cmpLinkTwo(Link l, Link r)
    {
        return l.getFrom_id() == r.getFrom_id() && l.getTo_id() == r.getTo_id();
    }

    private static double penalty(ArrayList<Link> pre, ArrayList<Link> post)
    {
        if (pre.size() == 0 || post.size() == 0)
        {
            return 0.0;
        }
        else
        {
            Link left = pre.get(pre.size() - 1);
            Link right = post.get(0);
            return left.getBelong_id() == right.getBelong_id() ? 0 : 1000;

        }
    }

    private static ArrayList<Link> cast_pre(ArrayList<Link> pre, Link post)
    {
        ArrayList<Link> cp_pre = new ArrayList<>(pre);
        if (post != null && cp_pre.size() >= 2)
        {
            if (cmpLinkTwo(cp_pre.get(cp_pre.size() - 1), cp_pre.get(cp_pre.size() - 2)))
            {
                if (cp_pre.get(cp_pre.size() - 1).getBelong_id() == post.getBelong_id())
                {
                    cp_pre.remove(cp_pre.size() - 2);
                }
                else
                {
                    cp_pre.remove(cp_pre.size() - 1);
                }
            }
        }
        return cp_pre;
    }

    private static ArrayList<Link> cast_post(Link pre, ArrayList<Link> post)
    {
        ArrayList<Link> cp_post = new ArrayList<>(post);
        if (pre != null && cp_post.size() >= 2)
        {
            if (cmpLinkTwo(cp_post.get(0), cp_post.get(1)))
            {
                if (cp_post.get(0).getBelong_id() == pre.getBelong_id())
                {
                    cp_post.remove(1);
                }
                else
                {
                    cp_post.remove(0);
                }
            }
        }
        return cp_post;
    }

    public void build_all()
    {
        dis_shortest.clear();
        dis_least.clear();

        for (int i = 0; i < adjList.size(); i++)
        {
            dis_shortest.add(new ArrayList<>(Collections.nCopies(adjList.size(), Double.MAX_VALUE)));
            dis_least.add(new ArrayList<>(Collections.nCopies(adjList.size(), Double.MAX_VALUE)));
        }

        for (int i = 0; i < adjList.size(); i++)
        {
            path_shortest.put(i, new HashMap<>());
            path_least.put(i, new HashMap<>());

            for (int j = 0; j < adjList.size(); j++)
            {
                path_shortest.get(i).put(j, new ArrayList<>());
                path_least.get(i).put(j, new ArrayList<>());
                if (i == j)
                {
                    dis_shortest.get(i).set(j, 0.0);
                    dis_least.get(i).set(j, 0.0);
                }
            }
        }
        for (ArrayList<Link> ll : adjList.values())
        {
            for (Link l : ll)
            {
                dis_shortest.get(l.getFrom_id()).set(l.getTo_id(), l.getDist());
                dis_least.get(l.getFrom_id()).set(l.getTo_id(), l.getDist());

                path_shortest.get(l.getFrom_id()).get(l.getTo_id()).add(l);
                path_least.get(l.getFrom_id()).get(l.getTo_id()).add(l);
            }
        }

        ArrayList<HashMap<Integer, HashMap<Integer, ArrayList<Link>>>> paths = new ArrayList<>();
        ArrayList<ArrayList<ArrayList<Double>>> dists = new ArrayList<>();
        paths.add(path_shortest);
        dists.add(dis_shortest);
        paths.add(path_least);
        dists.add(dis_least);

        ArrayList<Link> pre, post, comb, left, right;
        for (int k = 0; k < adjList.size(); k++)
        {
            for (int i = 0; i < adjList.size(); i++)
            {
                for (int j = 0; j < adjList.size(); j++)
                {
                    for (int d = 0; d <= 1; d++)
                    {
                        left = paths.get(d).get(i).get(k);
                        right = paths.get(d).get(k).get(j);
                        pre = cast_pre(left, right.size() != 0 ? right.get(0) : null);
                        post = cast_post(left.size() != 0 ? left.get(left.size() - 1) : null, right);
                        double pen = d * penalty(pre, post);
                        if (dists.get(d).get(i).get(j) > dists.get(d).get(i).get(k) + dists.get(d).get(k).get(j) + pen)
                        {
                            comb = new ArrayList<>(pre);
                            comb.addAll(post);
                            paths.get(d).get(i).put(j, comb);
                            dists.get(d).get(i).set(j, dists.get(d).get(i).get(k) + dists.get(d).get(k).get(j) + pen);
                        }
                    }
                }
            }
        }
    }

    public PathPair floyd(int begin, int end, String mode)
    {
        ArrayList<ArrayList<Double>> dis;
        HashMap<Integer, HashMap<Integer, ArrayList<Link>>> path;
        if (mode.equals("least"))
        {
            dis = dis_least;
            path = path_least;
        }
        else
        {
            dis = dis_shortest;
            path = path_shortest;
        }

        if (dis.get(begin).get(end) != Double.MAX_VALUE)
        {
            ArrayList<Link> path_res = new ArrayList<>(path.get(begin).get(end));
            if (path_res.size() == 2 && cmpLinkTwo(path_res.get(0), path_res.get(1)))
            {
                path_res.remove(1);
            }
            return new PathPair(path_res, dis.get(begin).get(end) % 1000);
        }
        else
        {
            System.out.println("ERROR");
            return null;
        }
    }

    private static void add(HashMap<Integer, ArrayList<Link>> al, int from, int to, int belong, double dist)
    {
        al.get(from).add(new Link(from, to, belong, dist));
        al.get(to).add(new Link(to, from, belong, dist));
    }

    public static void main(String[] args)
    {
        HashMap<Integer, ArrayList<Link>> adjList = new HashMap<>();
        for (int i = 0; i <= 3; i++)
        {
            adjList.put(i, new ArrayList<>());
        }
        add(adjList, 0, 1, 0, 1);

        add(adjList, 1, 2, 0, 3);
        add(adjList, 2, 3, 0, 3);

        add(adjList, 1, 2, 1, 3);
        Floyd floyd = new Floyd(adjList);
        PathPair res = floyd.floyd(3, 0, "least");
        System.out.println(res.getPath());
        System.out.println(res.getDist());
    }
}
