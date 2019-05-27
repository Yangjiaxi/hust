package game.model.base;

import java.util.function.BiPredicate;

class Transfer
{
    private BiPredicate<GameBoard, Root> condition;
    private int To;

    Transfer(BiPredicate<GameBoard, Root> cond, int to)
    {
        condition = cond;
        To = to;
    }

    BiPredicate<GameBoard, Root> getCondition()
    {
        return condition;
    }

    int getTo()
    {
        return To;
    }
}
