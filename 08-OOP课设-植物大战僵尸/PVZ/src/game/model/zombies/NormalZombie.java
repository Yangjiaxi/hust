package game.model.zombies;

import game.model.base.Extra;
import game.model.base.GameRule;

public class NormalZombie extends Zombie
{
    public NormalZombie(Integer x, Integer y)
    {
        // System.out.println("构造普通僵尸!");
        setName("normal_zombie");
        setMaxHp(270);
        setDamage(5);
        setDelta(2);
        setAttackPerTicks(10);
        setHitSoundList(GameRule.pea_hit);
        load_img();
        zombieSetAt(x, y);
    }

    public NormalZombie(int x, int y, boolean explict)
    {
        this(x, y);
        setX(x);
    }

    /*
       FSM - 有限状态自动机
           0 : 待机态，未出场
           1 : 有头行走
           2 : 有头攻击
           3 : 无头行走
           4 : 无头攻击
           5 : 被炸死
           6 : 无头死亡(正常死亡)
    */
    protected void setStateTable()
    {
        addState(0, "waiting.gif", null);
        addState(1, "walking.gif", (gameBoard, root) -> move());
        addState(2, "attacking.gif", getAttackAction(20));
        addState(3, "nohead_walking.gif", (gameBoard, root) ->
        {
            move();
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        });

        addState(4, "nohead_attacking.gif", getAttackAction(20).andThen(((gameBoard, root) ->
        {
            if (!head_drop)
            {
                head_drop = true;
                gameBoard.extraMap.add(new Extra(head_drop_file, 1000, getX() + getWidth() / 3, getY()));
            }
        })));

        addState(5, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(boom_die_gif, 3500, getX(), getY()));
        });

        addState(6, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(getPath() + "nohead_die.gif", 1500, getX(), getY()));
        });
    }

    protected void setStateTransfer()
    {
        /*
            状态转换表：优先级最高：转换为死亡
            一般来说，僵尸的状态转换只在两种情况下进行
                1. 僵尸的HP降到0以下，执行死亡
                2. 僵尸的前方一格出现变化，执行动作
                    没有进攻时 -> 前方一格判定有植物，开始攻击
                    进攻时 -> 前方一格不再有植物，停止攻击，进入行走状态
         */

        addTransfer(new int[] {1, 2, 3, 4}, 5, (gameBoard, root) -> boom_die); // 被炸死
        addTransfer(new int[] {3, 4}, 6, (gameBoard, root) -> hp <= 0);  // 无头情况下中弹致死
        addTransfer(1, 2, getAttackTransfer(20));            // 走路    -> 攻击
        addTransfer(2, 1, getAttackTransfer(20).negate());   // 攻击    -> 走路
        addTransfer(1, 3, (gameBoard, root) -> hp <= 70);             // 走路    -> 无头走路
        addTransfer(2, 4, (gameBoard, root) -> hp <= 70);             // 攻击    -> 无头攻击
        addTransfer(3, 4, getAttackTransfer(20));            // 无头走路 -> 无头攻击
        addTransfer(4, 3, getAttackTransfer(20).negate());   // 无头攻击 -> 无头走路
    }
}
