package game.controller;

import javax.swing.*;
import java.awt.*;

public class MainFrame extends JFrame
{
    public MainFrame()
    {
        System.out.println("创建开始界面");
        setLayout(new BorderLayout());
        initUI();
    }

    private void initUI()
    {
        setSize(new Dimension(1130, 600));
        setTitle("! ! ! P ! ! ! V ! ! ! Z ! ! !");
        setResizable(false);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        gameStart();
    }

    private void gameStart()
    {
        getContentPane().add(new TopPanel());
    }
}
