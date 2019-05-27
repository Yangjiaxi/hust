package game.model.level;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;

public class Level
{
    private int levelNumber;
    private HashMap<String, Integer> zombieCome;
    private int waves;          // 僵尸波数
    private int levelTime;      // 关卡的秒数
    private int levelNext;
    private int zombieRemain;
    private boolean dropSun;
    private int dropSunPerSeconds;
    private ArrayList<PlantInfo> plantInfos;
    private ArrayList<PreSetPlant> pres;

    private int zombieCount;    // 僵尸总数

    private String level_img;
    private String level_bgmusic;

    Level()
    {
    }

    // one line but ugly, I delete it
    // Level(int levelNumber, HashMap<String, Integer> zombieCome, int waves, int levelTime, int levelNext,
    //         ArrayList<PlantInfo> plantInfos, String level_img, String level_bgmusic)
    // {
    //     this.levelNumber = levelNumber;
    //     this.zombieCome = zombieCome;
    //     this.waves = waves;
    //     this.levelTime = levelTime;
    //     this.levelNext = levelNext;
    //     this.plantInfos = plantInfos;
    //     this.level_img = level_img;
    //     this.level_bgmusic = level_bgmusic;
    //     for (HashMap.Entry<String, Integer> ent : zombieCome.entrySet())
    //     {
    //         zombieCount += ent.getValue();
    //     }
    //     zombieCount += 1;
    //     zombieRemain = zombieCount;
    // }

    Level setLevelNumber(int levelNumber)
    {
        this.levelNumber = levelNumber;
        return this;
    }

    public Level setZombies(HashMap<String, Integer> zombieCome)
    {
        this.zombieCome = zombieCome;
        for (HashMap.Entry<String, Integer> ent : zombieCome.entrySet())
        {
            zombieCount += ent.getValue();
        }
        zombieCount += 1;
        zombieRemain = zombieCount;
        return this;
    }

    Level setWaves(int waves)
    {
        this.waves = waves;
        return this;
    }

    Level setLevelTime(int levelTime)
    {
        this.levelTime = levelTime;
        return this;
    }

    Level setLevelNext(int levelNext)
    {
        this.levelNext = levelNext;
        return this;
    }

    Level setDropSun(boolean dropSun)
    {
        this.dropSun = dropSun;
        return this;
    }

    Level setPlantInfos(ArrayList<PlantInfo> plantInfos)
    {
        this.plantInfos = plantInfos;
        return this;
    }

    Level setlevelImg(String level_img)
    {
        this.level_img = level_img;
        return this;
    }

    Level setLevelBgmusic(String level_bgmusic)
    {
        this.level_bgmusic = level_bgmusic;
        return this;
    }

    public ArrayList<PreSetPlant> getPrePlants()
    {
        return pres;
    }

    public Level setPrePlants(ArrayList<PreSetPlant> pres)
    {
        this.pres = pres;
        return this;
    }

    int getDropSunPerSeconds()
    {
        return dropSunPerSeconds;
    }

    Level setDropSunPerSeconds(int dropSunPerSeconds)
    {
        this.dropSunPerSeconds = dropSunPerSeconds;
        return this;
    }

    private String getRandom()
    {
        String[] keys = zombieCome.keySet().toArray(new String[0]);
        Random rand = new Random();
        int idx = rand.nextInt(zombieRemain);
        String randomKey = null;
        for (String key : keys)
        {
            idx -= zombieCome.get(key);
            if (idx <= 0)
            {
                randomKey = key;
                break;
            }
        }
        return randomKey;
    }

    private void letOut(String name)
    {
        zombieCome.merge(name, 1, (a, b) -> a - b);
        // System.out.println(name + " 剩余 " + zombieCome.get(name) + " 总剩余 " + zombieRemain);
        if (zombieCome.get(name) <= 0)
        {
            zombieCome.remove(name);
        }
        zombieRemain--;
    }

    String[] getRandomZombies(int wave)
    {
        ArrayList<String> res = new ArrayList<>();
        if (wave == 0)  // 第一波
        {
            letOut("normal_zombie");
            res.add("normal_zombie");
        } else if (1 <= wave && wave <= waves - 2)  // 中间
        {
            for (int i = 0; i < zombieCount / waves; i++)
            {
                String name = getRandom();
                letOut(name);
                res.add(name);
            }
        } else      // 最后一波
        {
            res.add("flag_zombie");
            zombieRemain--;
            int tmp = zombieRemain;
            for (int i = 0; i < tmp; i++)
            {
                String name = getRandom();
                letOut(name);
                res.add(name);
            }
        }
        return res.toArray(new String[] {});
    }

    boolean isDropSun()
    {
        return dropSun;
    }

    int getWaves()
    {
        return waves;
    }

    int getLevelNumber()
    {
        return levelNumber;
    }

    int getLevelNext()
    {
        return levelNext;
    }

    int getLevelTime()
    {
        return levelTime;
    }

    String getLevel_img()
    {
        return level_img;
    }

    String getLevel_bgmusic()
    {
        return level_bgmusic;
    }

    ArrayList<PlantInfo> getPlantInfos()
    {
        return plantInfos;
    }

    public HashMap<String, Integer> getzombieCome()
    {
        return zombieCome;
    }

    int getZombieCount()
    {
        return zombieCount;
    }
}
