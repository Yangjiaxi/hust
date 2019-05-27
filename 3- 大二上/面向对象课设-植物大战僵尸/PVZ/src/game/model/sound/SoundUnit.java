package game.model.sound;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.File;

public class SoundUnit extends Thread
{

    private volatile boolean isRunning = true;
    private Clip clip = null;
    private SoundPool parent;
    private boolean loop;
    private String fName;

    SoundUnit(String fName, boolean loop, SoundPool parent)
    {
        this.fName = fName;
        this.parent = parent;
        this.loop = loop;
        try
        {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(new File(fName));
            clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            clip.setFramePosition(0);
            if (loop)
            {
                clip.loop(Clip.LOOP_CONTINUOUSLY);
            }
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void run()
    {
        clip.start();
        while (clip.getMicrosecondLength() != clip.getMicrosecondPosition() && isRunning)
            Thread.onSpinWait();
        clip.stop();
        if (!loop)
        {
            parent.effectCount.merge(fName, 1, (a, b) -> a - b);
            // System.out.println(fName + ", " + parent.effectCount.get(fName));
        }
    }

    void kill()
    {
        isRunning = false;
    }
}

