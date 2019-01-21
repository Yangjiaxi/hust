package game.model.zombies;

import game.model.base.Extra;
import game.model.base.GameBoard;
import game.model.base.GameRule;
import game.model.base.Root;
import game.model.bullets.BeanBullet;
import game.model.sound.SoundPool;

import java.util.function.BiConsumer;

public class NewspaperZombie extends Zombie
{
    private boolean nopaper = false;
    private int lostp_time = 0;
    private int time_to_next = (int) (0.80 * GameRule.FRAME_RATE);

    public NewspaperZombie(Integer x, Integer y)
    {
        setName("newspaper_zombie");
        setMaxHp(420);
        setDamage(5);
        setDelta(2);
        setAttackPerTicks(10);
        setHitSoundList(GameRule.pea_hit);
        load_img();
        zombieSetAt(x, y);
    }

    protected void setStateTable()
    {
        /*
           0 : 待机态，未出场
           1 : 正常行走
           2 : 正常攻击
           3 : 失去报纸
           4 : 失去报纸行走
           5 : 失去报纸攻击
           6 : 无头行走
           7 : 无头攻击
           8 : 被炸死
           9 : 无头死亡
        */
        addState(0, "waiting.gif", null);
        addState(1, "walking.gif", (gameBoard, root) ->
        {
            setDelta(2);
            move();
        });
        addState(2, "attacking.gif", getAttackAction(20));
        addState(3, "lostnewspaper.gif", (gameBoard, root) ->
        {
            if (!nopaper)
            {
                nopaper = true;
                SoundPool.addSound(GameRule.newspaper_rarrgh);
            }
            lostp_time++;
        });
        addState(4, "nopaper_walking.gif", (gameBoard, root) ->
        {
            setDelta(5);
            move();
        });
        addState(5, "nopaper_attacking.gif", getAttackAction(20));
        addState(6, "nohp_walking.gif", (gameBoard, root) ->
        {
            move();
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        });
        addState(7, "nohp_attacking.gif", getAttackAction(20).andThen((gameBoard, root) ->
        {
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        }));
        addState(8, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(boom_die_gif, 3500, getX(), getY()));
        });

        addState(9, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(getPath() + "nohp_die.gif", 1500, getX(), getY()));
        });
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {1, 2, 3, 4, 5, 6, 7}, 8, (gameBoard, root) -> boom_die);  // 被炸死
        addTransfer(new int[] {1, 2}, 3, (gameBoard, root) -> hp <= 320);
        addTransfer(3, 4, (gameBoard, root) -> nopaper && lostp_time == time_to_next);
        addTransfer(new int[] {4, 5}, 6, (gameBoard, root) -> hp <= 70);
        addTransfer(new int[] {6, 7}, 9, (gameBoard, root) -> hp <= 0);
        addTransfer(1, 2, getAttackTransfer(20));
        addTransfer(2, 1, getAttackTransfer(20).negate());
        addTransfer(4, 5, getAttackTransfer(20));
        addTransfer(5, 4, getAttackTransfer(20).negate());
        addTransfer(6, 7, getAttackTransfer(20));
        addTransfer(7, 6, getAttackTransfer(20).negate());
    }
}
