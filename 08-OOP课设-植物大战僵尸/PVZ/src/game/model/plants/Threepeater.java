package game.model.plants;

import game.model.base.GameRule;
import game.model.base.ItemMap;
import game.model.bullets.BeanBullet;
import game.model.base.GameBoard;
import game.model.base.Root;
import game.model.sound.SoundPool;

import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public class Threepeater extends Plant
{
    public Threepeater(Integer x, Integer y)
    {
        // System.out.println("创建三发射手");
        setName("threepeater");
        setMaxHp(300);
        setAttackPerTicks(15);
        load_img();
        plantSetAt(x, y);
        //  System.out.println("Create :" + W + ", " + H);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 攻击
        // 2 : HP耗尽

        BiConsumer<GameBoard, Root> attack = ((gameBoard, root) ->
        {
            if ((intervalCount++) % attackPerTicks == 0)
            {
                for (int i = Math.max(0, root.getRow() - 1); i <= Math.min(4, root.getRow() + 1); i++)
                {
                    gameBoard.bulletMap.getRow(i).add(new BeanBullet(root.getX() + root.getWidth() / 2, i, 30));
                }
                SoundPool.addSound(GameRule.choice(GameRule.pea_shoot));
            }
        });
        addState(0, "threepeater.gif", null);
        addState(1, "threepeater.gif", attack);
        addState(2, "threepeater.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        BiPredicate<GameBoard, Root> canShoot = (gameBoard, root) ->
        {
            ItemMap negMap = gameBoard.zombieMap;
            for (int i = Math.max(0, root.getRow() - 1); i <= Math.min(4, root.getRow() + 1); i++)
            {
                for (Object ob : negMap.getRow(i))
                {
                    Root other = (Root) ob;
                    int dis = other.getX() - root.getX();
                    if (dis >= -20 && dis <= MAX_PROBE_RANGE)
                    {
                        return true;
                    }
                }
            }
            return false;
        };
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, canShoot);
        addTransfer(1, 0, canShoot.negate());
    }
}
