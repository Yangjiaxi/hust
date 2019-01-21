import java.util.ArrayList;
import java.util.Random;

public class Deck
{
    private ArrayList<Card> cards;
    private Random random;

    public Deck()
    {
        this.cards = new ArrayList<>();
        this.random = new Random();

        // create all the cards
        this.generateDeck();
    }

    /*
     * Generate all the cards for a deck
     * the cards are stored in the member variable - cards
     */
    private void generateDeck()
    {
        ArrayList<String> suitList = new ArrayList<>();
        suitList.add("Heart");
        suitList.add("Spade");
        suitList.add("Diamond");
        suitList.add("Club");
        for (int i = 1; i <= 13; i++)
        {
            for (String s : suitList)
            {
                // System.out.format("%d + %s\n", i, s);
                this.cards.add(new Card(i, s));
            }
        }
    }

    /*
     * Return a random card, remove it from the deck
     */
    public Card getRandomCard()
    {
        int index = this.random.nextInt(this.cards.size());
        return this.cards.remove(index);
    }

    /*
     * Create a CardGroup by picking 3 cards randomly
     */
    public CardGroup createRandomCardGroup()
    {
        return new CardGroup(
                getRandomCard(),
                getRandomCard(),
                getRandomCard()); // to be replaced
    }

    static void testGroup(CardGroup item)
    {
        System.out.println(item.toString());
        System.out.println("How many cards are of the same number? [ " + item.numOfSameNumber() + " ]");
        System.out.println("Is all the cards are of the same suit? [ " + item.ofSameSuit() + " ]");
        System.out.println("Level of this group? [ " + item.getGroupLevel() + " ]");
        System.out.println("******************************************************");
    }

    static String getBiggest(CardGroup cg1, CardGroup cg2, CardGroup cg3)
    {
        String big;
        CardGroup bigP;
        int c12 = cg1.compare(cg2);
        if (c12 > 0)
        {
            bigP = cg1;
            big = "cg1";
        }
        else if (c12 == 0)
        {
            bigP = cg1;
            big = "cg1 + cg2";
        }
        else
        {
            bigP = cg2;
            big = "cg2";
        }

        int c3B = cg3.compare(bigP);
        if (c3B == 0)
        {
            big += " + cg3";
        }
        else if (c3B > 0)
        {
            big = "cg3";
        }
        return big;
    }

    public static void main(String[] args)
    {
        Deck deck = new Deck();
        CardGroup cg1 = deck.createRandomCardGroup();
        CardGroup cg2 = deck.createRandomCardGroup();
        CardGroup cg3 = deck.createRandomCardGroup();
        testGroup(cg1);
        testGroup(cg2);
        testGroup(cg3);
        System.out.println("Biggest : " + getBiggest(cg1, cg2, cg3));
    }
}
