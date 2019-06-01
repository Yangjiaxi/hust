public class Article extends Publication
{
    private String journal;
    private int volume;
    private int number;

    public Article()
    {

    }

    public Article(String title,
                   String authors,
                   String pages,
                   int years,
                   String journal,
                   int volume,
                   int number)
    {
        super(title, authors, pages, years);
        this.journal = journal;
        this.volume = volume;
        this.number = number;
    }

    public String getJournal()
    {
        return journal;
    }

    public void setJournal(String journal)
    {
        this.journal = journal;
    }

    public int getVolume()
    {
        return volume;
    }

    public void setVolume(int volume)
    {
        this.volume = volume;
    }

    public int getNumber()
    {
        return number;
    }

    public void setNumber(int number)
    {
        this.number = number;
    }

    @Override
    public void showAPA()
    {
        System.out.println(this.getAuthors() + ".(" + this.getYears() + ")."
                + this.getTitle() + "." + this.getJournal() + "." + this.getVolume() +
                "(" + this.getNumber() + ")." + this.getPages());
    }

    @Override
    public String toString()
    {
        return "Article{\n" +
                super.toString() +
                "\njournal='" + journal + '\'' +
                ", volume=" + volume +
                ", number=" + number +
                '}';
    }
}
