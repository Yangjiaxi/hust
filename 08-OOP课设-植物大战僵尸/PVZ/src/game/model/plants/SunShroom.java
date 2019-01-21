package game.model.plants;

import game.model.base.GameRule;

public class SunShroom extends Plant
{
    private final static int GENERATE_CD = 10 * GameRule.FRAME_RATE;
    private final static int ENLARGE_CD = 60 * GameRule.FRAME_RATE;
    private int enlarge_time = 0;
    private int cur_time = 0;

    public SunShroom(Integer x, Integer y)
    {
        setName("sunshroom");
        setMaxHp(250);
        load_img();
        plantSetAt(x, y);
    }

    protected void setStateTable()
    {
        // 0 : 小正常
        // 1 : 大正常
        // 2 : 小产生太阳
        // 3 ：大产生太阳
        // 4 : 小死亡
        // 5 ：大死亡
        addState(0, "sunshroom_s.gif", ((gameBoard, root) ->
        {
            enlarge_time++;
            cur_time = (++cur_time) % (GENERATE_CD + 1);
        }));
        addState(1, "sunshroom.gif", ((gameBoard, root) -> cur_time = (++cur_time) % (GENERATE_CD + 1)));
        addState(2, "sunshroom_s.gif",
                ((gameBoard, root) -> gameBoard.sunMap.add(new SunSmall(getX(), getY() - 5, getY() + 5))));
        addState(3, "sunshroom.gif",
                ((gameBoard, root) -> gameBoard.sunMap.add(new Sun(getX(), getY() - 5, getY() + 5))));
        addState(4, "sunshroom_s.gif", (gameBoard, root) -> finish = true);
        addState(5, "sunshroom.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(new int[] {0, 2}, 4, ((gameBoard, root) -> hp <= 0));
        addTransfer(new int[] {1, 3}, 5, ((gameBoard, root) -> hp <= 0));
        addTransfer(0, 2, ((gameBoard, root) -> cur_time == GENERATE_CD));
        addTransfer(2, 0, ((gameBoard, root) -> true));
        addTransfer(0, 1, ((gameBoard, root) -> enlarge_time == ENLARGE_CD));
        addTransfer(1, 3, ((gameBoard, root) -> cur_time == GENERATE_CD));
        addTransfer(3, 1, ((gameBoard, root) -> true));
    }
}
