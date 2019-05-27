import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Billboard
{
    private HashMap<Integer, ArrayList<Song>> years;
    private ArrayList<Composer> composers;

    public Billboard()
    {
        years = new HashMap<>();
        for (int yy = 1960; yy <= 2016; yy++)
        {
            years.put(yy, new ArrayList<>());
        }
        composers = new ArrayList<>();
    }

    private boolean existSong(String songName, int year)
    {
        for (int yy = 1960; yy < year; yy++)
        {
            if (years.get(yy).contains(new Song(songName)))
            {
                return true;
            }
        }
        return false;
    }

    private Composer getComposer(String name)
    {
        for (Composer e : composers)
        {
            if (e.getName().equals(name))
            {
                return e;
            }
        }
        return null;
    }

    public void addSong(Song song)
    {
        /*
        添加歌曲
        添加到这一年的ArrayList
        检查composers是否包含作者名字
            如果有：
                检查之前的年份是否包含该歌曲，如果不包含，对应作者inc()
            没有：
                创建Composers对象插入到composers列表中
        */
        years.get(song.getYear()).add(song);
        Composer tmp = getComposer(song.getComposer());
        if (tmp != null)
        {
            if (!existSong(song.getName(), song.getYear()))
            {
                tmp.inc();
            }
        }
        else
        {
            composers.add(new Composer(song.getComposer()));
        }
    }

    public ArrayList<String> queryByYear(int year)
    {
        ArrayList<String> res = new ArrayList<>();
        res.add("=====[All Songs in year " + year + "]======");
        int idx = 1;
        for (Song ss : years.get(year))
        {
            res.add(idx++ + " : " + ss.getName());
        }
        res.add("=======================");
        return res;
    }

    public ArrayList<String> getAllComposers()
    {
        ArrayList<String> res = new ArrayList<>();
        for (Composer comp : composers)
        {
            res.add(comp.getName());
        }
        Collections.sort(res);
        res.add(0, "=====[All Composers in Billboard]======");
        res.add("====================");
        return res;
    }

    public ArrayList<String> getTopTen()
    {
        ArrayList<String> res = new ArrayList<>();
        Collections.sort(composers);
        res.add("=====[Top-10 composers]======");
        for (int i = 0; i < 10; i++)
        {
            res.add((i + 1) + " : " + composers.get(i).getName() +
                    " : " + composers.get(i).getCount());
        }
        res.add("=================");
        return res;
    }


    public void show()
    {
        for (HashMap.Entry<Integer, ArrayList<Song>> ent : years.entrySet())
        {
            System.out.println(ent.getKey());
            for (Song ss : ent.getValue())
            {
                System.out.println(ss);
            }
        }
        System.out.println("===============");
        for (Composer cm : composers)
        {
            System.out.println(cm);
        }
    }

}
