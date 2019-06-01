package game.model.plants;

import game.model.base.GameRule;
import game.model.bullets.BeanBullet;
import game.model.base.GameBoard;
import game.model.base.Root;
import game.model.sound.SoundPool;

import java.util.function.BiConsumer;

public class GatlingPea extends Plant
{
    public GatlingPea(Integer x, Integer y)
    {
        // System.out.println("创建双发射手");
        setName("gatlingpea");
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
            if (intervalCount == 0 || intervalCount == 2 || intervalCount == 4 || intervalCount == 6)
            {
                gameBoard.bulletMap.getRow(root.getRow())
                                   .add(new BeanBullet(root.getX() + root.getWidth() / 2, root.getRow(), 30));
                SoundPool.addSound(GameRule.choice(GameRule.pea_shoot));

            }
            intervalCount = (++intervalCount) % attackPerTicks;
        });
        addState(0, "gatlingpea.gif", null);
        addState(1, "gatlingpea.gif", attack);
        addState(2, "gatlingpea.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, getAttackTransfer(MAX_PROBE_RANGE));
        addTransfer(1, 0, getAttackTransfer(MAX_PROBE_RANGE).negate());
    }
}

