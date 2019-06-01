public class Song
{
    private String name;
    private String composer;
    private int year;

    public Song(String name, String composer, int year)
    {
        this.name = name;
        this.composer = composer;
        this.year = year;
    }

    public Song(String name)
    {
        this.name = name;
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        this.name = name;
    }

    public String getComposer()
    {
        return composer;
    }

    public void setComposer(String composer)
    {
        this.composer = composer;
    }

    public int getYear()
    {
        return year;
    }

    public void setYear(int year)
    {
        this.year = year;
    }

    public boolean equals(Object obj)
    {
        boolean res = false;
        if (obj instanceof Song)
        {
            Song o = (Song) obj;
            res = this.name.equals(o.getName());
        }
        return res;
    }

    @Override
    public String toString()
    {
        return "Song{" +
                "name='" + name + '\'' +
                ", composer='" + composer + '\'' +
                ", year=" + year +
                '}';
    }
}
