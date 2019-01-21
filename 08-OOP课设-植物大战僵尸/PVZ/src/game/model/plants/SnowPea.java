package game.model.plants;

import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.bullets.IceBullet;
import game.model.sound.SoundPool;

import java.util.function.BiConsumer;

public class SnowPea extends Plant
{
    public SnowPea(Integer x, Integer y){
        setName("snowpea");
        setMaxHp(300);
        setAttackPerTicks(15);
        load_img();
        plantSetAt(x, y);
    }

    @Override
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
                        .add(new IceBullet(root.getX() + root.getWidth() / 2, root.getRow(), 30));
                SoundPool.addSound(GameRule.choice(GameRule.pea_shoot));
            }
        });
        addState(0, "snowpea.gif", null);
        addState(1, "snowpea.gif", attack);
        addState(2, "snowpea.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, getAttackTransfer(MAX_PROBE_RANGE));
        addTransfer(1, 0, getAttackTransfer(MAX_PROBE_RANGE).negate());
    }
}
