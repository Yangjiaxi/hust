public class WuhanCard extends RegularTicket
{
    public WuhanCard()
    {
        this.method = "武汉通支付方式";
    }

    @Override
    public double pay(double distance)
    {
        return 0.9 * super.pay(distance);
    }

    public static void main(String[] args)
    {
        System.out.println((new WuhanCard()).pay(10));
    }
}
