package game.model.plants;

public class TallNut extends Plant
{
    private final int MAX_HP = 8000;

    public TallNut(Integer x, Integer y)
    {
        // System.out.println("创建坚果");
        setName("tallnut");
        setMaxHp(MAX_HP);
        load_img();
        plantSetAt(x, y);
        // System.out.println(x + ", " + y);
    }

    protected void setStateTable()
    {
        // 0 : 正常
        // 1 : 稍微损伤
        // 2 : 严重损伤
        // 3 : HP耗尽
        addState(0, "tallnut_0.gif", null);
        addState(1, "tallnut_1.gif", null);
        addState(2, "tallnut_2.gif", null);
        addState(3, "tallnut_2.gif", (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        addTransfer(0, 1, ((gameBoard, root) -> hp <= MAX_HP * 2 / 3));
        addTransfer(1, 2, ((gameBoard, root) -> hp <= MAX_HP / 3));
        addTransfer(2, 3, ((gameBoard, root) -> hp <= 0));
    }
}
