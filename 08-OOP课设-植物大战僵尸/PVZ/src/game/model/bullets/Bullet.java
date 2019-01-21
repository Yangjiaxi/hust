package game.model.bullets;

import game.model.base.Extra;
import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;

public abstract class Bullet extends Root
{
    private int delta;
    private int damage;

    private boolean decelerate = false;

    Bullet()
    {
        // System.out.println("子弹父类被调用");
    }

    void setBulletAt(int x, int row, int bias)
    {
        setX(x);
        setY(row * GameRule.SIZE_Y + bias);
        setRow(row);
    }

    void move()
    {
        x += delta;
    }

    void setDelta(int delta)
    {
        this.delta = delta;
    }

    void setDamage(int damage)
    {
        this.damage = damage;
    }

    void setDeceleration(boolean deceleration)
    {
        this.decelerate = deceleration;
    }

    BiConsumer<GameBoard, Root> getHitAction(int range)
    {
        return ((gameBoard, root) ->
        {
            Bullet bl = (Bullet) root;
            for (Object ob : gameBoard.zombieMap.getRow(bl.getRow()))
            {
                Zombie zb = (Zombie) ob;
                if (zb.getX() - bl.getX() <= range)
                {
                    gameBoard.extraMap.add(new Extra(getPath(), 100, getX(), getY(), true));
                    zb.takeDamage(damage);
                    if (decelerate)
                    {
                        zb.decelerate();
                    }
                    finish = true;
                    return;
                }
            }

        });
    }

    @Override
    protected String getPath()
    {
        return "resource/image/bullet/" + stateTable.get(state).getfName();
    }
}
