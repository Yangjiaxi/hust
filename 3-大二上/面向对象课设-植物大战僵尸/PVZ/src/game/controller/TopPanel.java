package game.controller;

import game.GameOptions;
import game.model.base.GameRule;
import game.model.level.LevelManager;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;
import game.view.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.HashMap;

public class TopPanel extends JPanel implements Runnable
{

    final private static int INTRO_SCENE = 0;           // 开始界面
    final private static int GAME_SCENE = 1;            // 游戏界面

    private Image img;
    private int state;
    private HashMap<String, JButton> buttonMap;

    private Slot slot;
    private Backyard backyard;

    private Thread timer;
    private int DELAY = GameRule.CONTROLLER_DELAY;

    private LevelManager levelManager;

    TopPanel()
    {
        System.out.println("创建顶层窗口");

        buttonMap = new HashMap<>();
        setPreferredSize(new Dimension(1130, 600));
        setSize(new Dimension(1130, 600));
        setLayout(null);
        img = new ImageIcon("resource/image/background/2.jpg").getImage();
        setVisible(true);
        intro();
    }

    @Override
    public void addNotify()
    {
        super.addNotify();
        timer = new Thread(this);
        timer.start();
    }

    @Override
    public void run()
    {
        long beforeTime, timeDiff, sleep;
        beforeTime = System.currentTimeMillis();
        while (true)
        {
            updateAll();
            repaint();
            timeDiff = System.currentTimeMillis() - beforeTime; //得到因绘制而耽搁的时间，这部分时间从DELAY中扣除
            sleep = DELAY - timeDiff;
            if (sleep < 0)
            {
                sleep = 2;
            }
            try
            {
                Thread.sleep(sleep);
            } catch (InterruptedException e)
            {
                String msg = "游戏暂停";
                JOptionPane.showMessageDialog(this, msg, "暂停", JOptionPane.INFORMATION_MESSAGE);
            }
            beforeTime = System.currentTimeMillis();
        }
    }

    private void updateAll()
    {
        if (state == GAME_SCENE)  // 当游戏没暂停的时候才更新组件
        {
            // backyard.updateAll();
            if (levelManager.getLevelStatus() == 0)
            {
                slot.updateAll();
                String[] zbs = levelManager.call();
                if (zbs != null)
                {
                    // System.out.println(Arrays.toString(zbs));
                    // System.out.println("Map size : " + Zombie.zombieClassMap.size());
                    for (String str : zbs)
                    {
                        // System.out.println("str : " + str);
                        // System.out.println("Object : " + Zombie.zombieClassMap.get(str));
                        backyard.addZombie(Zombie.zombieClassMap.get(str));
                    }
                }
                if (levelManager.getZombiesRemain() <= 0)
                {
                    dialogLevelFinish();
                }
            } else if (levelManager.getLevelStatus() == -1)
            {
                dialogLevelFailed();
            }
        }
    }

    private void dialogLevelFailed()
    {
        Object[] options = new Object[] {"重玩", "主菜单"};
        JFrame jf = new JFrame();
        int optionSelected = JOptionPane.showOptionDialog(jf, "僵尸吃掉了你的脑子!", null, JOptionPane.YES_NO_CANCEL_OPTION,
                JOptionPane.WARNING_MESSAGE, null, options, null);
        backyard.kill();
        if (optionSelected == 0)
        {
            // System.out.println("重玩本关");
            startNewGame(levelManager.getLevelName());
        } else if (optionSelected == 1)
        {
            // System.out.println("进入主菜单");
            intro();
        }
    }

    private void dialogLevelFinish()
    {
        Object[] options = new Object[] {"重玩", "主菜单", "下一关"};
        JFrame jf = new JFrame();
        int optionSelected = JOptionPane.showOptionDialog(jf, "恭喜完成关卡" + levelManager.getLevelName(), null,
                JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, null);
        backyard.kill();
        if (optionSelected == 0)
        {
            // System.out.println("重玩本关");
            startNewGame(levelManager.getLevelName());
        } else if (optionSelected == 1)
        {
            // System.out.println("进入主菜单");
            intro();
        } else if (optionSelected == 2)
        {
            // System.out.println("选择下一关");
            int nextLevel = levelManager.getNextLevel();
            if (nextLevel != -1)
            {
                startNewGame(levelManager.getNextLevel());
            } else
            {
                System.out.println("全部关卡打通");
                JOptionPane.showMessageDialog(jf, "恭喜，您已经完成全部关卡", null, JOptionPane.INFORMATION_MESSAGE);
                intro();
            }
        }
    }

    private void dialogLevelPause()
    {
        Object[] options = new Object[] {"继续游戏", "主菜单"};
        JFrame jf = new JFrame();
        int optionSelected = JOptionPane.showOptionDialog(jf, "游戏暂停" + levelManager.getLevelName(), null,
                JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.INFORMATION_MESSAGE, null, options, null);
        if (optionSelected == 0)
        {
            System.out.println("继续游戏");
            levelManager.gameContinue();
            backyard.gameCountinue();
        } else if (optionSelected == 1)
        {
            System.out.println("进入主菜单");
            intro();
        }
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        if (state == INTRO_SCENE)
        {
            g.drawImage(img, 0, 0, 1130, 600, null);
        }
    }

