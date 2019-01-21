package game.model.plants;

import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.bullets.ShroomBullet;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;

public class PuffShroom extends Plant
{
    private boolean attacked = false;
    private Zombie zb = null;

    public PuffShroom(Integer x, Integer y)
    {
        setName("puffshroom");
        setMaxHp(300);
        setAttackPerTicks(15);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 攻击
        // 2 : HP耗尽
        // 3 : 睡眠

        BiConsumer<GameBoard, Root> attack = ((gameBoard, root) ->
        {
            if ((intervalCount++) % attackPerTicks == 0)
            {
                gameBoard.bulletMap.getRow(root.getRow())
                        .add(new ShroomBullet(root.getX() + root.getWidth() / 2, root.getRow(), 70));
            }
        });

        addState(0, "puffshroom.gif", ((gameBoard, root) ->
        {
            attacked = false;
            zb = null;
        }));
        addState(1, "puffshroom.gif", attack);
        addState(2, "puffshroom.gif", (gameBoard, root) -> finish = true);
        //addState(3, "puffshroom_sleep.gif",null);

    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0)); // hp耗尽
        addTransfer(0, 1, getAttackTransfer(2 * GameRule.SIZE_X));
        addTransfer(1, 0, getAttackTransfer(2 * GameRule.SIZE_X).negate());
    }
}
