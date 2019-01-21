package game.model.zombies;

import game.model.base.DownGrade;
import game.model.base.Extra;
import game.model.base.GameRule;

public class ConeheadZombie extends Zombie implements DownGrade
{
    public ConeheadZombie(Integer x, Integer y)
    {
        // System.out.println("构造路障僵尸!");
        setName("conehead_zombie");
        setMaxHp(640 - 270); // 实际上是头上的宝贝的HP
        setDamage(5);
        setDelta(2);
        setAttackPerTicks(10);
        setHitSoundList(GameRule.pea_hit_plastic);
        load_img();
        zombieSetAt(x, y);
    }

    protected void setStateTable()
    {
        /*
           0 : 待机态，未出场
           1 : 路障行走
           2 : 路障攻击
           3 : 转换为普通僵尸
           4 : 被炸死
        */
        addState(0, "waiting.gif", null);
        addState(1, "walking.gif", (gameBoard, root) -> move());
        addState(2, "attacking.gif", getAttackAction(20));
        addState(3, null, getDownGradeToNormalAction());
        addState(4, null, (gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(boom_die_gif, 3500, getX(), getY()));
        });
    }

    protected void setStateTransfer()
    {
        // (路障的)血量耗尽转换为普通僵尸
        addTransfer(new int[] {1, 2}, 4, (gameBoard, root) -> boom_die);  // 被炸死
        addTransfer(new int[] {1, 2}, 3, (gameBoard, root) -> hp <= 0);   // 本体(路障)hp耗尽，转换为普通僵尸
        addTransfer(1, 2, getAttackTransfer(20));            // 走路    -> 攻击
        addTransfer(2, 1, getAttackTransfer(20).negate());   // 攻击    -> 走路
    }
}
