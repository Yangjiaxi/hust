import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Window extends JPanel implements ActionListener
{
    private Billboard bb;

    private JTextArea msgArea;
    private JTextArea inputYear;
    private JButton clear;
    private JButton btnYear;
    private JButton btnComposers;
    private JButton btnTopTen;

    public Window(String path)
    {
        bb = BillParser.readBillboard(path);
        clear = new JButton("清空文本框");
        clear.addActionListener(this);
        msgArea = new JTextArea();
        JScrollPane msgOutter = new JScrollPane(msgArea);
        msgArea.setEditable(false);
        msgArea.setLineWrap(true);

        inputYear = new JTextArea();
        btnYear = new JButton("显示曲目");
        btnYear.addActionListener(this);

        btnComposers = new JButton("显示所有歌手");
        btnComposers.addActionListener(this);

        btnTopTen = new JButton("Top-10 歌手");
        btnTopTen.addActionListener(this);

        setLayout(new BorderLayout());

        JPanel side = new JPanel();
        side.setLayout(new GridLayout(5, 1));
        side.add(clear);
        side.add(inputYear);
        side.add(btnYear);
        side.add(btnComposers);
        side.add(btnTopTen);
        add(msgOutter, BorderLayout.CENTER);
        add(side, BorderLayout.EAST);
    }

    public void appendArrString(ArrayList<String> as)
    {
        for (String ss : as)
        {
            msgArea.append(ss + "\n");
        }
    }

    public boolean isNumeric(String str)
    {
        Pattern pattern = Pattern.compile("[0-9]*");
        Matcher isNum = pattern.matcher(str);
        return isNum.matches();
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        if (e.getSource() == btnYear)
        {
            System.out.println("output year " + inputYear.getText());
            try
            {
                int yy = Integer.parseInt(inputYear.getText());
                if (1960 <= yy && yy <= 2016)
                {
                    appendArrString(bb.queryByYear(yy));
                }
                else
                {
                    msgArea.append("非法的输入！(1960~2016)\n");
                }
            } catch (Exception ee)
            {
                msgArea.append("非法的输入！(1960~2016)\n");
            }


        }
        else if (e.getSource() == btnComposers)
        {
            appendArrString(bb.getAllComposers());
            System.out.println("output composers");
        }
        else if (e.getSource() == btnTopTen)
        {
            appendArrString(bb.getTopTen());
            System.out.println("output top ten");
        }
        else if (e.getSource() == clear)
        {
            System.out.println("Clean text");
            msgArea.setText("");
        }
    }

    public static void main(String[] args)
    {
        JFrame frame = new JFrame("※ B I L L B O A R D ※");
        frame.setSize(500, 500);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new Window("wiki_hot_100s.txt"));
        frame.setVisible(true);
    }
}
