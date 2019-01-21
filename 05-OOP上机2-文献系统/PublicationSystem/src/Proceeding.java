public class Proceeding extends Publication
{
    private String bookTitle;

    public Proceeding()
    {

    }

    public Proceeding(String title,
                      String authors,
                      String pages,
                      int years,
                      String bookTitle)
    {
        super(title, authors, pages, years);
        this.bookTitle = bookTitle;
    }

    public void setBookTitle(String bookTitle)
    {
        this.bookTitle = bookTitle;
    }

    public String getBookTitle()
    {
        return bookTitle;
    }

    public void showAPA()
    {
        System.out.println(this.getAuthors() + ".(" + this.getYears() + ")."
                + this.getTitle() + "." + this.getBookTitle() + "." + this.getPages());
    }

    @Override
    public String toString()
    {
        return "Proceeding{\n" +
                super.toString() +
                "\nbookTitle='" + bookTitle + '\'' +
                '}';
    }
}
