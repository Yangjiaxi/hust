import java.util.ArrayList;

public class Library
{
    private ArrayList<Author> authors;
    private ArrayList<Publication> publications;

    public Library()
    {
        this.authors = new ArrayList<>();
        this.publications = new ArrayList<>();
    }

    public ArrayList<Author> getAuthors()
    {
        return authors;
    }

    public ArrayList<Publication> getPublications()
    {
        return publications;
    }

    public void addPublication(Publication pbl, ArrayList<Author> athrs)
    {
        if (!publications.contains(pbl))
        {
            publications.add(pbl);
        }
        else
        {
            System.out.println("already contain publications");
        }
        if (athrs != null)
        {
            for (Author aa : athrs)
            {
                if (!authors.contains(aa))
                {
                    authors.add(aa);
                }
            }
        }

    }

    public void showInfo()
    {
        System.out.println("==========[Title]==========");
        for (Publication pub : publications)
        {
            System.out.println(pub.getYears() + "  " + pub.getAuthors());
        }
        System.out.println("===========[End]===========");
    }

    public void showAPA()
    {
        System.out.println("===========[APA]===========");
        for (Publication pub : publications)
        {
            pub.showAPA();
        }
        System.out.println("===========[End]===========");
    }

    public Library query(String cond)
    {
        Library res = new Library();
        for (Publication pub : this.publications)
        {
            if (pub.getAuthors().toLowerCase().contains(cond.toLowerCase())
                    || pub.getTitle().toLowerCase().contains(cond.toLowerCase()))
            {
                res.addPublication(pub, null);
            }
        }
        return res;
    }

    public boolean hasBoth(String name1, String name2)
    {
        Library res = new Library();
        for (Publication pub : this.publications)
        {
            if (pub.getAuthors().toLowerCase().contains(name1.toLowerCase()))
            {
                res.addPublication(pub, null);
            }
        }
        if (!res.isEmpty())
        {
            for (Publication pub : res.publications)
            {
                if (pub.getAuthors().toLowerCase().contains(name2.toLowerCase()))
                {
                    return true;
                }
            }
        }
        return false;
    }

    public boolean isEmpty()
    {
        return this.publications.isEmpty();
    }

    public Library copy()
    {
        Library nn = new Library();
        nn.publications.addAll(this.publications);
        nn.authors.addAll(this.authors);
        return nn;
    }

    public void show()
    {
        for (Publication pub : publications)
        {
            if (pub instanceof Article)
            {
                System.out.println("Article");
            }
            else
            {
                System.out.println("Proceeding");
            }
            System.out.println(pub);
            System.out.println("--------------------------");
        }
        System.out.println("**************************");
        for (Author author : authors)
        {
            System.out.println(author);
            System.out.println("--------------------------");
        }
    }
}
