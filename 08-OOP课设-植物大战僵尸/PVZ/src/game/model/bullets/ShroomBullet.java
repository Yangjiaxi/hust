package game.model.bullets;

public class ShroomBullet extends Bullet
{
    public ShroomBullet(int x, int y, int bias)
    {
        setName("shroom_bullet");
        setDelta(10);
        setDamage(20);
        load_img();
        setBulletAt(x, y, bias);
    }

    protected void setStateTable()
    {
        // 0 : 飞行
        // 1 : 击中
        // 2 : 出界
        addState(0, "shroom.gif", (gameBoard, root) -> move());
        addState(1, "shroom_hit.gif", getHitAction(5));
        addState(2, "shroom.gif", ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, getAttackTransfer(5));
        addTransfer(0, 2, ((gameBoard, root) -> root.getX() >= MAX_PROBE_RANGE));
    }
}
