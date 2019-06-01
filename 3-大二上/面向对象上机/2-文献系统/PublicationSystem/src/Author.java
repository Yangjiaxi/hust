import java.util.Objects;

public class Author
{
    private String firstName;
    private String lastName;

    public Author(String firstName,
                  String lastName)
    {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName()
    {
        return firstName;
    }

    public void setFirstName(String firstName)
    {
        this.firstName = firstName;
    }

    public String getLastName()
    {
        return lastName;
    }

    public void setLastName(String lastName)
    {
        this.lastName = lastName;
    }

    public boolean equals(Object obj)
    {
        boolean res = false;
        if (obj instanceof Author)
        {
            Author o = (Author) obj;
            res = (this.firstName.equals(o.firstName)) & (this.lastName.equals(o.lastName));
        }
        return res;
    }

    @Override
    public String toString()
    {
        return "Author{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                '}';
    }
}
