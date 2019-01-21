import java.util.ArrayList;

public class PathPair
{
    private ArrayList<Link> path;
    private double dist;

    public PathPair(ArrayList<Link> path, double dist)
    {
        this.path = path;
        this.dist = dist;
    }

    public ArrayList<Link> getPath()
    {
        return path;
    }

    public void setPath(ArrayList<Link> path)
    {
        this.path = path;
    }

    public double getDist()
    {
        return dist;
    }

    public void setDist(double dist)
    {
        this.dist = dist;
    }
}
