package game.model.zombies;

import game.model.base.DownGrade;
import game.model.base.GameRule;

public class BucketheadZombie extends ConeheadZombie implements DownGrade
{
    public BucketheadZombie(Integer x, Integer y)
    {
        super(x, y);
        setName("buckethead_zombie");
        setMaxHp(1100 - 270); // 实际上是头上的宝贝的HP
        setHitSoundList(GameRule.pea_hit_shield);
        load_img();
        // System.out.println(getY() + " : " + getRow() + " : " + getY() / GameRule.SIZE_Y);
    }
}

