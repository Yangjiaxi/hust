package game.model.plants;

import game.model.base.Extra;
import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.bullets.BeanBullet;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.concurrent.CopyOnWriteArrayList;
import java.util.function.BiConsumer;

public class CherryBomb extends Plant
{
    private int enlarge_time = 0;
    private int time_to_fire = (int) (0.60 * GameRule.FRAME_RATE);

    public CherryBomb(Integer x, Integer y)
    {
        // System.out.println("创建樱桃炸弹");
        setName("cherrybomb");
        setMaxHp(5000);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 变大中
        // 1 : 爆炸
        addState(0, "cherrybomb.gif", (gameBoard, root) -> enlarge_time++);
        addState(1, "boom.gif", ((gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(getPath(), 2000, getX() - (getWidth() - GameRule.SIZE_X) / 2,
                    getY() - (getHeight() - GameRule.SIZE_Y) / 2));
            SoundPool.addSound(GameRule.cherry_bomb);
            int start_row = Math.max(0, root.getRow() - 1);
            int end_row = Math.min(4, root.getRow() + 1);
            int start_x = Math.max(0, root.getX() - GameRule.SIZE_X - (166 - 112));//166为正常僵尸的宽度，112为樱桃炸弹的宽度
            int end_x = Math.min(GameRule.CORNER_X + 9 * GameRule.SIZE_X, root.getX() + GameRule.SIZE_X);
            for (int i = start_row; i <= end_row; i++)
            {
                for (Object ob : gameBoard.zombieMap.getRow(i))
                {
                    Zombie cur = (Zombie) ob;
                    if (cur.getX() >= start_x && cur.getX() <= end_x)
                    {
                        cur.boomDie();
                    }
                }
            }
        }));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, ((gameBoard, root) -> enlarge_time == time_to_fire));
    }
}
