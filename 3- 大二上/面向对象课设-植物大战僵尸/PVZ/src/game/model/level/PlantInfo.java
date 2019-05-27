package game.model.level;

public class PlantInfo
{
    private String name;
    private int cost;
    private int cooldown;

    public PlantInfo(String name, int cost, int cooldown)
    {
        this.name = name;
        this.cost = cost;
        this.cooldown = cooldown;
    }

    public String getName()
    {
        return name;
    }

    public int getCost()
    {
        return cost;
    }

    public int getCooldown()
    {
        return cooldown;
    }
}