
public class Rectangle extends Shape
{
    private int width;
    private int height;

    public Rectangle(int w, int h)
    {
        this.width = w;
        this.height = h;
    }

    @Override
    public double getArea()
    {
        return (double) (this.width * this.height); // to be replaced
    }

}
