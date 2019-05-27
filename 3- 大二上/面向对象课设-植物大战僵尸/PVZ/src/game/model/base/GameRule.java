package game.model.base;

import java.util.Random;

public class GameRule
{
    final public static int FRAME_RATE = 10;
    final public static int DELAY = 1000 / FRAME_RATE;

    final public static int CONTROLLER_RARE = 25;
    final public static int CONTROLLER_DELAY = 1000 / CONTROLLER_RARE;
    final public static int CORNER_X = 270 - 120;
    final public static int CORNER_Y = 70;
    final public static int SIZE_X = 80;
    final public static int SIZE_Y = 100;

    final public static int DROP_SUN_PER_SECOND = 8;

    final public static String introBG = "resource/sound/bg/intro.wav";
    final public static String chooseSeedBG = "resource/sound/bg/chooseSeed.wav";
    final public static String dayBG = "resource/sound/bg/dayBG.wav";
    final public static String nightBG = "resource/sound/bg/nightBG.wav";

    final public static String backgroundDay = "resource/image/background/bg1.jpg";
    final public static String backgroundNight = "resource/image/background/bg2.jpg";

    final public static String[] pea_shoot = {"resource/sound/effect/pea_shoot_1.wav",
            "resource/sound/effect/pea_shoot_2.wav"};

    final public static String[] pea_hit = {"resource/sound/effect/pea_hit_1.wav",
            "resource/sound/effect/pea_hit_2.wav", "resource/sound/effect/pea_hit_3.wav"};

    final public static String[] firepea_shoot = {"resource/sound/effect/firepea_shoot.wav"};

    final public static String[] firepea_hit = {"resource/sound/effect/firepea_hit_1.wav",
            "resource/sound/effect/firepea_hit_2.wav"};

    final public static String[] pea_hit_plastic = {"resource/sound/effect/pea_hit_plastic_1.wav",
            "resource/sound/effect/pea_hit_plastic_2.wav"};

    final public static String[] pea_hit_shield = {"resource/sound/effect/pea_hit_shield_1.wav",
            "resource/sound/effect/pea_hit_shield_2.wav"};

    final public static String[] zombie_eat = {"resource/sound/effect/zombie_eat_1.wav",
            "resource/sound/effect/zombie_eat_1.wav", "resource/sound/effect/zombie_eat_1.wav"};

    final public static String chomper_chomp = "resource/sound/effect/chomper_chomp.wav";

    final public static String jalapeno_fire = "resource/sound/effect/jalapeno_fire.wav";

    final public static String cherry_bomb = "resource/sound/effect/cherry_bomb.wav";

    final public static String potato_mine = "resource/sound/effect/potato_mine.wav";

    final public static String newspaper_rarrgh = "resource/sound/effect/newspaper_rarrgh.wav";

    public static String choice(String[] strs)
    {
        Random rand = new Random();
        return strs[rand.nextInt(strs.length)];
    }

}
