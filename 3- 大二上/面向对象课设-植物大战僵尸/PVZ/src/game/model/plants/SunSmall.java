package game.model.plants;

class SunSmall extends Sun
{
    SunSmall(int x, int y_from, int y_to)   // size - 阳光的尺寸，0为正常，1为小阳光
    {
        super(x, y_from, y_to);
        //System.out.println("生成小阳光");
        setName("sun_s");
        contain = 15;
    }
}
