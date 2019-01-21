package game.model.plants;

import game.model.base.GameRule;
import game.model.bullets.BeanBullet;
import game.model.base.GameBoard;
import game.model.base.Root;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;

public class Peashooter extends Plant
{

    public Peashooter(Integer x, Integer y)
    {
        // System.out.println("创建豌豆射手");
        setName("peashooter");
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
                gameBoard.bulletMap.getRow(root.getRow())
                        .add(new BeanBullet(root.getX() + root.getWidth() / 2, root.getRow(), 30));
                SoundPool.addSound(GameRule.choice(GameRule.pea_shoot));
            }
        });
        addState(0, "peashooter.gif", null);
        addState(1, "peashooter.gif", attack);
        addState(2, "peashooter.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, getAttackTransfer(MAX_PROBE_RANGE));
        addTransfer(1, 0, getAttackTransfer(MAX_PROBE_RANGE).negate());
    }
}
