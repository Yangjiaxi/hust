package game.model.plants;

import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.ItemMap;
import game.model.base.Root;
import game.model.bullets.BeanBullet;
import game.model.bullets.Bullet;
import game.model.bullets.IceBullet;
import game.model.bullets.FireBullet;
import game.model.sound.SoundPool;

import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public class TorchWood extends Plant
{
    public TorchWood(Integer x, Integer y)
    {
        setName("torchwood");
        setMaxHp(400);
        load_img();
        plantSetAt(x, y);
    }

    @Override
    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 转换子弹
        // 2 : HP耗尽
        BiConsumer<GameBoard, Root> change = ((gameBoard, root) ->
        {
            for (Bullet bt : gameBoard.bulletMap.getRow(root.getRow()))
            {
                if (bt.getX() >= root.getX() && bt.getX() < root.getX() + root.getWidth()/3 )  //当子弹经过火炬树桩
                {
                    if (bt instanceof BeanBullet)
                    {
                        bt.setFinish();
                        gameBoard.bulletMap.getRow(root.getRow()).add(new FireBullet(root.getX() , root.getRow(), 30));
                        SoundPool.addSound(GameRule.choice(GameRule.firepea_shoot));
                    }
                    if (bt instanceof IceBullet)
                    {
                        bt.setFinish();
                        gameBoard.bulletMap.getRow(root.getRow()).add(new BeanBullet(root.getX()+ root.getWidth()/3 , root.getRow(), 30));
                    }
                }
            }
        });
        addState(0, "torchwood.gif", null);
        addState(1, "torchwood.gif", change);
        addState(2, "torchwood.gif", (gameBoard, root) -> finish = true);
    }

    @Override
    protected void setStateTransfer()
    {
        BiPredicate<GameBoard, Root> canChange = (gameBoard, root) ->
        {
            ItemMap bulletMap;
            if (root instanceof TorchWood)
            {
                bulletMap = gameBoard.bulletMap;
                for (Object ob : bulletMap.getRow(root.getRow()))
                {
                    Bullet bt = (Bullet) ob;
                    if (bt.getX() > root.getX() && bt.getX() < root.getX() + root.getWidth())
                        return true;
                }
            }
            return false;
        };

        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, canChange);
    }
}
