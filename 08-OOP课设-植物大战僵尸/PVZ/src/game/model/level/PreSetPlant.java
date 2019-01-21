package game.model.level;

import game.model.plants.Plant;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public class PreSetPlant
{
    private Constructor constructor;
    private int x;
    private int y;

    PreSetPlant(String name, int x, int y)
    {
        this.x = x;
        this.y = y;
        Class cls = Plant.plantClassMap.get(name);
        try
        {
            // System.out.println(name);
            this.constructor = cls.getConstructor(Integer.class, Integer.class);
        } catch (NoSuchMethodException e)
        {
            e.printStackTrace();
        }
    }

    public Plant makeIt()
    {
        Plant pl = null;
        try
        {
            pl = (Plant) constructor.newInstance(x, y);
        } catch (InstantiationException | IllegalAccessException | InvocationTargetException e)
        {
            e.printStackTrace();
        }
        if (pl == null)
        {
            System.out.println("[Fatal Error] no such class");
        }
        return pl;
    }
}
