package game.model.level;

import game.model.base.GameRule;

import java.util.ArrayList;
import java.util.Arrays;

public class LevelManager
{
    private Level currentLevel;
    private int callCount;      // 计数器，统计被调用次数，到一定程度就会返回僵尸
    private int generatePerCall;
    private int wave;
    private int zombiesAlive;
    private int levelStatus = 0;    // 关卡状态，0:游戏中，-1:关卡失败, 1:游戏暂停

    /*
        原理：LevelManager类由TopPanel承载，
            当处于游戏视图时，TopPanel会定时询问LevelManager，
            LevelManager负责返回是否应该加入僵尸，
            LevelManager的每levelTime / 10加入一次僵尸，
            一次加入僵尸的10%，僵尸逐个加入，中间有间隔，
            TopPanel得到僵尸后，给Backyard类加入僵尸，
            加入的原则是在僵尸当前总HP最少的行上加入这个僵尸
     */
    public LevelManager(int level)
    {
        currentLevel = LevelFactory.getLevel(level);
        callCount = 0;
        generatePerCall = currentLevel.getLevelTime() * GameRule.CONTROLLER_RARE / currentLevel.getWaves();
        wave = 0;
        zombiesAlive = currentLevel.getZombieCount();
    }

    public void levelFailed()
    {
        levelStatus = -1;
    }

    public void gamePause()
    {
        levelStatus = 1;
    }

    public void gameContinue()
    {
        levelStatus = 0;
    }

    public int getLevelStatus()
    {
        return levelStatus;
    }

    public String[] call()
    {
        if (wave <= 9)
        {
            callCount++;
            String[] res = null;
            if (callCount % generatePerCall == 0)
            {
                res = currentLevel.getRandomZombies(wave++);
                // System.out.println(Arrays.toString(res));
            }
            return res;
        } else
        {
            // System.out.println("游戏结束");
            return null;
        }
    }

    public void zombieDeath()
    {
        zombiesAlive--;
    }

    public int getNextLevel()
    {
        return currentLevel.getLevelNext();
    }

    public boolean shouldDropSun()
    {
        return currentLevel.isDropSun();
    }

    public ArrayList<PreSetPlant> getPrePlants()
    {
        return currentLevel.getPrePlants();
    }

    public int getSunDropInterval()
    {
        return currentLevel.getDropSunPerSeconds();
    }

    public String getLevelBGmusic()
    {
        return currentLevel.getLevel_bgmusic();
    }

    public String getLevelImg()
    {
        return currentLevel.getLevel_img();
    }

    public int getLevelName()
    {
        return currentLevel.getLevelNumber();
    }

    public ArrayList<PlantInfo> getPlants()
    {
        return currentLevel.getPlantInfos();
    }

    public int getZombiesRemain()
    {
        return zombiesAlive;
    }

    private void test()
    {
        System.out.println("僵尸总数 : " + currentLevel.getZombieCount());
        System.out.println("中间每波 : " + currentLevel.getZombieCount() / currentLevel.getWaves());
        for (int wave = 0; wave < currentLevel.getWaves(); wave++)
        {
            System.out.println(Arrays.toString(currentLevel.getRandomZombies(wave)));
        }
    }

    public static void main(String[] args)
    {
        LevelManager lm = new LevelManager(2);
        lm.test();
    }

}
