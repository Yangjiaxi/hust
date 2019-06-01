import java.util.ArrayList;

public class Main
{
    public static void showArrList(ArrayList<String> toShow)
    {
        for (String ss : toShow)
        {
            System.out.println(ss);
        }
    }

    public static void main(String[] args)
    {
        Billboard bb = BillParser.readBillboard("wiki_hot_100s.txt");
        //bb.show();
        //showArrList(bb.queryByYear(1960));
        //showArrList(bb.getAllComposers());
        //showArrList(bb.getTopTen());
    }
}
