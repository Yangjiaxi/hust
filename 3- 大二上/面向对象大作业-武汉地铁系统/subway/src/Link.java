public class Link
{
    private int from_id;
    private int to_id;
    private int belong_id;
    private double dist;

    public Link(int from_id, int to_id, int belong_id, double dist)
    {
        this.from_id = from_id;
        this.to_id = to_id;
        this.belong_id = belong_id;
        this.dist = dist;
    }

    public Link()
    {
    }

    public Link reverse()
    {
        return new Link(to_id, from_id, belong_id, dist);
    }

    public int getFrom_id()
    {
        return from_id;
    }

    public void setFrom_id(int from_id)
    {
        this.from_id = from_id;
    }

    public int getTo_id()
    {
        return to_id;
    }

    public void setTo_id(int to_id)
    {
        this.to_id = to_id;
    }

    public int getBelong_id()
    {
        return belong_id;
    }

    public void setBelong_id(int belong_id)
    {
        this.belong_id = belong_id;
    }

    public double getDist()
    {
        return dist;
    }

    public void setDist(double dist)
    {
        this.dist = dist;
    }

    @Override
    public String toString()
    {
        return from_id +
                "->" + to_id +
                " @ " + belong_id +
                " @ " + dist;
    }
}
