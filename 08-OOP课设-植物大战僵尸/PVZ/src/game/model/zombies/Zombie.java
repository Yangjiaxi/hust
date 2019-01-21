package game.model.zombies;/*
 * 僵尸抽象类
 */

import game.model.base.GameRule;
import game.model.plants.Plant;
import game.model.base.GameBoard;
import game.model.base.Root;
import game.model.sound.SoundPool;

import java.util.HashMap;
import java.util.function.BiConsumer;

public abstract class Zombie extends Root
{
    public static HashMap<String, Class> zombieClassMap;

    static
    {
        System.out.println("僵尸静态构造");
        zombieClassMap = new HashMap<>();
        zombieClassMap.put("normal_zombie", NormalZombie.class);
        zombieClassMap.put("conehead_zombie", ConeheadZombie.class);
        zombieClassMap.put("buckethead_zombie", BucketheadZombie.class);
        zombieClassMap.put("flag_zombie", FlagZombie.class);
        zombieClassMap.put("football_zombie", FootballZombie.class);
        zombieClassMap.put("newspaper_zombie",NewspaperZombie.class);
    }

    boolean boom_die;
    boolean head_drop;

    final String head_drop_file = "resource/image/zombie/zombie/head_drop.gif";
    final String boom_die_gif = "resource/image/zombie/normal_zombie/boom_die.gif";

    private int delta;  //速度，每一次事件循环行走的像素数
    private int damage;

    public String[] hitSoundList;

    Zombie()
    {
        //System.out.println("僵尸父类被调用！");
        head_drop = false;
    }

    void zombieSetAt(int x, int y)
    {
        setX(x * GameRule.SIZE_X);
        setY(y * GameRule.SIZE_Y - getHeight() + GameRule.SIZE_Y);
        setRow(y);
    }

    public void boomDie()
    {
        boom_die = true;
        finish = true;
    }

    public boolean isBoomDie()
    {
        return boom_die;
    }

    void setDelta(int delta)
    {
        this.delta = delta;
    }

    void setDamage(int damage)
    {
        this.damage = damage;
    }

    void setHitSoundList(String[] stl)
    {
        hitSoundList = stl;
    }

    void playHitSound()
    {
        SoundPool.addSound(GameRule.choice(hitSoundList));
    }

    void move()
    {
        x -= delta;
    }

    public void decelerate()
    {
        this.delta = 1;
    }

    @Override
    protected String getPath()
    {
        String ss = stateTable.get(state).getfName();
        return "resource/image/zombie/" + name + "/" + ((ss == null) ? "" : ss);
    }

    //临时
    public void setState(int state)
    {
        if (state != this.state)
        {
            this.state = state;
            load_img();
        } else
        {
            System.out.println("状态不发生改变");
        }
    }

    BiConsumer<GameBoard, Root> getAttackAction(int range)
    {
        return ((gameBoard, root) ->
        {
            Zombie zb = (Zombie) root;
            for (Object ob : gameBoard.plantMap.getRow(zb.getRow()))
            {
                Plant pt = (Plant) ob;
                if (zb.getX() - pt.getX() <= range)
                {
                    pt.takeDamage(damage);
                    if ((intervalCount++) % attackPerTicks == 0)
                    {
                        SoundPool.addSound(GameRule.choice(GameRule.zombie_eat));
                    }
                    return;
                }
            }
        });
    }

    BiConsumer<GameBoard, Root> getDownGradeToNormalAction()
    {
        return (((gameBoard, root) ->
        {
            root.setFinish();
            Zombie azb = new NormalZombie(getX(), getRow(), true);
            azb.setState(1);
            gameBoard.zombieMap.add(azb);
        }));
    }
}
