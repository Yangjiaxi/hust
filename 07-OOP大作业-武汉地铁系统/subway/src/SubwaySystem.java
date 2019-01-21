import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class SubwaySystem
{
    private HashMap<Integer, Station> stations;
    private HashMap<Integer, String> idToRouteStr;
    private HashMap<String, Route> routes;
    //    private Dijkstra dijkstra;  // [Deprecated]  fuck life
    private Floyd floyd;

    public SubwaySystem()
    {
        System.out.println("Creating subway system...");

        stations = new HashMap<>();
        idToRouteStr = new HashMap<>();
        routes = new HashMap<>();
        HashMap<Integer, ArrayList<Link>> matrix = new HashMap<>();

        SubwayDA sda = new SubwayDA();
        sda.init();

        ArrayList<Station> DB_stations = sda.get_station();
        for (Station s : DB_stations)
        {
            stations.put(s.getId(), s);
            matrix.put(s.getId(), new ArrayList<>());
        }

        ArrayList<Route> DB_routes = sda.get_route();
        for (Route s : DB_routes)
        {
            routes.put(s.getName(), s);
            idToRouteStr.put(s.getId(), s.getName());
        }

        ArrayList<Link> DB_links = sda.get_link();
        for (Link s : DB_links)
        {
            matrix.get(s.getFrom_id()).add(s);
            matrix.get(s.getTo_id()).add(s.reverse());
        }
//        dijkstra = new Dijkstra(this.matrix, this.routes);
        floyd = new Floyd(matrix);
        System.out.println("==>Complete!");
        System.out.println();
//        System.out.println(stations);
//        System.out.println(routes);
//        for (int i = 0; i < matrix.size(); i++)
//        {
//            System.out.println("id: " + i + " name: " + stations.get(i).getName());
//            System.out.println(matrix.get(i));
//        }
    }

    private int getStationID(String stationName)
    {
        for (HashMap.Entry<Integer, Station> s : stations.entrySet())
        {
            if (s.getValue().getName().equals(stationName))
            {
                return s.getValue().getId();
            }
        }
        System.out.println("No such station called " + stationName);
        return -1;
    }

    public ArrayList<Route> showAllRouteHasStation(String stationName)
    {
        System.out.println("Search for: " + stationName);
        int station_id;
        ArrayList<Route> res = new ArrayList<>();
        station_id = getStationID(stationName);
        if (station_id == -1)
        {
            System.out.println("No such station");
            return null;
        }

        for (Route cur : routes.values())
        {
            if (cur.getPath().contains(station_id))
            {
                System.out.println("\tfound: " + cur.getName());
                res.add(cur);
            }
        }
        System.out.println();
        return res;
    }

    public ArrayList<Station> showAllStations(String routeName, String endStation)
    {
        System.out.println("线路: " + routeName + "\t开往: " + endStation);
        Route route = routes.get(routeName);
        ArrayList<Station> res = new ArrayList<>();
        int end_id;
        end_id = getStationID(endStation);
        if (end_id == -1)
        {
            System.out.println("No such station");
            return null;
        }

        if (route.getPath().get(route.getPath().size() - 1) != end_id)
        {

            Collections.reverse(route.getPath());
        }

        for (int station_id : route.getPath())
        {
            res.add(stations.get(station_id));
            System.out.println("\t - " + stations.get(station_id).getName());
        }
        System.out.println("\n");
        return res;
    }

    public PathPair showShortestPath(String startStation, String endStation, boolean output)
    {
        int start_id = 0;
        int end_id = 0;

        start_id = getStationID(startStation);
        end_id = getStationID(endStation);
        if (start_id == -1 || end_id == -1)
        {
            System.out.println("No such station");
            return null;
        }
        System.out.format("\nFrom %s to %s with SHORTEST path\n",
                stations.get(start_id).getName(),
                stations.get(end_id).getName());
//        PathPair res = dijkstra.shortesPath(start_id, end_id, "shortest");
        PathPair res = floyd.floyd(start_id, end_id, "shortest");
        if (res != null)
        {
            System.out.format("Path length: %.3f\n", res.getDist());
            if (output)
            {
                for (Link l : res.getPath())
                {
                    System.out.format("\t| %s \t| %f \t| %s -> %s\n",
                            routes.get(idToRouteStr.get(l.getBelong_id())).getName(),
                            l.getDist(),
                            stations.get(l.getFrom_id()).getName(),
                            stations.get(l.getTo_id()).getName());
                }
                System.out.println();
            }
            return res;
        }
        else
        {
            System.out.println("No such path");
            return null;
        }
    }

    public PathPair showLeastTransfer(String startStation, String endStation, boolean output)
    {
        int start_id;
        int end_id;
        start_id = getStationID(startStation);
        end_id = getStationID(endStation);
        if (start_id == -1 || end_id == -1)
        {
            System.out.println("No such station");
            return null;
        }
        System.out.format("\nFrom %s to %s with LEAST transfer\n",
                stations.get(start_id).getName(),
                stations.get(end_id).getName());
//        PathPair res = dijkstra.shortesPath(start_id, end_id, "least");
        PathPair res = floyd.floyd(start_id, end_id, "least");
        if (res != null)
        {
            System.out.format("Path length: %.3f\n", res.getDist());
            if (output)
            {
                for (Link l : res.getPath())
                {
                    System.out.format("\t| %s \t| %f \t| %s -> %s\n",
                            routes.get(idToRouteStr.get(l.getBelong_id())).getName(),
                            l.getDist(),
                            stations.get(l.getFrom_id()).getName(),
                            stations.get(l.getTo_id()).getName());
                }
                System.out.println();
            }
            return res;
        }
        else
        {
            System.out.println("No such path");
            return null;
        }
    }

    public ArrayList<String> printPath(ArrayList<Link> path)
    {
        ArrayList<String> res = new ArrayList<>();
        Link cur;
        int pre_id = -1;
        String line = null;
        for (int i = 0; i < path.size(); i++)
        {
            cur = path.get(i);
            if (cur.getBelong_id() != pre_id)
            {
                pre_id = cur.getBelong_id();
                if (i == 0)
                {
                    line = "乘" +
                            routes.get(idToRouteStr.get(cur.getBelong_id())).getName() +
                            "  [" + stations.get(cur.getFrom_id()).getName();
                }
                else
                {
                    System.out.println(line + "->" + stations.get(path.get(i - 1).getTo_id()).getName() + "]");
                    res.add(line + "->" + stations.get(path.get(i - 1).getTo_id()).getName() + "]");
                    line = "换乘" +
                            routes.get(idToRouteStr.get(cur.getBelong_id())).getName() +
                            "  [" + stations.get(cur.getFrom_id()).getName();
                }
            }
        }
        res.add(line + "->" + stations.get(path.get(path.size() - 1).getTo_id()).getName() + "]");
        System.out.println(line + "->" + stations.get(path.get(path.size() - 1).getTo_id()).getName() + "]");
        line = "共 " + path.size() + " 站";
        System.out.println(line);
        res.add(line);
        return res;
    }

    public double pathPay(PathPair pathPair, Payment mod)
    {
        System.out.println();
        double cost = mod.pay(pathPair.getDist());
        System.out.println("需要 " + cost + " 元");
        System.out.println();
        return cost;
    }

    public String getStationName(int stationId)
    {
        return stations.get(stationId).getName();
    }

    public ArrayList<String> getAllRouteName()
    {
        ArrayList<String> res = new ArrayList<>(routes.keySet());
        res.sort((o1, o2) ->
        {
            if (o1.length() != o2.length())
            {
                return Integer.compare(o1.length(), o2.length());
            }
            else
            {
                return o1.compareTo(o2);
            }
        });
        return res;
    }

    public int[] getRouteHeadTail(String name)
    {
        ArrayList<Integer> path = routes.get(name).getPath();
        return new int[]{path.get(0), path.get(path.size() - 1)};
    }

    public static void main(String[] args)
    {
        SubwaySystem Wuhan = new SubwaySystem();
//        System.out.println(Wuhan.getAllRouteName());
        PathPair res = Wuhan.showLeastTransfer("楚河汉街", "中南路", false);
        System.out.println(res.getPath());
    }
}
