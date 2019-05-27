package game.model.level;

import game.model.base.GameRule;

import java.util.ArrayList;
import java.util.HashMap;

class LevelFactory
{
    static Level getLevel(int n)
    {
        Level level = new Level();
        HashMap<String, Integer> zombieCount = new HashMap<>();
        ArrayList<PlantInfo> cards = new ArrayList<>();
        ArrayList<PreSetPlant> pres = new ArrayList<>();
        level.setWaves(10)                                          // -1是默认设置，防止忘记设置而出现逻辑错误
             .setLevelNext(-1)                                      // 默认10波僵尸，可以修改，但推荐10波
             .setDropSunPerSeconds(GameRule.DROP_SUN_PER_SECOND)    // 默认关卡掉落阳光的间隔
             .setPrePlants(pres);                                   // 置空
        switch (n)
        {
        case 1:
            zombieCount.put("normal_zombie", 10);
            cards.add(new PlantInfo("WallNut", 50, 5));
            cards.add(new PlantInfo("Peashooter", 50, 5));
            cards.add(new PlantInfo("Repeater", 100, 10));
            cards.add(new PlantInfo("Chomper", 100, 20));
            cards.add(new PlantInfo("SunFlower", 50, 6));
            cards.add(new PlantInfo("Torchwood", 100, 10));
            level.setLevelNumber(1)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(200)
                 .setLevelNext(2)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5);
            break;
        case 2:
            zombieCount.put("normal_zombie", 10);
            zombieCount.put("conehead_zombie", 3);
            zombieCount.put("buckethead_zombie", 4);
            zombieCount.put("flag_zombie", 4);
            cards.add(new PlantInfo("SunShroom", 50, 2));
            cards.add(new PlantInfo("ScaredyShroom", 50, 2));
            cards.add(new PlantInfo("PuffShroom", 0, 2));
            cards.add(new PlantInfo("WallNut", 50, 2));
            cards.add(new PlantInfo("Repeater", 50, 2));
            cards.add(new PlantInfo("Torchwood", 100, 2));
            level.setLevelNumber(2)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(300)
                 .setLevelNext(3)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundNight)
                 .setLevelBgmusic(GameRule.nightBG)
                 .setDropSun(false);
            break;
        case 3:
            zombieCount.put("normal_zombie", 7);
            zombieCount.put("conehead_zombie", 3);
            zombieCount.put("buckethead_zombie", 4);
            zombieCount.put("newspaper_zombie", 5);
            zombieCount.put("football_zombie", 4);
            cards.add(new PlantInfo("CherryBomb", 100, 2));
            cards.add(new PlantInfo("Jalapeno", 100, 2));
            cards.add(new PlantInfo("PotatoMine", 30, 1));
            cards.add(new PlantInfo("SunShroom", 50, 2));
            level.setLevelNumber(3)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(50)
                 .setLevelNext(4)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundNight)
                 .setLevelBgmusic(GameRule.nightBG)
                 .setDropSun(false);
            break;
        case 4:
            zombieCount.put("normal_zombie", 10);
            zombieCount.put("football_zombie", 5);
            zombieCount.put("buckethead_zombie", 5);
            zombieCount.put("conehead_zombie", 5);
            zombieCount.put("flag_zombie", 5);
            cards.add(new PlantInfo("Peashooter", 100, 2));
            cards.add(new PlantInfo("TallNut", 50, 2));
            cards.add(new PlantInfo("WallNut", 20, 1));
            cards.add(new PlantInfo("SunFlower", 50, 2));
            level.setLevelNumber(4)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(50)
                 .setLevelNext(5)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5);
            break;
        case 5:
            zombieCount.put("normal_zombie", 15);
            zombieCount.put("football_zombie", 10);
            zombieCount.put("buckethead_zombie", 5);
            zombieCount.put("conehead_zombie", 5);
            zombieCount.put("newspaper_zombie", 5);
            zombieCount.put("flag_zombie", 4);
            cards.add(new PlantInfo("Repeater", 50, 2));
            cards.add(new PlantInfo("CherryBomb", 100, 2));
            cards.add(new PlantInfo("PotatoMine", 30, 1));
            cards.add(new PlantInfo("Threepeater", 100, 2));
            cards.add(new PlantInfo("Chomper", 100, 2));
            cards.add(new PlantInfo("TallNut", 50, 2));
            cards.add(new PlantInfo("SunFlower", 50, 2));
            level.setLevelNumber(5)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(50)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5);
            break;
        case 11:
            zombieCount.put("normal_zombie", 10);
            cards.add(new PlantInfo("CherryBomb", 50, 5));
            cards.add(new PlantInfo("Peashooter", 50, 5));
            cards.add(new PlantInfo("Repeater", 100, 10));
            cards.add(new PlantInfo("Jalapeno", 100, 20));
            cards.add(new PlantInfo("SunFlower", 50, 6));
            cards.add(new PlantInfo("Torchwood", 100, 10));
            pres.add(new PreSetPlant("GatlingPea", 0, 0));
            pres.add(new PreSetPlant("GatlingPea", 0, 1));
            pres.add(new PreSetPlant("GatlingPea", 0, 2));
            pres.add(new PreSetPlant("GatlingPea", 0, 3));
            pres.add(new PreSetPlant("GatlingPea", 0, 4));
            pres.add(new PreSetPlant("Repeater", 1, 0));
            pres.add(new PreSetPlant("Repeater", 1, 1));
            pres.add(new PreSetPlant("Repeater", 1, 2));
            pres.add(new PreSetPlant("Repeater", 1, 3));
            pres.add(new PreSetPlant("Repeater", 1, 4));
            pres.add(new PreSetPlant("Peashooter", 2, 0));
            pres.add(new PreSetPlant("Peashooter", 2, 1));
            pres.add(new PreSetPlant("Peashooter", 2, 2));
            pres.add(new PreSetPlant("Peashooter", 2, 3));
            pres.add(new PreSetPlant("Peashooter", 2, 4));
            pres.add(new PreSetPlant("Torchwood", 3, 0));
            pres.add(new PreSetPlant("Torchwood", 3, 1));
            pres.add(new PreSetPlant("Torchwood", 3, 2));
            pres.add(new PreSetPlant("Torchwood", 3, 3));
            pres.add(new PreSetPlant("Torchwood", 3, 4));
            pres.add(new PreSetPlant("SnowPea", 4, 0));
            pres.add(new PreSetPlant("SnowPea", 4, 1));
            pres.add(new PreSetPlant("SnowPea", 4, 2));
            pres.add(new PreSetPlant("SnowPea", 4, 3));
            pres.add(new PreSetPlant("SnowPea", 4, 4));
            pres.add(new PreSetPlant("TallNut", 7, 0));
            pres.add(new PreSetPlant("TallNut", 7, 1));
            pres.add(new PreSetPlant("TallNut", 7, 2));
            pres.add(new PreSetPlant("TallNut", 7, 3));
            pres.add(new PreSetPlant("TallNut", 7, 4));
            level.setLevelNumber(10)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(20)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        case 12:
            zombieCount.put("normal_zombie", 10);
            cards.add(new PlantInfo("CherryBomb", 0, 2));
            cards.add(new PlantInfo("Peashooter", 0, 2));
            cards.add(new PlantInfo("Repeater", 0, 2));
            cards.add(new PlantInfo("Jalapeno", 0, 2));
            cards.add(new PlantInfo("SunFlower", 0, 2));
            cards.add(new PlantInfo("Torchwood", 0, 2));
            pres.add(new PreSetPlant("TwinSunflower", 0, 2));
            pres.add(new PreSetPlant("GatlingPea", 1, 2));
            pres.add(new PreSetPlant("TallNut", 2, 2));
            pres.add(new PreSetPlant("TwinSunflower", 3, 2));
            pres.add(new PreSetPlant("GatlingPea", 4, 2));
            pres.add(new PreSetPlant("TallNut", 5, 2));
            pres.add(new PreSetPlant("TallNut", 6, 2));
            pres.add(new PreSetPlant("TallNut", 7, 2));
            pres.add(new PreSetPlant("Peashooter", 0, 0));
            pres.add(new PreSetPlant("Peashooter", 0, 1));
            pres.add(new PreSetPlant("Repeater", 0, 3));
            pres.add(new PreSetPlant("Repeater", 0, 4));
            pres.add(new PreSetPlant("Chomper", 1, 0));
            pres.add(new PreSetPlant("Chomper", 1, 1));
            pres.add(new PreSetPlant("WallNut", 1, 3));
            pres.add(new PreSetPlant("WallNut", 1, 4));
            pres.add(new PreSetPlant("Torchwood", 2, 0));
            pres.add(new PreSetPlant("Torchwood", 2, 1));
            pres.add(new PreSetPlant("Torchwood", 2, 3));
            pres.add(new PreSetPlant("Torchwood", 2, 4));
            pres.add(new PreSetPlant("SnowPea", 3, 0));
            pres.add(new PreSetPlant("SnowPea", 3, 1));
            pres.add(new PreSetPlant("Jalapeno", 3, 3));
            pres.add(new PreSetPlant("Jalapeno", 3, 4));
            pres.add(new PreSetPlant("PuffShroom", 4, 0));
            pres.add(new PreSetPlant("PuffShroom", 4, 1));
            pres.add(new PreSetPlant("PuffShroom", 4, 3));
            pres.add(new PreSetPlant("PuffShroom", 4, 4));
            pres.add(new PreSetPlant("Threepeater", 5, 0));
            pres.add(new PreSetPlant("Threepeater", 5, 1));
            pres.add(new PreSetPlant("CherryBomb", 5, 3));
            pres.add(new PreSetPlant("CherryBomb", 5, 4));
            pres.add(new PreSetPlant("SunFlower", 6, 0));
            pres.add(new PreSetPlant("SunFlower", 6, 1));
            pres.add(new PreSetPlant("PotatoMine", 6, 3));
            pres.add(new PreSetPlant("PotatoMine", 6, 4));
            pres.add(new PreSetPlant("SunShroom", 7, 0));
            pres.add(new PreSetPlant("SunShroom", 7, 1));
            pres.add(new PreSetPlant("ScaredyShroom", 7, 3));
            pres.add(new PreSetPlant("ScaredyShroom", 7, 4));
            pres.add(new PreSetPlant("TallNut", 8, 0));
            pres.add(new PreSetPlant("TallNut", 8, 1));
            pres.add(new PreSetPlant("TallNut", 8, 2));
            pres.add(new PreSetPlant("TallNut", 8, 3));
            pres.add(new PreSetPlant("TallNut", 8, 4));
            level.setLevelNumber(12)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(300)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundNight)
                 .setLevelBgmusic(GameRule.nightBG)
                 .setDropSun(false)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        case 13:
            zombieCount.put("normal_zombie", 5);
            zombieCount.put("football_zombie", 5);
            zombieCount.put("buckethead_zombie", 5);
            zombieCount.put("conehead_zombie", 5);
            zombieCount.put("newspaper_zombie", 5);
            zombieCount.put("flag_zombie", 5);
            cards.add(new PlantInfo("CherryBomb", 50, 5));
            cards.add(new PlantInfo("Peashooter", 50, 5));
            cards.add(new PlantInfo("Repeater", 100, 10));
            cards.add(new PlantInfo("Jalapeno", 100, 20));
            cards.add(new PlantInfo("SunFlower", 50, 6));
            cards.add(new PlantInfo("Torchwood", 100, 10));
            pres.add(new PreSetPlant("Repeater", 0, 0));
            pres.add(new PreSetPlant("Repeater", 0, 1));
            pres.add(new PreSetPlant("Repeater", 0, 2));
            pres.add(new PreSetPlant("Repeater", 0, 3));
            pres.add(new PreSetPlant("Repeater", 0, 4));
            pres.add(new PreSetPlant("Repeater", 1, 0));
            pres.add(new PreSetPlant("Repeater", 1, 1));
            pres.add(new PreSetPlant("Repeater", 1, 2));
            pres.add(new PreSetPlant("Repeater", 1, 3));
            pres.add(new PreSetPlant("Repeater", 1, 4));
            pres.add(new PreSetPlant("Repeater", 2, 0));
            pres.add(new PreSetPlant("Repeater", 2, 1));
            pres.add(new PreSetPlant("Repeater", 2, 2));
            pres.add(new PreSetPlant("Repeater", 2, 3));
            pres.add(new PreSetPlant("Repeater", 2, 4));
            pres.add(new PreSetPlant("Torchwood", 3, 0));
            pres.add(new PreSetPlant("Torchwood", 3, 1));
            pres.add(new PreSetPlant("Torchwood", 3, 2));
            pres.add(new PreSetPlant("Torchwood", 3, 3));
            pres.add(new PreSetPlant("Torchwood", 3, 4));
            pres.add(new PreSetPlant("SnowPea", 4, 0));
            pres.add(new PreSetPlant("SnowPea", 4, 1));
            pres.add(new PreSetPlant("SnowPea", 4, 2));
            pres.add(new PreSetPlant("SnowPea", 4, 3));
            pres.add(new PreSetPlant("SnowPea", 4, 4));
            pres.add(new PreSetPlant("TallNut", 5, 0));
            pres.add(new PreSetPlant("TallNut", 5, 1));
            pres.add(new PreSetPlant("TallNut", 5, 2));
            pres.add(new PreSetPlant("TallNut", 5, 3));
            pres.add(new PreSetPlant("TallNut", 5, 4));
            level.setLevelNumber(13)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(100)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        case 14:
            zombieCount.put("normal_zombie", 30);
            cards.add(new PlantInfo("CherryBomb", 0, 2));
            cards.add(new PlantInfo("Jalapeno", 0, 2));
            cards.add(new PlantInfo("PotatoMine", 0, 2));
            pres.add(new PreSetPlant("PotatoMine", 5, 0));
            pres.add(new PreSetPlant("PotatoMine", 5, 1));
            pres.add(new PreSetPlant("PotatoMine", 5, 2));
            pres.add(new PreSetPlant("PotatoMine", 5, 3));
            pres.add(new PreSetPlant("PotatoMine", 5, 4));
            level.setLevelNumber(14)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(50)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        case 15:
            zombieCount.put("normal_zombie", 10);
            zombieCount.put("football_zombie", 10);
            zombieCount.put("buckethead_zombie", 10);
            zombieCount.put("conehead_zombie", 10);
            zombieCount.put("newspaper_zombie", 10);
            cards.add(new PlantInfo("CherryBomb", 0, 2));
            cards.add(new PlantInfo("Jalapeno", 0, 2));
            cards.add(new PlantInfo("PotatoMine", 0, 2));
            level.setLevelNumber(15)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(100)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundNight)
                 .setLevelBgmusic(GameRule.nightBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        case 16:
            zombieCount.put("normal_zombie", 10);
            cards.add(new PlantInfo("CherryBomb", 50, 5));
            cards.add(new PlantInfo("Peashooter", 50, 5));
            cards.add(new PlantInfo("Repeater", 100, 10));
            cards.add(new PlantInfo("Jalapeno", 100, 20));
            cards.add(new PlantInfo("SunFlower", 50, 6));
            cards.add(new PlantInfo("Torchwood", 100, 10));
            pres.add(new PreSetPlant("Repeater", 0, 0));
            pres.add(new PreSetPlant("Repeater", 0, 1));
            pres.add(new PreSetPlant("Repeater", 0, 2));
            pres.add(new PreSetPlant("Repeater", 0, 3));
            pres.add(new PreSetPlant("Repeater", 0, 4));
            pres.add(new PreSetPlant("Repeater", 1, 0));
            pres.add(new PreSetPlant("Repeater", 1, 1));
            pres.add(new PreSetPlant("Repeater", 1, 2));
            pres.add(new PreSetPlant("Repeater", 1, 3));
            pres.add(new PreSetPlant("Repeater", 1, 4));
            pres.add(new PreSetPlant("Repeater", 2, 0));
            pres.add(new PreSetPlant("Repeater", 2, 1));
            pres.add(new PreSetPlant("Repeater", 2, 2));
            pres.add(new PreSetPlant("Repeater", 2, 3));
            pres.add(new PreSetPlant("Repeater", 2, 4));
            pres.add(new PreSetPlant("Torchwood", 3, 0));
            pres.add(new PreSetPlant("Torchwood", 3, 1));
            pres.add(new PreSetPlant("Torchwood", 3, 2));
            pres.add(new PreSetPlant("Torchwood", 3, 3));
            pres.add(new PreSetPlant("Torchwood", 3, 4));
            pres.add(new PreSetPlant("SnowPea", 4, 0));
            pres.add(new PreSetPlant("SnowPea", 4, 1));
            pres.add(new PreSetPlant("SnowPea", 4, 2));
            pres.add(new PreSetPlant("SnowPea", 4, 3));
            pres.add(new PreSetPlant("SnowPea", 4, 4));
            pres.add(new PreSetPlant("TallNut", 7, 0));
            pres.add(new PreSetPlant("TallNut", 7, 1));
            pres.add(new PreSetPlant("TallNut", 7, 2));
            pres.add(new PreSetPlant("TallNut", 7, 3));
            pres.add(new PreSetPlant("TallNut", 7, 4));
            level.setLevelNumber(16)
                 .setZombies(zombieCount)
                 .setWaves(10)
                 .setLevelTime(20)
                 .setLevelNext(-1)
                 .setPlantInfos(cards)
                 .setlevelImg(GameRule.backgroundDay)
                 .setLevelBgmusic(GameRule.dayBG)
                 .setDropSun(true)
                 .setDropSunPerSeconds(5)
                 .setPrePlants(pres);
            break;
        }
        return level;
    }
}


