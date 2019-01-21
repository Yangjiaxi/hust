import java.util.ArrayList;

public class Route implements Comparable<Route>
{
    private int id;
    private String name;
    private ArrayList<Integer> path;

    public Route(int id, String name, ArrayList<Integer> path)
    {
        this.id = id;
        this.name = name;
        this.path = path;
    }

    public Route()
    {
    }

    public int getId()
    {
        return id;
    }

    public void setId(int id)
    {
        this.id = id;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public ArrayList<Integer> getPath()
    {
        return path;
    }

    public void setPath(ArrayList<Integer> path)
    {
        this.path = path;
    }

    @Override
    public int compareTo(Route o)
    {

        if (this.getName().length() != o.getName().length())
        {
            return Integer.compare(this.getName().length(), o.getName().length());
        }
        else
        {
            return this.getName().compareTo(o.getName());
        }

    }

    @Override
    public String toString()
    {
        return "Route{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", path=" + path +
                '}';
    }
}
