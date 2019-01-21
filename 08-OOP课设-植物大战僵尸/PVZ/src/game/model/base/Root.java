package game.model.base;

import game.model.bullets.Bullet;
import game.model.plants.Plant;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public abstract class Root
{
    protected int hp;
    protected int state = 0;
    protected Boolean finish;

    protected String name;
    protected HashMap<Integer, ObjState> stateTable;
    protected int x; // 列(具体坐标)
    protected int y; // 行(具体坐标)
    protected int row; // 行(0,1,2,3,4)
    protected int H;
    protected int W;

    private HashMap<Integer, ArrayList<Transfer>> transferTable;
    protected Image image;

    protected int intervalCount;
    protected int attackPerTicks;

    protected final int MAX_PROBE_RANGE = 1000;

    public Root()
    {
        // System.out.println("根类被调用！");
        stateTable = new HashMap<>();
        transferTable = new HashMap<>();
        finish = false;
        setStateTable();
        setStateTransfer();
    }

    protected void setAttackPerTicks(int pt)
    {
        this.intervalCount = 0;
        this.attackPerTicks = pt;
    }

    protected void setName(String name)
    {
        this.name = name;
    }

    protected void setMaxHp(int hp)
    {
        this.hp = hp;
    }

    public int getHp()
    {
        return hp;
    }

    public boolean isFinish()
    {
        return finish;
    }

    public void setFinish()
    {
        finish = true;
    }

    public synchronized void takeDamage(int damage)
    {
        hp -= damage;
        if (this instanceof Zombie)
        {
            Zombie self = (Zombie) this;
            if (damage == 40) //40是被火焰子弹击中
            {
                SoundPool.addSound(GameRule.choice(GameRule.firepea_hit));
            } else
            {
                SoundPool.addSound(GameRule.choice(self.hitSoundList));
            }
            // System.out.println(hp);
        }
    }

    protected abstract void setStateTable(); // 设置状态表

    protected void addState(int state, String fName, BiConsumer<GameBoard, Root> action)
    {
        stateTable.put(state, new ObjState(fName, action));
    }

    protected abstract void setStateTransfer(); // 设置转移条件

    protected void addTransfer(int from, int to, BiPredicate<GameBoard, Root> cond)
    {
        if (!transferTable.containsKey(from))
        {
            transferTable.put(from, new ArrayList<>());
        }
        transferTable.get(from).add(new Transfer(cond, to));
    }

    protected void addTransfer(int[] froms, int to, BiPredicate<GameBoard, Root> cond)
    {
        for (int from : froms)
        {
            addTransfer(from, to, cond);
        }
    }

    public void action(GameBoard gameBoard)
    {
        ArrayList<Transfer> cur = transferTable.get(state);
        if (cur != null)
        {
            for (Transfer tran : cur)
            {
                boolean res = tran.getCondition().test(gameBoard, this);
                if (res)
                {
                    // System.out.println("条件转移！ -> " + tran.getTo());
                    state = tran.getTo();
                    load_img();
                    break;
                }
            }
        }

        BiConsumer<GameBoard, Root> action = stateTable.get(state).getAction();
        if (action != null)
        {
            action.accept(gameBoard, this);
        }
    }

    protected void setX(int x)
    {
        this.x = x;
    }

    protected void setY(int y)
    {
        this.y = y;
    }

    protected void setRow(int row)
    {
        this.row = row;
    }

    public int getX()
    {
        return x;
    }

    public int getY()
    {
        return y;
    }

    public int getRow()
    {
        return row;
    }

    public int getWidth()
    {
        return W;
    }

    public int getHeight()
    {
        return H;
    }

    public Image getImage()
    {
        return image;
    }

    protected abstract String getPath();

    protected void load_img()
    {
        // String uri = "resource/image/" + name + "/" + stateTable.get(state).getfName();
        String path = getPath();
        // System.out.println(path);
        image = Toolkit.getDefaultToolkit().createImage(path);
        ImageIcon tmp = new ImageIcon(path);
        W = tmp.getIconWidth();
        H = tmp.getIconHeight();
        // System.out.println(W + ", " + H);
    }

    protected BiPredicate<GameBoard, Root> getAttackTransfer(int range)
    {
        return (gameBoard, root) ->
        {
            ItemMap negMap;
            if (root instanceof Zombie) // zombie as root
            {
                negMap = gameBoard.plantMap;
                for (Object ob : negMap.getRow(root.getRow()))
                {
                    Root other = (Root) ob;
                    int dis = other.getX() - root.getX();
                    if (dis >= range && dis <= GameRule.SIZE_X && !other.finish)
                    {
                        return true;
                    }
                }
            } else if (root instanceof Plant) // plant as root
            {
                negMap = gameBoard.zombieMap;
                for (Object ob : negMap.getRow(root.getRow()))
                {
                    Root other = (Root) ob;
                    int dis = other.getX() - root.getX();
                    if (dis >= -20 && dis <= range && !other.finish)
                    {
                        return true;
                    }
                }
            } else if (root instanceof Bullet)
            {
                negMap = gameBoard.zombieMap;
                for (Object ob : negMap.getRow(root.getRow()))
                {
                    Root other = (Root) ob;
                    int dis = root.getX() - other.getX();
                    if (dis > 0 && dis <= other.getWidth() && dis >= range + other.getWidth() / 3 && !other.finish)
                    {
                        return true;
                    }
                }
            } else // 发生致命错误
            {
                System.out.println("Fatal Error: negMap is null!");
                System.exit(-1);
            }

            return false;
        };
    }

}
