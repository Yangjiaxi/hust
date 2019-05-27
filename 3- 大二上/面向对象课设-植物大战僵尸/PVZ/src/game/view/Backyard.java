package game.view;

import game.model.base.*;
import game.model.bullets.*;
import game.model.level.LevelManager;
import game.model.plants.*;
import game.model.sound.SoundPool;
import game.model.zombies.*;

import javax.swing.*;
import java.awt.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Random;

public class Backyard extends JPanel implements Runnable
{
    private final int DELAY = GameRule.DELAY;
    private Thread timer;
    private boolean isRunning;

    private GameBoard gameBoard; // 游戏棋盘

    private ImageIcon bg;
    private Image moveImg;

    private LevelManager levelManager;

    private int levelTicksCounter;

    public Backyard(LevelManager lmg)
    {
        this.levelManager = lmg;
        gameBoard = new GameBoard(5);
        setPreferredSize(new Dimension(1400, 600));
        initBoard();
    }

    private void initBoard()
    {
        SoundPool.setBGmusic(levelManager.getLevelBGmusic());
        bg = new ImageIcon(levelManager.getLevelImg());

        levelManager.getPrePlants().forEach(pre -> gameBoard.plantMap.add(pre.makeIt()));

        gameBoard.plantMap.add(new LawnCleaner(-1, 0));
        gameBoard.plantMap.add(new LawnCleaner(-1, 1));
        gameBoard.plantMap.add(new LawnCleaner(-1, 2));
        gameBoard.plantMap.add(new LawnCleaner(-1, 3));
        gameBoard.plantMap.add(new LawnCleaner(-1, 4));
    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        doDrawing(g);
        Toolkit.getDefaultToolkit().sync();
    }

    public void setMoveImg(Image m_img)
    {
        moveImg = m_img;
    }

    public Image getMoveImg()
    {
        return moveImg;
    }

    private void doDrawing(Graphics g)
    {
        Graphics2D g2d = (Graphics2D) g;
        g2d.drawImage(bg.getImage(), -100, 0, this);
        // g2d.drawRect(0, 0, GameRule.CORNER_X, GameRule.CORNER_Y);
        // for (int i = 0; i <= 8; i++)
        // {
        //     for (int j = 0; j <= 4; j++)
        //     {
        //         int x = GameRule.CORNER_X + GameRule.SIZE_X * i;
        //         int y = GameRule.CORNER_Y + GameRule.SIZE_Y * j;
        //         g2d.drawRect(x, y, GameRule.SIZE_X, GameRule.SIZE_Y);
        //     }
        // }

        g2d.setColor(Color.GRAY);
        g2d.fillRect(getWidth() - 100, 0, 100, 50);
        g2d.setFont(new Font(null, Font.BOLD, 24));
        g2d.setColor(Color.WHITE);
        g2d.drawString("暂停", getWidth() - 80, 30);
        if (moveImg != null)
        {
            Point p = getMousePosition();
            if (p != null)
            {
                // System.out.println(p.x + ", " + p.y);
                int w = moveImg.getWidth(null);
                int h = moveImg.getHeight(null);
                g.drawImage(moveImg, p.x - w / 2, p.y - h / 2, w, h, null);
            }
        }

        for (int i = 0; i < 5; i++)
        {
            gameBoard.plantMap.getRow(i).forEach(pt -> drawItem(g2d, pt));
            gameBoard.zombieMap.getRow(i).forEach(zb -> drawItem(g2d, zb));
            gameBoard.bulletMap.getRow(i).forEach(bl -> drawItem(g2d, bl));
            gameBoard.extraMap.forEach(ex -> drawItem(g2d, ex));
            gameBoard.sunMap.forEach(sn -> drawItem(g2d, sn));
        }
    }

    private void drawItem(Graphics2D g2d, Root obj)
    {
        int x = GameRule.CORNER_X + obj.getX();
        int y = GameRule.CORNER_Y + obj.getY();
        // Rectangle2D rect = new Rectangle(x, y, obj.getWidth(), obj.getHeight());
        // g2d.draw(rect);
        g2d.drawImage(obj.getImage(), x, y, this);

    }

    @Override
    public void addNotify()
    {
        super.addNotify();
        timer = new Thread(this);
        isRunning = true;
        timer.start();
    }

