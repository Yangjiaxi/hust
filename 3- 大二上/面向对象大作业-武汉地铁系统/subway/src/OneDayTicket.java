public class OneDayTicket extends Payment
{
    public OneDayTicket()
    {
        this.method = "1日票";
    }

    public double pay(double distance)
    {
        System.out.format("%s 支付 %.3f km\n", this.method, distance);
        return 0.0;
    }
}
