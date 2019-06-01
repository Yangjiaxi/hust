package game.model.bullets;

import game.model.base.Extra;
import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public class LawnCleanerBullet extends Bullet {
    public LawnCleanerBullet(int x, int y, int bias)
    {
        // System.out.println("创建普通豌豆子弹");
        setName("lawncleanerbullet");
        setDelta(10);
        setDamage(4000);
        load_img();
        setBulletAt(x, y, bias);
        // System.out.println(x + ", " + y);
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
                    zb.takeDamage(4000);
                    return;
                }
            }

        });
    }

    private BiPredicate<GameBoard, Root> getTrue(){return (gameBoard, root) ->{return true;};}

    protected void setStateTable()
    {
        // 0 : 飞行
        // 1 : 击中
        // 2 : 出界
        addState(0, "lawncleanerbullet.gif", (gameBoard, root) -> move());
        addState(1, "lawncleanerbullet.gif", getHitAction(5));
        addState(2, "lawncleanerbullet.gif", ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, getAttackTransfer(5));
        addTransfer(1, 0, getTrue());
        addTransfer(0, 2, ((gameBoard, root) -> root.getX() >= MAX_PROBE_RANGE));
    }
}