    @Override
    public void run()
    {
        long beforeTime, timeDiff, sleep;
        beforeTime = System.currentTimeMillis();
        while (isRunning)
        {
            updateAll();
            timeDiff = System.currentTimeMillis() - beforeTime; // 得到因绘制而耽搁的时间，这部分时间从DELAY中扣除
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
        System.out.println("Backyard 结束");
    }

    public void kill()
    {
        isRunning = false;
    }

    public boolean checkPause(int rx, int ry)
    {
        Rectangle rect = new Rectangle(getWidth() - 100, 0, 100, 50);
        if (rect.contains(rx, ry))
        {
            kill();
            levelManager.gamePause();
            return true;
        }
        return false;
    }

    public void gameCountinue()
    {
        timer = new Thread(this);
        isRunning = true;
        timer.start();
    }

    private void updateAll()
    {
        updatePlants();
        updateBullets();
        updateZombies();
        updateExtras();
        updateSuns();
        repaint();
    }

    private void updateSuns()
    {
        // System.out.println(levelManager.getSunDropInterval());
        // System.out.println(levelTicksCounter);
        if (levelManager.shouldDropSun())
        {
            levelTicksCounter++;
            levelTicksCounter %= (levelManager.getSunDropInterval() * GameRule.FRAME_RATE + 1);
            if (levelTicksCounter == levelManager.getSunDropInterval() * GameRule.FRAME_RATE)
            {
                // System.out.println("随机下降阳光");
                Random rand = new Random();
                gameBoard.sunMap.add(new Sun(rand.nextInt(getWidth()), 0, 300 + rand.nextInt(100) - 50));
            }
        }
        ArrayList<Sun> tmpList = new ArrayList<>();
        for (Sun sn : gameBoard.sunMap)
        {
            sn.action(gameBoard);
            if (sn.isFinish())
            {
                tmpList.add(sn);
            }
        }
        gameBoard.sunMap.removeAll(tmpList);
    }

    private void updateExtras()
    {
        ArrayList<Extra> tmpList = new ArrayList<>();
        for (Extra ex : gameBoard.extraMap)
        {
            if (ex.isFinish())
            {
                tmpList.add(ex);
            }
        }
        gameBoard.extraMap.removeAll(tmpList);
    }

    private void updateBullets()
    {
        ArrayList<Bullet> tmpList = new ArrayList<>();
        for (int i = 0; i < 5; i++)
        {
            for (Bullet bl : gameBoard.bulletMap.getRow(i))
            {
                bl.action(gameBoard);
                if (bl.isFinish())
                {
                    tmpList.add(bl);
                }
            }
            gameBoard.bulletMap.getRow(i).removeAll(tmpList);
        }
    }

    private void updateZombies()
    {
        ArrayList<Zombie> tmpList = new ArrayList<>();
        for (int i = 0; i < 5; i++)
        {
            for (Zombie zb : gameBoard.zombieMap.getRow(i))
            {
                zb.action(gameBoard);
                if (zb.isFinish())
                {
                    if (zb.isBoomDie() || !(zb instanceof DownGrade))
                    {
                        levelManager.zombieDeath();
                    }
                    tmpList.add(zb);
                }
                if (zb.getX() + zb.getWidth() + 150 <= 0)
                {
                    levelManager.levelFailed();
                }
            }
            gameBoard.zombieMap.getRow(i).removeAll(tmpList);
        }
    }

    private void updatePlants()
    {
        ArrayList<Plant> tmpList = new ArrayList<>();
        for (int i = 0; i < 5; i++)
        {
            for (Plant pl : gameBoard.plantMap.getRow(i))
            {
                pl.action(gameBoard);
                if (pl.isFinish())
                {
                    tmpList.add(pl);
                }
            }
            gameBoard.plantMap.getRow(i).removeAll(tmpList);
        }
    }

    public void changeState(int state)
    {
        System.out.println("Change ! " + state);
        for (Zombie zb : gameBoard.zombieMap.getRow(2))
        {
            zb.setState(state);
        }

    }

    public boolean canPlace(int ix, int iy)
    {
        // System.out.println(ix + " : " + iy);
        if (ix < 0 || ix > 8)
        {
            // System.out.println("Out of Bound");
            return false;
        }
        for (Plant pl : gameBoard.plantMap.getRow(iy))
        {
            // System.out.println(pl.getX());
            if (pl.getX() == ix * GameRule.SIZE_X)
            {
                return false;
            }
        }
        return true;
    }

    public int hasSun(int rx, int ry)
    {
        int get;

        rx -= GameRule.CORNER_X;
        ry -= GameRule.CORNER_Y;

        for (Sun sn : gameBoard.sunMap)
        {
            if (sn != null)
            {
                // System.out.println("Click at : " + rx + ", " + ry);
                // System.out.format("%d, %d, %d, %d\n", sn.getX(), sn.getY(), sn.getWidth(), sn.getHeight());
                Rectangle area = new Rectangle(sn.getX(), sn.getY(), sn.getWidth(), sn.getHeight());
                if (area.contains(rx, ry))
                {
                    get = sn.getContain();
                    sn.setFinish();
                    return get;
                }

            }
        }
        return 0;
    }

    public void addZombieTo(int index)
    {
        // System.out.println("Add to " + index);
        Zombie azb = new ConeheadZombie(9, index);
        azb.setState(1);
        gameBoard.zombieMap.add(azb);
    }

    public void addZombie(Class cls)
    {
        // 找到总HP最少的行
        // System.out.println("Name : " + cls.getName());
        ArrayList<Integer> lst = new ArrayList<>();
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < 5; i++)
        {
            int tmp = 0;
            for (Zombie zb : gameBoard.zombieMap.getRow(i))
            {
                tmp += zb.getHp();
            }
            if (min > tmp)
            {
                min = tmp;
                lst.clear();
                lst.add(i);
            } else if (min == tmp)
            {
                lst.add(i);
            }
        }
        // System.out.println("Total : " + lst);
        Random rand = new Random();
        int idx = lst.get(rand.nextInt(lst.size()));
        // System.out.println("Choose : " + idx);
        Constructor cons = null;
        try
        {
            cons = cls.getConstructor(Integer.class, Integer.class);
        } catch (NoSuchMethodException e)
        {
            e.printStackTrace();
        }
        Zombie azb = null;
        try
        {
            azb = (Zombie) cons.newInstance(9, idx);
            azb.setState(1);
        } catch (InstantiationException | IllegalAccessException | InvocationTargetException e)
        {
            e.printStackTrace();
        }
        if (azb == null)
        {
            System.out.println("[Fatal Error] no such class");
            System.exit(-1);
        }
        gameBoard.zombieMap.add(azb);
    }

    public void addPlant(Plant pl)
    {
        gameBoard.plantMap.add(pl);
    }
}
