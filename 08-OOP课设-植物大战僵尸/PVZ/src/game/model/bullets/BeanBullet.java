package game.model.bullets;

import game.model.base.GameRule;
import game.model.sound.SoundPool;

public class BeanBullet extends Bullet
{
    public BeanBullet(int x, int y, int bias)
    {
        // System.out.println("创建普通豌豆子弹");
        setName("bean_bullet");
        setDelta(10);
        setDamage(20);
        load_img();
        setBulletAt(x, y, bias);
        // System.out.println(x + ", " + y);
    }

    protected void setStateTable()
    {
        // 0 : 飞行
        // 1 : 击中
        // 2 : 出界
        addState(0, "bean.gif", (gameBoard, root) -> move());
        addState(1, "bean_hit.gif", getHitAction(5));
        addState(2, "bean.gif", ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, getAttackTransfer(5));
        addTransfer(0, 2, ((gameBoard, root) -> root.getX() >= MAX_PROBE_RANGE));
    }
}
