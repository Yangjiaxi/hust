
public class Card
{
    private int number;
    private String suit; // Heart, Spade, Diamond, Club

    public Card(int n, String s)
    {
        // TODO 3.1
        this.number = n;
        this.suit = s;
    }

    public int getNumber()
    {
        return number;
    }

    public void setNumber(int number)
    {
        this.number = number;
    }

    public String getSuit()
    {
        return suit;
    }

    public void setSuit(String suit)
    {
        this.suit = suit;
    }

    @Override
    public String toString()
    {
        return String.format("Card { number = %2d, suit = %7s }", number, suit);
    }
}
