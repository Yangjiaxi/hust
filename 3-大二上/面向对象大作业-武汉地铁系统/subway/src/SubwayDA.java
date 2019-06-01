import java.sql.*;
import java.util.ArrayList;

public class SubwayDA {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/subway?useSSL=false";

    private static final String USER_NAME = "USERNAME";
    private static final String PASSWORD = "PASSWORD";

    private Connection conn = null;
    private Statement stmt = null;
    private ResultSet rs = null;

    public void init() {
        Parser.readAndSave("subway.txt");
    }

    public int init_subway() {
        int status = 0;
        try {
            String base = "jdbc:mysql://localhost:3306/?useSSL=false";
            conn = DriverManager.getConnection(base, USER_NAME, PASSWORD);
            stmt = conn.createStatement();
            String sql = "CREATE DATABASE subway";
            stmt.executeUpdate(sql);
            System.out.println("DB subway created!");
            close();
            init_subway_table();
            status = 1;
        } catch (SQLException e) {
            if (e.getErrorCode() == 1007) {
                System.out.println("DB subway already exist!");
                close();
                status = 0;
            } else {
                e.printStackTrace();
            }
        }
        return status;
    }

    private void init_subway_table() {
        open();
        try {
            stmt = conn.createStatement();
            String sql;
            // 1. station表
            sql = "CREATE TABLE station " + "(id INTEGER not NULL, " + " name VARCHAR(255), " + " PRIMARY KEY ( id ))";
            System.out.println("Table station created!");

            // 2. route表
            stmt.executeUpdate(sql);
            sql = "CREATE TABLE route " + "(id INTEGER not NULL, " + " name VARCHAR(255), " + " path VARCHAR(255), "
                    + " PRIMARY KEY ( id ))";
            stmt.executeUpdate(sql);
            System.out.println("Table route created!");

            // 3. link表
            sql = "CREATE TABLE link " + "(from_id INTEGER, " + " to_id INTEGER, " + " belong_id INTEGER, "
                    + " dist DOUBLE)";
            stmt.executeUpdate(sql);
            System.out.println("Table link created!");

        } catch (Exception e) {
            e.printStackTrace();
        }
        close();
    }

    private void open() {
        try {
            conn = DriverManager.getConnection(DB_URL, USER_NAME, PASSWORD);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void close() {
        try {
            if (rs != null) {
                rs.close();
            }
        } catch (Exception ignored) {
        }
        try {
            if (stmt != null) {
                stmt.close();
            }
        } catch (Exception ignored) {
        }
        try {
            if (conn != null) {
                conn.close();
            }
        } catch (Exception ignored) {
        }
    }

    private int execUpdate(String sql) {
        open();
        int status = 0;
        try {
            stmt = conn.createStatement();
            status = stmt.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
        }
        close();
        return status;
    }

    private ResultSet execQuery(String sql) {
        open();
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sql);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return rs;
    }

    public int add_station(Station station) {
        String sql = "INSERT INTO station VALUE ('" + station.getId() + "', '" + station.getName() + "')";
        // System.out.println(sql);
        return execUpdate(sql);
    }

    public int add_route(Route route) {
        String ss = route.getPath().toString();
        ss = ss.substring(1, ss.length() - 1);
        ss = ss.replaceAll(" ", "");
        String sql = "INSERT INTO route VALUE ('" + route.getId() + "', '" + route.getName() + "', '" + ss + "')";
        // System.out.println(sql);
        return execUpdate(sql);
    }

    public int add_link(Link link) {
        String sql = "INSERT INTO link VALUE ('" + link.getFrom_id() + "', '" + link.getTo_id() + "', '"
                + link.getBelong_id() + "', '" + link.getDist() + "')";
        // System.out.println(sql);
        return execUpdate(sql);
    }

    public ArrayList<Station> get_station() {
        String sql = "SELECT * FROM station";
        rs = execQuery(sql);
        ArrayList<Station> list = new ArrayList<>();
        try {
            while (rs.next()) {
                Station a = new Station();
                a.setId(rs.getInt("id"));
                a.setName(rs.getString("name"));
                list.add(a);
            }
            close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public ArrayList<Route> get_route() {
        String sql = "SELECT * FROM route";
        rs = execQuery(sql);
        ArrayList<Route> list = new ArrayList<>();
        try {
            while (rs.next()) {
                Route r = new Route();
                r.setId(rs.getInt("id"));
                r.setName(rs.getString("name"));
                String csl = rs.getString("path");
                String[] nodes = csl.split(",");
                ArrayList path = new ArrayList();
                for (String s : nodes) {
                    path.add(Integer.parseInt(s));
                }
                r.setPath(path);
                list.add(r);
            }
            close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    public ArrayList<Link> get_link() {
        String sql = "SELECT * FROM link";
        rs = execQuery(sql);
        ArrayList<Link> list = new ArrayList<>();
        try {
            while (rs.next()) {
                Link l = new Link();
                l.setFrom_id(rs.getInt("from_id"));
                l.setTo_id(rs.getInt("to_id"));
                l.setBelong_id(rs.getInt("belong_id"));
                l.setDist(rs.getDouble("dist"));
                list.add(l);
            }
            close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    // public static void main(String[] args)
    // {
    // SubwayDA sda = new SubwayDA();
    // ArrayList<Station> stations = sda.get_station();
    // for (Station s : stations)
    // {
    // System.out.println(s);
    // }
    // ArrayList<Route> routes = sda.get_route();
    // for (Route s : routes)
    // {
    // System.out.println(s);
    // }
    // ArrayList<Link> links = sda.get_link();
    // for (Link s : links)
    // {
    // System.out.println(s);
    // }
    // }
}