    private void intro()
    {
        SoundPool.setBGmusic(GameRule.introBG);
        state = INTRO_SCENE;
        removeAll();

        buttonMap.put("btnNewGame", btnMaker("新的游戏", 32));
        buttonMap.put("btnExit", btnMaker("退出游戏", 32));

        buttonMap.put("btnShow_1", btnMaker("普通演示 & 通关", 24));
        buttonMap.put("btnShow_2", btnMaker("所有植物", 24));
        buttonMap.put("btnShow_3", btnMaker("所有僵尸", 24));
        buttonMap.put("btnShow_4", btnMaker("爆炸效果", 24));
        buttonMap.put("btnShow_5", btnMaker("小推车 & 游戏失败", 24));
        buttonMap.put("btnShow_6", btnMaker("音频池", 24));

        buttonMap.put("btnSound", btnMaker("音效:关闭", 16));
        buttonMap.put("btnBGM", btnMaker("音乐:关闭", 16));

        add(buttonMap.get("btnSound"));
        Dimension sz = buttonMap.get("btnSound").getPreferredSize();
        buttonMap.get("btnSound").setBounds(getWidth() - 150, getHeight() - 200, sz.width, sz.height);
        buttonMap.get("btnSound").addActionListener(e ->
        {
            if (GameOptions.SOUND_EFFECT)
            {
                GameOptions.SOUND_EFFECT = false;
                buttonMap.get("btnSound").setText("音效:关闭");
            } else
            {
                GameOptions.SOUND_EFFECT = true;
                buttonMap.get("btnSound").setText("音效:开启");

            }
        });

        add(buttonMap.get("btnBGM"));
        sz = buttonMap.get("btnBGM").getPreferredSize();
        buttonMap.get("btnBGM").setBounds(getWidth() - 150, getHeight() - 100, sz.width, sz.height);
        buttonMap.get("btnBGM").addActionListener(e ->
        {
            if (GameOptions.BACKGROUND_MUSIC)
            {
                GameOptions.BACKGROUND_MUSIC = false;
                SoundPool.turnDown();
                buttonMap.get("btnBGM").setText("音乐:关闭");
            } else
            {
                GameOptions.BACKGROUND_MUSIC = true;
                SoundPool.setBGmusic(GameRule.introBG);
                buttonMap.get("btnBGM").setText("音乐:开启");

            }
        });
        add(buttonMap.get("btnNewGame"));
        add(buttonMap.get("btnExit"));

        for (int i = 1; i <= 6; i++)
        {
            add(buttonMap.get("btnShow_" + i));
        }

        for (int i = 1; i <= 6; i++)
        {
            sz = buttonMap.get("btnShow_" + i).getPreferredSize();
            buttonMap.get("btnShow_" + i).setBounds(0, i * 80, sz.width, sz.height);
            int finalI = i;
            buttonMap.get("btnShow_" + i).addActionListener(e -> startNewGame(finalI + 10));
        }

        centerComp(buttonMap.get("btnNewGame"), 250);
        centerComp(buttonMap.get("btnExit"), 350);

        buttonMap.get("btnNewGame").addActionListener(e -> startNewGame(1));
        buttonMap.get("btnExit").addActionListener(e -> System.exit(0));
    }

    private JButton btnMaker(String text, int f_size)
    {
        JButton res = new JButton(text);
        Font ft = new Font("黑体", Font.PLAIN, f_size);
        res.setFont(ft);
        res.setMargin(new Insets(20, 20, 20, 20));
        return res;
    }

    private void centerComp(Component cp, int y)
    {
        Dimension size = cp.getPreferredSize();
        cp.setBounds(getWidth() / 2 - size.width / 2, y, size.width, size.height);
    }

    private void startNewGame(int startLevel)
    {
        removeAll();
        buttonMap.clear();
        repaint();
        setLayout(null);
        levelManager = new LevelManager(startLevel);
        slot = new Slot(levelManager);
        backyard = new Backyard(levelManager);
        add(slot);
        add(backyard);
        slot.setBounds(0, 0, 200, 600);
        backyard.setBounds(200, 0, 1130 - 200, 600);

        state = GAME_SCENE;

        slot.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mousePressed(MouseEvent e)
            {
                super.mousePressed(e);
                backyard.setMoveImg(slot.checkClick(e.getX(), e.getY()));
            }
        });

        backyard.addMouseListener(new MouseAdapter()
        {
            @Override
            public void mousePressed(MouseEvent e)
            {
                super.mousePressed(e);

                int rx = e.getX();
                int ry = e.getY();
                int ix = (rx - GameRule.CORNER_X) / GameRule.SIZE_X;
                int iy = (ry - GameRule.CORNER_Y) / GameRule.SIZE_Y;
                // System.out.println(ix + " : " + iy);
                // backyard.addZombieTo(iy);
                if (backyard.getMoveImg() != null)
                {
                    if (backyard.canPlace(ix, iy))
                    {
                        backyard.addPlant(slot.placeConfirm(ix, iy));
                        backyard.setMoveImg(null);
                    }
                } else
                {
                    // System.out.println("Check Sun");
                    int res = backyard.hasSun(rx, ry);
                    // System.out.println("Get : " + res);
                    if (res != 0)
                    {
                        slot.addSun(res);
                    } else
                    {
                        if (backyard.checkPause(rx, ry))
                        {
                            dialogLevelPause();
                        }
                    }
                }
            }
        });
    }
}
