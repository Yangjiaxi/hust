package game.view;

import game.model.base.GameRule;
import game.model.level.PlantInfo;
import game.model.plants.Plant;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

class Card
{
    private String cardImg;
    private String moveImg;
    private String fName;
    private int cost;
    private int cdTime;
    private double currentTime;
    private boolean canPlace;
    private Constructor constructor;

    static Card make(PlantInfo plantInfo)
    {
        return new Card(plantInfo.getName(), plantInfo.getCost(), plantInfo.getCooldown(),
                Plant.plantClassMap.get(plantInfo.getName()));
    }

    private Card(String fName, int cost, int cdTime, Class cls)
    {
        this.fName = fName;
        this.cardImg = "resource/image/Card/" + fName + ".png";
        this.moveImg = "resource/image/Card/" + fName + ".gif";
        this.cost = cost;
        this.cdTime = cdTime;
        canPlace = false;
        try
        {
            this.constructor = cls.getConstructor(Integer.class, Integer.class);
        } catch (NoSuchMethodException e)
        {
            e.printStackTrace();
        }
    }

    void updateTime()
    {
        // System.out.println(fName + " update!");
        if (!canPlace)
        {
            currentTime += 1.0 / GameRule.CONTROLLER_RARE;
            if (currentTime >= cdTime)
            {
                canPlace = true;
                currentTime = 0;
            }
        }
    }

    void clearCounter()
    {
        canPlace = false;
    }

    String getChargingPercent()
    {
        return String.format("%.1f %%", currentTime * 100.0 / cdTime);
    }

    boolean isCanPlace()
    {
        return canPlace;
    }

    Plant getInstance(int x, int y)
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

    int getCost()
    {
        return cost;
    }

    String getCardImg()
    {
        return cardImg;
    }

    String getMoveImg()

    {
        return moveImg;
    }
}
