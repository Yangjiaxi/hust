package game.model.plants;

import game.model.base.GameRule;

public class SunFlower extends Plant
{
    private final static int GENERATE_CD = 10 * GameRule.FRAME_RATE;
    private int cur_time = 0;

    public SunFlower(Integer x, Integer y)
    {
        setName("sunflower");
        setMaxHp(300);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 产生太阳
        // 2 : 死亡
        addState(0, "SunFlower.gif", ((gameBoard, root) -> cur_time = (++cur_time) % (GENERATE_CD + 1)));
        addState(1, "SunFlower.gif",
                ((gameBoard, root) -> gameBoard.sunMap.add(new Sun(getX(), getY() - 5, getY() + 5))));
        addState(2, "SunFlower.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 1}, 2, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 1, ((gameBoard, root) -> cur_time == GENERATE_CD));
        addTransfer(1, 0, ((gameBoard, root) -> true));
    }
}
