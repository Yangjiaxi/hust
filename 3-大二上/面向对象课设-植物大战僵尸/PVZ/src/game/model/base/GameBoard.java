package game.model.base;

import game.model.bullets.Bullet;
import game.model.plants.Plant;
import game.model.plants.Sun;
import game.model.zombies.Zombie;

import java.util.concurrent.CopyOnWriteArrayList;

public class GameBoard
{
    public ItemMap<Zombie> zombieMap;
    public ItemMap<Plant> plantMap;
    public ItemMap<Bullet> bulletMap;
    public CopyOnWriteArrayList<Sun> sunMap;
    public CopyOnWriteArrayList<Extra> extraMap;
    //    public ArrayList<Extra> extraMap;

    public GameBoard(int rows)
    {
        zombieMap = new ItemMap<>(rows);
        plantMap = new ItemMap<>(rows);
        bulletMap = new ItemMap<>(rows);
        sunMap = new CopyOnWriteArrayList<>();
        extraMap = new CopyOnWriteArrayList<>();
    }

}
