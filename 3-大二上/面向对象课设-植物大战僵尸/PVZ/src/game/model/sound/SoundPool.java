package game.model.sound;

import game.GameOptions;

import java.util.HashMap;

public class SoundPool
{
    private static SoundPool self = null;
    private SoundUnit bgmusic = null;
    HashMap<String, Integer> effectCount;

    private SoundPool()
    {
        effectCount = new HashMap<>();
    }

    private void play(String fName, boolean loop)
    {
        SoundUnit cur = new SoundUnit(fName, loop, this);
        if (loop)
        {
            if (bgmusic != null)
            {
                bgmusic.kill();
            }
            bgmusic = cur;
        }
        cur.start();
    }

    static public void turnDown()
    {
        if (self != null)
        {
            self.bgmusic.kill();
        }
    }

    static public void addSound(String fName)
    {
        if (GameOptions.SOUND_EFFECT)
        {
            if (self == null)
            {
                self = new SoundPool();
            }
            if (self.effectCount.containsKey(fName))
            {
                if (self.effectCount.get(fName) < 3)
                {
                    self.effectCount.merge(fName, 1, (a, b) -> a + b);
                    self.play(fName, false);
                }
            } else
            {
                self.effectCount.put(fName, 1);
                self.play(fName, false);
            }
        }
    }

    static public void setBGmusic(String fName)
    {
        if (GameOptions.BACKGROUND_MUSIC)
        {
            if (self == null)
            {
                self = new SoundPool();
            }
            self.play(fName, true);
        }
    }
}