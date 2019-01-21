package game.model.plants;

import game.model.base.GameRule;

public class Sun extends Plant
{
    private int waiting = 0;
    private int y_to;
    private final int DISAPPEAR_CD = 24 * GameRule.FRAME_RATE;
    int contain;   // 包含多少阳光

    public Sun(int x, int y_from, int y_to)   // size - 阳光的尺寸，0为正常，1为小阳光
    {
        // System.out.println("生成阳光");
        setName("sun");
        this.y_to = y_to;
        setX(x);
        setY(y_from);
        contain = 25;
    }

    protected void setStateTable()
    {
        /*
            阳光状态:
                0. 出场
                1. 下落
                2. 停止下落并等待
                3. 直到等待时间还不拾取，消失
         */
        addState(0, "sun.gif", null);
        addState(1, "sun.gif", ((gameBoard, root) -> y += 2));
        addState(2, "sun.gif", ((gameBoard, root) -> waiting++));
        addState(3, "sun.gif", ((gameBoard, root) -> finish = true));
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, ((gameBoard, root) -> true));
        addTransfer(1, 2, ((gameBoard, root) -> y >= y_to));
        addTransfer(2, 3, ((gameBoard, root) -> waiting >= DISAPPEAR_CD));
    }

    public int getContain()
    {
        return contain;
    }
}
