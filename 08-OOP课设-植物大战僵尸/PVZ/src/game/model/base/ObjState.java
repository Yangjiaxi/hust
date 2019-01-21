package game.model.base;

import java.util.function.BiConsumer;

public class ObjState
{
    private String fName;
    private BiConsumer<GameBoard, Root> action;

    ObjState(String fName, BiConsumer<GameBoard, Root> action)
    {
        this.fName = fName;
        this.action = action;
    }

    public String getfName()
    {
        return fName;
    }

    BiConsumer<GameBoard, Root> getAction()
    {
        return action;
    }
}
