package game.model.plants;

import game.model.base.*;
import game.model.bullets.BeanBullet;
import game.model.bullets.LawnCleanerBullet;
import game.model.bullets.ShroomBullet;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;

public class LawnCleaner extends Plant {
    public LawnCleaner(Integer x, Integer y)
    {
        // System.out.println("创建豌豆射手");
        setName("lawncleaner");
        setMaxHp(10000);
        load_img();
        plantSetAt(x, y);
        //  System.out.println("Create :" + W + ", " + H);
    }

    protected void setStateTable()
    {
        // 0 : 待着
        // 1 : 冲啊

        addState(0, "lawncleaner.gif", null);

        addState(1, null, (gameBoard, root) ->
        {
            finish = true;
            //            System.out.println(getPath());
            gameBoard.bulletMap.getRow(root.getRow())
                    .add(new LawnCleanerBullet(root.getX() + root.getWidth() / 2, root.getRow(), 30));
            //SoundPool.addSound(GameRule.choice(GameRule.pea_shoot));
        });
    }

    @Override

    protected void setStateTransfer()
    {
        addTransfer(0, 1, getAttackTransfer(10));
    }
}
