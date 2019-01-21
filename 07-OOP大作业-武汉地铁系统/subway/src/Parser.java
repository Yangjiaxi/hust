import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class Parser
{
    public static void readAndSave(String path)
    {
        File txt = new File(path);
        SubwayDA sda = new SubwayDA();
        if (sda.init_subway() == 1)
        {
            System.out.println("Prarsing start...");
            try
            {
                Scanner scan = new Scanner(txt);
                int state = 0;
                int routeCount = 0; //分配线路的ID
                String routeName = null;
                HashMap<String, Integer> stationMap = new HashMap<>(); //站点->ID，按照录取顺序分配
                ArrayList<Integer> route = new ArrayList<>();
            /*
                0: 待机态，不读入数据
                1: 读入态
             */
                while (scan.hasNext())
                {
                    String ss = scan.nextLine();
                    switch (state)
                    {
                    /*
                        0 ->
                            0 读入空行
                            1 读入非空行，此时分离路线名，
                     */
                        case 0:
                            if (ss.trim().length() == 0)
                            {
                                state = 0; //uncessary
                            }
                            else
                            {
//                                System.out.println("\n==============[START]================");
                                routeName = ss.split("站点间距")[0].trim();
//                                System.out.println(routeName + "\t" + routeCount);
                                routeCount++;
                                state = 1;
                                scan.nextLine();
                                scan.nextLine();
                                scan.nextLine();
                            }
                            break;
                        case 1:
                            if (ss.trim().length() == 0)
                            {
                                state = 0;
//                                System.out.print("route : \t");
//                                System.out.println(route);
                                sda.add_route(new Route(routeCount - 1, routeName, route));
                                route.clear();
//                                System.out.println("\n================[END]================");
                            }
                            else
                            {
                                String[] part = ss.split("\t");
                                String[] ft = part[0].split("---");
                                for (String e : ft)
                                {
                                    if (!stationMap.containsKey(e))
                                    {
                                        stationMap.put(e, stationMap.size());
                                        sda.add_station(new Station(stationMap.size() - 1, e));
                                    }
                                }
                                if (route.size() == 0)
                                {
                                    route.add(stationMap.get(ft[0]));
                                }
                                route.add(stationMap.get(ft[1]));
                                sda.add_link(new Link(stationMap.get(ft[0]), stationMap.get(ft[1]),
                                        routeCount - 1, Double.parseDouble(part[1])));
                                //System.out.println(ft[0] + stationMap.get(ft[0]) + "->"
                                //       + ft[1] + stationMap.get(ft[1]) + "\t" + part[1]);
                            }
                            break;
                    }
                }
                if (state != 0)
                {
                    //System.out.print("route : \t");
                    //System.out.println(route);
                    sda.add_route(new Route(routeCount - 1, routeName, route));
                    route.clear();
                    //System.out.println("\n================[END]================");
                }
            } catch (FileNotFoundException e)
            {
                e.printStackTrace();
            }
            System.out.println("==>Parsing complete!");
        }
        else
        {
//            System.out.println("DB [subway] already exist.");
        }
    }

    public static void main(String[] args)
    {
        readAndSave("subway.txt");
    }
}
