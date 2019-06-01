package game.model.plants;

import game.model.base.*;
import game.model.sound.SoundPool;
import game.model.zombies.Zombie;

import java.util.function.BiConsumer;
import java.util.function.BiPredicate;

public class PotatoMine extends Plant
{
    private int grow_time = 0;
    private int time_to_wait = 10 * GameRule.FRAME_RATE;

    public PotatoMine(Integer x, Integer y)
    {
        // System.out.println("创建土豆雷);
        setName("potatomine");
        setMaxHp(300);
        load_img();
        plantSetAt(x, y);
        //  System.out.println("Create :" + W + ", " + H);
    }

    protected void setStateTable()
    {
        // 0 : 准备
        // 1 : 等待
        //2 : 爆炸
        //3 : hp耗尽

        BiConsumer<GameBoard, Root> boom = ((gameBoard, root) ->
        {
            finish = true;
            gameBoard.extraMap.add(new Extra(getPath(), 2000, getX() - (getWidth() - GameRule.SIZE_X) / 2,
                    getY() - (getHeight() - GameRule.SIZE_Y) / 2));
            gameBoard.extraMap.add(new Extra("resource/image/plant/potatomine/explosionspudow.gif", 2000,
                    getX() - (getWidth() - GameRule.SIZE_X) / 2, getY() - getHeight() / 2));
            SoundPool.addSound(GameRule.potato_mine);
            ItemMap negMap = gameBoard.zombieMap;
            for (Object ob : negMap.getRow(root.getRow()))
            {
                Zombie cur = (Zombie) ob;
                int dis = cur.getX() - root.getX();
                if (dis >= -20 && dis <= GameRule.SIZE_X / 2)
                {
                    cur.boomDie();
                }
            }
        });
        addState(0, "potatominenotready.gif", (gameBoard, root) -> ++grow_time);
        addState(1, "potatomine.gif", null);
        addState(2, "potatominemashed.gif", boom);
        addState(3, null, (gameBoard, root) -> finish = true);
    }

    protected void setStateTransfer()
    {
        BiPredicate<GameBoard, Root> canBoom = (gameBoard, root) ->
        {
            ItemMap negMap = gameBoard.zombieMap;
            for (Object ob : negMap.getRow(root.getRow()))
            {
                Root other = (Root) ob;
                int dis = other.getX() - root.getX();
                if (dis >= -20 && dis <= GameRule.SIZE_X / 2)
                {
                    return true;
                }
            }
            return false;
        };
        addTransfer(0, 3, (gameBoard, root) -> hp <= 0);//hp耗尽
        addTransfer(0, 1, (gameBoard, root) -> grow_time == time_to_wait);
        addTransfer(1, 2, canBoom);
    }
}
