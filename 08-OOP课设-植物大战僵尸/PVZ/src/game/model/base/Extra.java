package game.model.base;

public class Extra extends Root
{
    private String fName; //完整的路径
    private int ms; //持续时间
    private boolean bullet;

    public Extra(String fName, int ms, int x, int y, boolean bullet)
    {
        //        System.out.println("构造额外项目");
        finish = false;
        setX(x);
        setY(y);
        this.fName = fName;
        this.ms = ms;
        this.bullet = bullet;
        load_img();
        perform();
    }

    public Extra(String fName, int ms, int x, int y)
    {
        this(fName, ms, x, y, false);
    }

    private void perform()
    {
        (new Thread(() ->
        {
            try
            {
                Thread.sleep(ms);
                finish = true;
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
        })).start();
    }

    public boolean isBullet()
    {
        return bullet;
    }

    protected void setStateTable()
    {

    }

    protected void setStateTransfer()
    {

    }

    protected String getPath()
    {
        return fName;
    }
}
