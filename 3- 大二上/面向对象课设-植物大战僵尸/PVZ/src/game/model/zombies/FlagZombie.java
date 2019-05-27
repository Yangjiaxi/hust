package game.model.zombies;

public class FlagZombie extends NormalZombie
{
    public FlagZombie(Integer x, Integer y)
    {
        super(x, y);
        setName("flag_zombie");
        load_img();
    }
}
