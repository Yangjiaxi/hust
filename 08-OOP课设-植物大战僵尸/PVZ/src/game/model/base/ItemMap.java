package game.model.base;

import java.util.concurrent.CopyOnWriteArrayList;

public class ItemMap<T extends Root>
{
    private CopyOnWriteArrayList<CopyOnWriteArrayList<T>> itemMap;

    ItemMap(int n)
    {
        itemMap = new CopyOnWriteArrayList<>();
        for (int i = 0; i < n; i++)
        {
            itemMap.add(new CopyOnWriteArrayList<>());
        }
    }

    public CopyOnWriteArrayList<T> getRow(int row)
    {
        return itemMap.get(row);
    }

    public void add(T obj)
    {
        itemMap.get(obj.getRow()).add(obj);
    }

}
