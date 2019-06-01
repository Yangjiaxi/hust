package game.model.plants;

import game.model.base.GameRule;
import game.model.base.Root;

import java.util.HashMap;

public abstract class Plant extends Root
{

    public static HashMap<String, Class> plantClassMap;

    static
    {
        System.out.println("植物静态构造");
        plantClassMap = new HashMap<>();
        plantClassMap.put("Peashooter", Peashooter.class);
        plantClassMap.put("Repeater", Repeater.class);
        plantClassMap.put("Chomper", Chomper.class);
        plantClassMap.put("WallNut", WallNut.class);
        plantClassMap.put("Torchwood", TorchWood.class);
        plantClassMap.put("SnowPea", SnowPea.class);
        plantClassMap.put("Jalapeno", Jalapeno.class);
        plantClassMap.put("TallNut", TallNut.class);
        plantClassMap.put("PuffShroom", PuffShroom.class);
        plantClassMap.put("Threepeater", Threepeater.class);
        plantClassMap.put("CherryBomb", CherryBomb.class);
        plantClassMap.put("SunFlower", SunFlower.class);
        plantClassMap.put("PotatoMine", PotatoMine.class);
        plantClassMap.put("SunShroom", SunShroom.class);
        plantClassMap.put("ScaredyShroom", ScaredyShroom.class);
        plantClassMap.put("TwinSunflower", TwinSunflower.class);
        plantClassMap.put("GatlingPea", GatlingPea.class);
    }

    Plant()
    {
        // System.out.println("植物父类被调用!");
    }

    void plantSetAt(int x, int y)
    {
        setX(x * GameRule.SIZE_X);
        setY(y * GameRule.SIZE_Y - getHeight() + GameRule.SIZE_Y);
        setRow(y);
    }

    @Override
    protected String getPath()
    {
        String ss = stateTable.get(state).getfName();
        return "resource/image/plant/" + name + "/" + ((ss == null) ? "" : ss);
    }
}
