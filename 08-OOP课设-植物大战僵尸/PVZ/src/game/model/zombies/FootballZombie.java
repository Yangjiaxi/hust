package game.model.zombies;

import game.model.base.DownGrade;
import game.model.base.Extra;
import game.model.base.GameRule;

public class FootballZombie extends Zombie
{
    public FootballZombie(Integer x, Integer y)
    {
        setName("football_zombie");
        setMaxHp(1670);
        setDamage(5);
        setDelta(3);
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
           3 : 失去漂亮帽子行走
           4 : 失去漂亮帽子攻击
           5 : 无头行走
           6 : 无头攻击
           7 : 被炸死
           8 : 无头死亡
        */
        addState(0, "waiting.gif", null);
        addState(1, "walking.gif", (gameBoard, root) -> move());
        addState(2, "attacking.gif", getAttackAction(20));
        addState(3, "noorn_walking.gif",(gameBoard, root) -> move());
        addState(4, "noorn_attacking.gif",getAttackAction(20));
        addState(5,"nohead_walking.gif",(gameBoard, root) ->
        {
            move();
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        });
        addState(6,"nohead_attacking.gif",getAttackAction(20).andThen((gameBoard, root) -> {
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        }));
        addState(7, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(boom_die_gif, 3500, getX(), getY()));
        });

        addState(8, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(getPath() + "nohead_die.gif", 1500, getX(), getY()));
        });
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {1, 2, 3, 4, 5, 6}, 7, (gameBoard, root) -> boom_die);  // 被炸死
        addTransfer(new int[] {1, 2}, 3, (gameBoard, root) -> hp <= 1110);
        addTransfer(new int[] {3, 4}, 5, (gameBoard, root) -> hp <= 550);
        addTransfer(new int[] {5, 6}, 8, (gameBoard, root) -> hp <= 0);
        addTransfer(1, 2, getAttackTransfer(20));
        addTransfer(2, 1, getAttackTransfer(20).negate());
        addTransfer(3, 4, getAttackTransfer(20));
        addTransfer(4, 3, getAttackTransfer(20).negate());
        addTransfer(5, 6, getAttackTransfer(20));
        addTransfer(6, 5, getAttackTransfer(20).negate());

    }
}
