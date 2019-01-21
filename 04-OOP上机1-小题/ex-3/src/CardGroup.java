
public class CardGroup
{
    private Card c1;
    private Card c2;
    private Card c3;

    public CardGroup(Card c1, Card c2, Card c3)
    {
        this.c1 = c1;
        this.c2 = c2;
        this.c3 = c3;
    }

    /*
     * Return the number of cards with the same number
     */
    public int numOfSameNumber()
    {
        int num;
        int n1 = c1.getNumber();
        int n2 = c2.getNumber();
        int n3 = c3.getNumber();
        if (n1 == n2 && n2 == n3)
        {
            num = 3;
        }
        else
        {
            if (n1 == n2 || n1 == n3 || n2 == n3)
            {
                num = 2;
            }
            else
            {
                num = 1;
            }
        }
        return num; // to be replaced
    }

    /*
     * Return if all cards in the group are of the same suit.
     */
    public boolean ofSameSuit()
    {
        // TODO 3.3
        String s1 = c1.getSuit();
        String s2 = c2.getSuit();
        String s3 = c3.getSuit();
        return s1.equals(s2) && s2.equals(s3);
    }

    /*
        Get level of this card group,
        decrease from 4 -- of the same suit
                      3 -- 3 cards same number
                      2 -- 2 cards same number
                      1 -- diff number
     */
    public int getGroupLevel()
    {
        if (this.ofSameSuit())
        {
            return 4;
        }
        if (this.numOfSameNumber() == 3)
        {
            return 3;
        }
        if (this.numOfSameNumber() == 2)
        {
            return 2;
        }
        return 1;
    }

    /*
     * Compare if it is bigger than CardGroup c
     * @param c another CardGroup
     * @return true 1 it is bigger than c, 0 equals, -1 smaller than c
     */
    public int compare(CardGroup c)
    {
        int levelThis = this.getGroupLevel();
        int levelC = c.getGroupLevel();
        int levelDiff = levelThis - levelC;
        if (levelDiff == 0)
        {
            return 0;
        }
        else
        {
            return levelDiff / Math.abs(levelDiff);
        }
    }

    @Override
    public String toString()
    {
        return c1.toString() + "\n" + c2.toString() + "\n" + c3.toString();
    }
}
