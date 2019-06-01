import java.util.Objects;

public class Composer implements Comparable<Composer>
{
    private String name;
    private int count;

    public Composer(String name)
    {
        this.name = name;
        this.count = 1;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public int getCount()
    {
        return count;
    }

    public void inc()
    {
        this.count++;
    }

    public void dec()
    {
        this.count--;
    }

    public boolean equals(Object obj)
    {
        boolean res = false;
        if (obj instanceof Composer)
        {
            Composer o = (Composer) obj;
            res = this.name.equals(o.getName());
        }
        return res;
    }

    @Override
    public int compareTo(Composer o)
    {
        return Integer.compare(o.count, this.count);
    }

    @Override
    public String toString()
    {
        return "Composer{" +
                "name='" + name + '\'' +
                ", count=" + count +
                '}';
    }
}
