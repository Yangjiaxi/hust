public class RegularTicket extends Payment
{
    // 计价标准：9公里以内（含9公里）2元/人次，
    // 9-14公里（含14公里）3元/人次，
    // 14公里以上每增加1元可乘坐的里程比上一区段递增2公里，以此类推

    public RegularTicket()
    {
        this.method = "普通支付方式";
    }

    @Override
    public double pay(double distance)
    {
        System.out.format("%s 支付 %.3f km\n", this.method, distance);
        double cost = 2.0;
        int delta = 5;
        distance -= 9;
        while (distance > 0)
        {
            cost += 1;
            distance -= delta;
            delta += 2;
        }
        return cost;
    }

    public static void main(String[] args)
    {
        System.out.println((new RegularTicket()).pay(10));
    }
}
