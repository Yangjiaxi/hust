package game.model.plants;

import game.model.base.GameRule;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

public class Chomper extends Plant
{
    private int attack_to_digest = 0; // 攻击->开始消化需要执行攻击gif那么长时间
    private boolean attacked = false;

    private int DIGEST_CD = 42 * GameRule.FRAME_RATE;
    private int digest_count = 0;
    private Zombie zb = null; //要吃的僵尸，用于比较，选最近的吃

    public Chomper(Integer x, Integer y)
    {
        // System.out.println("创建大嘴花");
        setName("chomper");
        setMaxHp(300);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 攻击
        // 2 : 消化
        // 3 : HP耗尽
        addState(0, "chomper.gif", ((gameBoard, root) ->
        {
            attack_to_digest = 0;
            digest_count = 0;
            attacked = false;
            zb = null;
        }));
        addState(1, "chomper_attack.gif", ((gameBoard, root) ->
        {
            if (!attacked)
        {
            Plant pt = (Plant) root;
            for (Object ob : gameBoard.zombieMap.getRow(pt.getRow()))
            {
                Zombie cur = (Zombie) ob;
                int dis = cur.getX() - root.getX();
                if (dis >= -20 && dis <= GameRule.SIZE_X && !cur.isFinish())
                {
                    if (zb == null)
                    {
                        zb = cur;
                    } else if (zb.getX() > cur.getX())
                    {
                        attacked = true;
                        zb = cur;
                    }
                }
            }
        }
            if ((++attack_to_digest) % 7 == 0)
            {
                zb.setFinish();
                SoundPool.addSound(GameRule.chomper_chomp);
            }
        }));

        addState(2, "chomper_digest.gif", ((gameBoard, root) -> digest_count++));
        addState(3, null, ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1, 2}, 3, ((gameBoard, root) -> hp <= 0)); // hp耗尽
        addTransfer(0, 1, getAttackTransfer(GameRule.SIZE_X));  // 准备->攻击
        addTransfer(1, 2, ((gameBoard, root) -> attack_to_digest % 10 == 0));  // 攻击-> 消化
        addTransfer(2, 0, ((gameBoard, root) -> digest_count % DIGEST_CD == 0)); // 消化->准备
    }
}
