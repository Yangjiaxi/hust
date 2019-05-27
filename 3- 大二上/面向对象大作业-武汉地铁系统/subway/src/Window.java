import javax.swing.*;
import java.util.ArrayList;
import java.util.Collections;

public class Window
{
    private JPanel panel;
    private JTabbedPane tabbedPane;

    // Page1 -- 查询路过某一站点的所有路线
    private JTextField textStation;
    private JButton btnQueryP1;
    private JButton btnClearP1;
    private JTextArea textAreaP1;

    // Page2 -- 查询某条路线途径的所有站点
    private JComboBox comboRoute;
    private JRadioButton radioFrom;
    private JRadioButton radioTo;
    private JButton btnQueryP2;
    private JButton btnClearP2;
    private JTextArea textAreaP2;

    // Page3 -- 查询两站点之间总距离最短的路径
    private JTextField textFromShortest;
    private JTextField textToShortest;
    private JButton btnQueryP3;
    private JButton btnClearP3;
    private JTextArea textAreaP3;

    // Page4 -- 查询两站点之间换乘次数最少且较短的路径
    private JTextField textFromLeast;
    private JTextField textToLeast;
    private JButton btnQueryP4;
    private JButton btnClearP4;
    private JTextArea textAreaP4;

    private SubwaySystem Wuhan;

    public Window()
    {
        Wuhan = new SubwaySystem();

        btnClearP1.addActionListener(e -> textAreaP1.setText(""));
        btnClearP2.addActionListener(e -> textAreaP2.setText(""));
        btnClearP3.addActionListener(e -> textAreaP3.setText(""));
        btnClearP4.addActionListener(e -> textAreaP4.setText(""));

        btnQueryP1.addActionListener(e -> execQueryP1());
        btnQueryP2.addActionListener(e -> execQueryP2());
        btnQueryP3.addActionListener(e -> execQueryP3());
        btnQueryP4.addActionListener(e -> execQueryP4());
        comboRoute.addItemListener(e -> routeChanged());
    }

    private void execQueryP1()
    {
        String name = textStation.getText().trim();
        textStation.setText("");
        if (name.length() > 0)
        {
            ArrayList<Route> res = Wuhan.showAllRouteHasStation(name);
            if (res == null)
            {
                textAreaP1.append("没有找到经过[ " + name + " ]的路线！\n");
                textAreaP1.append("=======================\n");
            }
            else
            {
                Collections.sort(res);
                textAreaP1.append("找到 " + res.size() + " 条经过[ " + name + " ]的路线\n");
                res.forEach(route -> textAreaP1.append("   - " + route.getName() + "\n"));
                textAreaP1.append("=======================\n");
            }
        }
    }

    private void execQueryP2()
    {
        String selected = radioFrom.isSelected() ? radioFrom.getText() : radioTo.getText();
        String routeName = (String) comboRoute.getSelectedItem();
        ArrayList<Station> res = Wuhan.showAllStations(routeName, selected);
        textAreaP2.append("线路: " + routeName + "    开往: " + selected + "\n");
        for (Station s : res)
        {
            textAreaP2.append("    - " + s.getName() + "\n");
        }
        textAreaP2.append("======================\n");
    }

    private void execQueryP3()
    {
        String from = textFromShortest.getText().trim();
        String to = textToShortest.getText().trim();
        if (from.length() > 0 && to.length() > 0)
        {
            textFromShortest.setText("");
            textToShortest.setText("");
            PathPair res = Wuhan.showShortestPath(from, to, false);
            textAreaP3.append("从[ " + from + " ]到[ " + to + " ]\n");
            if (res != null)
            {
                if (res.getPath().size() == 0)
                {
                    textAreaP3.append("如蜜传如蜜！\n");
                }
                else
                {
                    textAreaP3.append("最短路径：\n");
                    ArrayList<String> out = Wuhan.printPath(res.getPath());
                    out.forEach(s -> textAreaP3.append(" - " + s + "\n"));
                    textAreaP3.append("长度：" + String.format("%.3f", res.getDist()) + " km\n");
                    textAreaP3.append(" - 普通票支付：" + Wuhan.pathPay(res, new RegularTicket()) + "元\n");
                    textAreaP3.append(" - 武汉通支付：" + Wuhan.pathPay(res, new WuhanCard()) + "元\n");
                    textAreaP3.append(" - 一日票支付：" + Wuhan.pathPay(res, new OneDayTicket()) + "元\n");
                }
            }
            else
            {
                textAreaP3.append("不存在通路！\n");
            }
            textAreaP3.append("======================\n");
        }
    }

    private void execQueryP4()
    {
        String from = textFromLeast.getText().trim();
        String to = textToLeast.getText().trim();
        if (from.length() > 0 && to.length() > 0)
        {
            textFromLeast.setText("");
            textToLeast.setText("");
            PathPair res = Wuhan.showLeastTransfer(from, to, false);
            textAreaP4.append("从[ " + from + " ]到[ " + to + " ]\n");
            if (res != null)
            {
                if (res.getPath().size() == 0)
                {
                    textAreaP4.append("如蜜传如蜜！\n");
                }
                else
                {
                    textAreaP4.append("最少换乘：\n");
                    ArrayList<String> out = Wuhan.printPath(res.getPath());
                    out.forEach(s -> textAreaP4.append(" - " + s + "\n"));
                    textAreaP4.append("长度：" + String.format("%.3f", res.getDist()) + " km\n");
                    textAreaP4.append(" - 普通票支付：" + Wuhan.pathPay(res, new RegularTicket()) + "元\n");
                    textAreaP4.append(" - 武汉通支付：" + Wuhan.pathPay(res, new WuhanCard()) + "元\n");
                    textAreaP4.append(" - 一日票支付：" + Wuhan.pathPay(res, new OneDayTicket()) + "元\n");
                }
            }
            else
            {
                textAreaP4.append("不存在通路！\n");
            }
            textAreaP4.append("======================\n");
        }
    }

    public JPanel init_ui()
    {
        ArrayList<String> names = Wuhan.getAllRouteName();
        for (String s : names)
        {
            comboRoute.addItem(s);
        }
        routeChanged();
        return panel;
    }

    private void routeChanged()
    {
        String selected = (String) comboRoute.getSelectedItem();
        int[] headTail = Wuhan.getRouteHeadTail(selected);
        radioFrom.setText(Wuhan.getStationName(headTail[0]));
        radioTo.setText(Wuhan.getStationName(headTail[1]));
        radioFrom.setSelected(true);
    }

    public static void main(String[] args)
    {
        JFrame frame = new JFrame("武汉地铁模拟系统");
        frame.setContentPane((new Window()).panel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setSize(600, 400);
        frame.setResizable(false);
        frame.setVisible(true);
    }
}
