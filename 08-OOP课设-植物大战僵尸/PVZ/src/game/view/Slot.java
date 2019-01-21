package game.view;

import game.model.base.GameRule;
import game.model.level.LevelManager;
import game.model.plants.*;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Slot extends JPanel
{

    private int sunBank = 50;
    private ArrayList<Card> cardList;

    private int pickingIDX = -1;

    final private int topBias = 175;
    final private int heightPerCard = 60;

    private LevelManager levelManager;

    public Slot(LevelManager levelManager)
    {
        setSize(200, 600);
        setBackground(new Color(39, 54, 38));

        this.levelManager = levelManager;

        cardList = new ArrayList<>();
        // cardList.add(new Card("resource/image/Card/SunFlower.png", 75, 5, null));

        levelManager.getPlants().forEach(plantInfo -> cardList.add(Card.make(plantInfo)));
        // cardList.add(new Card("Peashooter", 50, 2, Peashooter.class));
        // cardList.add(new Card("Repeater", 50, 2, Repeater.class));
        // cardList.add(new Card("Chomper", 100, 2, Chomper.class));
        // cardList.add(new Card("WallNut", 100, 2, WallNut.class));
        // cardList.add(new Card("Torchwood", 100, 2, TorchWood.class));
        // cardList.add(new Card("SnowPea", 100, 2, SnowPea.class));
    }

    public Image checkClick(int x, int y)
    {
        if (y > topBias)
        {
            int idx = (y - topBias) / heightPerCard;
            if (idx < cardList.size())
            {
                if ((y - topBias - idx * heightPerCard) <= 60)
                {
                    Card cur = cardList.get(idx);
                    if (sunBank >= cur.getCost() && cur.isCanPlace())
                    {
                        if (idx != pickingIDX)
                        {
                            // System.out.println("Pick " + idx);
                            pickingIDX = idx;
                            return (new ImageIcon(cur.getMoveImg())).getImage();
                        } else
                        {
                            pickingIDX = -1;
                        }
                    }
                }
            }
        }
        return null;
    }

    public void addSun(int s)
    {
        sunBank += s;
    }

    public Plant placeConfirm(int ix, int iy)
    {
        cardList.get(pickingIDX).clearCounter();
        sunBank -= cardList.get(pickingIDX).getCost();
        Plant pl = cardList.get(pickingIDX).getInstance(ix, iy);
        pickingIDX = -1;
        return pl;
    }

    public void updateAll()
    {
        for (Card c : cardList)
        {
            c.updateTime();
        }
    }

    @Override
    protected void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        Image sun = new ImageIcon("resource/image/other/SunBack.png").getImage();
        g.drawImage(sun, 0, 0, 200, 60, null);
        g.setFont(new Font(null, Font.BOLD, 40));
        g.drawString(String.valueOf(sunBank), 80, 45);

        g.setFont(new Font(null, Font.BOLD, 20));
        g.setColor(Color.WHITE);
        g.drawString("关卡: " + String.valueOf(levelManager.getLevelName()), 20, 100);
        g.drawString("剩余僵尸: " + levelManager.getZombiesRemain(), 20, 150);
        for (int i = 0; i < cardList.size(); i++)
        {
            Card cur = cardList.get(i);
            Image ca = new ImageIcon(cur.getCardImg()).getImage();
            if (cur.isCanPlace() && sunBank >= cur.getCost() && i != pickingIDX)
            {
                g.drawImage(ca, 0, i * heightPerCard + topBias, 100, i * heightPerCard + topBias + 60, 0, 0, 100, 60,
                        null);
            } else
            {
                g.drawImage(ca, 0, i * heightPerCard + topBias, 100, i * heightPerCard + topBias + 60, 0, 60, 100, 120,
                        null);
            }
            g.setFont(new Font(null, Font.BOLD, 16));
            g.drawString("cost : " + String.valueOf(cur.getCost()), 110, i * heightPerCard + topBias + 20);
            if (cur.isCanPlace())
            {
                g.drawString("Charged!", 110, i * heightPerCard + topBias + 50);
            } else
            {
                g.drawString(cur.getChargingPercent(), 110, i * heightPerCard + topBias + 50);
            }
        }
    }
}
