package game.model.bullets;

public class FireBullet extends Bullet
{
    public FireBullet(int x, int y, int bias)
    {
        setName("fire_bullet");
        setDelta(10);
        setDamage(40);
        setDeceleration(true);
        load_img();
        setBulletAt(x, y, bias);
    }

    protected void setStateTable()
    {
        // 0 : 飞行
        // 1 : 击中
        // 2 : 出界
        addState(0, "fire_bean.gif", (gameBoard, root) -> move());
        addState(1, "sputtering_fire.gif", getHitAction(5));
        addState(2, "fire_bean.gif", ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, getAttackTransfer(5));
        addTransfer(0, 2, ((gameBoard, root) -> root.getX() >= MAX_PROBE_RANGE));
    }
}
