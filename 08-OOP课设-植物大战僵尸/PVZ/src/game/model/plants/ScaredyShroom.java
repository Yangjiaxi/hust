package game.model.plants;

import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.ItemMap;
import game.model.base.Root;
import game.model.bullets.ShroomBullet;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public class ScaredyShroom extends Plant {
    private boolean attacked = false;
    private Zombie zb = null;

    public ScaredyShroom(Integer x, Integer y)
    {
        setName("scaredyshroom");
        setMaxHp(300);
        setAttackPerTicks(15);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 攻击
        // 2 : 害怕
        // 3 : HP耗尽
        // 4 : 睡眠

        BiConsumer<GameBoard, Root> attack = ((gameBoard, root) ->
        {
            if ((intervalCount++) % attackPerTicks == 0)
            {
                gameBoard.bulletMap.getRow(root.getRow())
                        .add(new ShroomBullet(root.getX() + root.getWidth() / 2, root.getRow(), 50));
            }
        });

        addState(0, "scaredyshroom.gif", ((gameBoard, root) ->
        {
            attacked = false;
            zb = null;
        }));

        addState(1, "scaredyshroom.gif", attack);
        addState(2, "scaredyshroom_cry.gif",null);
        addState(3, "scaredyshroom.gif", (gameBoard, root) -> finish = true);

        //addState(4, "puffshroom_sleep.gif",null);

    }

    protected void setStateTransfer()
    {
        BiPredicate<GameBoard, Root> scaredy = (gameBoard, root) ->
        {
            ItemMap negMap = gameBoard.zombieMap;
            for (int i = Math.max(0, root.getRow() - 1); i <= Math.min(4, root.getRow() + 1); i++)
            {
                for (Object ob : negMap.getRow(i))
                {
                    Root other = (Root) ob;
                    int dis = other.getX() - root.getX();
                    if (dis >= -50 && dis <= 1 * GameRule.SIZE_X)
                    {
                        return true;
                    }
                }
            }
            return false;
        };
        addTransfer(new int[] {0, 1, 2}, 3, ((gameBoard, root) -> hp <= 0)); // hp耗尽
        addTransfer(new int[] {0, 1}, 2, scaredy);//先判断是否缩头
        addTransfer(2, 0, scaredy.negate());//再判断是否露头
        addTransfer(0, 1, getAttackTransfer(MAX_PROBE_RANGE));//再攻击
        addTransfer(1, 0, getAttackTransfer(MAX_PROBE_RANGE).negate());

    }
}
