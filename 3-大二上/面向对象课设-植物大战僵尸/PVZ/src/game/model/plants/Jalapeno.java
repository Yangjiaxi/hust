package game.model.plants;

import game.model.base.Extra;
import game.model.base.GameRule;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

public class Jalapeno extends Plant
{
    private int enlarge_time = 0;
    private int time_to_fire = (int) (0.75 * GameRule.FRAME_RATE);

    public Jalapeno(Integer x, Integer y)
    {
        setName("jalapeno");
        setMaxHp(5000);
        load_img();
        plantSetAt(x, y);
    }

    @Override
    protected void setStateTable()
    {
        //0 变大中
        //1 变成火焰， 消失

        addState(0, "jalapeno.gif", (gameBoard, root) -> enlarge_time++);

        addState(1, "jalapeno_attack.gif", (gameBoard, root) ->
        {
            finish = true;
            //            System.out.println(getPath());
            gameBoard.extraMap.add(new Extra(getPath(), 2000, 0, getY() - (getHeight() - GameRule.SIZE_Y + 10)));
            SoundPool.addSound(GameRule.jalapeno_fire);
            for (Zombie zb : gameBoard.zombieMap.getRow(root.getRow()))
            {
                zb.boomDie();
            }
        });
    }

    @Override
    protected void setStateTransfer()
    {
        addTransfer(0, 1, ((gameBoard, root) -> enlarge_time == time_to_fire));
    }
}
