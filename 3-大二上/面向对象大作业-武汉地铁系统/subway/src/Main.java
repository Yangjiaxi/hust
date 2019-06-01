import javax.swing.*;

public class Main
{
    public static void main(String[] args)
    {
        JFrame frame = new JFrame("武汉地铁模拟系统");
        frame.setContentPane((new Window()).init_ui());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        frame.pack();
        frame.setSize(640, 480);
        frame.setResizable(false);
        frame.setVisible(true);
    }
}
