abstract public class Publication implements Comparable<Publication>
{
    private String title;
    private String authors;
    private String pages;
    private int years;


    public Publication()
    {}

    public Publication(String title,
                       String author,
                       String pages,
                       int years)
    {
        this.title = title;
        this.authors = author;
        this.pages = pages;
        this.years = years;
    }

    public String getTitle()
    {
        return title;
    }

    public void setTitle(String title)
    {
        this.title = title;
    }

    public String getAuthors()
    {
        return authors;
    }

    public void setAuthor(String authors)
    {
        this.authors = authors;
    }

    public String getPages()
    {
        return pages;
    }

    public void setPages(String pages)
    {
        this.pages = pages;
    }

    public int getYears()
    {
        return years;
    }

    public void setYears(int years)
    {
        this.years = years;
    }

    @Override
    public int compareTo(Publication o)
    {
        if(this.getYears() != o.getYears())
        {
            return Integer.compare(this.getYears(), o.getYears());
        }
        else
        {
            return this.getAuthors().compareTo(o.getAuthors());
        }
    }


    abstract public void showAPA();

    @Override
    public String toString()
    {
        return "Publication{" +
                "title='" + title + '\'' +
                ", author='" + authors + '\'' +
                ", pages='" + pages + '\'' +
                ", years=" + years +
                '}';
    }
}
