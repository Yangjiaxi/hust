import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Parser
{
    public static Publication makeOne(String line)
    {

        if (line.toLowerCase().contains("article"))
        {
            // System.out.println("Article");
            return new Article();
        }
        else if (line.toLowerCase().contains("inproceeding"))
        {
            // System.out.println("Proceeding");
            return new Proceeding();
        }
        else
        {
            System.out.println("Unrecognized category : " + line.substring(1, line.indexOf('{')));
            return null;
        }
    }

    public static KVPair ParseLine(String line)
    {
        line = line.trim();
        if (line.charAt(line.length() - 1) == ',')
        {
            line = line.substring(0, line.length() - 1);
        }

        String[] pp = line.split(" ?= ?");
        String key = pp[0];
        String value = pp[1];
        return new KVPair(key, value);
    }

    public static void fill(KVPair cur, Publication pub)
    {
        if (pub instanceof Article)
        {
            fillArticle(cur, (Article) pub);
        }
        else
        {
            fillProceeding(cur, (Proceeding) pub);
        }
    }

    public static void fillProceeding(KVPair cur, Proceeding pcd)
    {
        String vv = cur.value.substring(1, cur.value.length() - 1);
        switch (cur.key.toLowerCase())
        {
            case "title":
                pcd.setTitle(vv);
                break;
            case "author":
                pcd.setAuthor(vv);
                break;
            case "pages":
                pcd.setPages(vv);
                break;
            case "year":
                pcd.setYears(Integer.parseInt(vv));
                break;
            case "booktitle":
                pcd.setBookTitle(vv);
                break;
            default:
                break;
        }
    }

    public static void fillArticle(KVPair cur, Article art)
    {
        String vv = cur.value.substring(1, cur.value.length() - 1);
        switch (cur.key.toLowerCase())
        {
            case "title":
                art.setTitle(vv);
                break;
            case "author":
                art.setAuthor(vv);
                break;
            case "pages":
                art.setPages(vv);
                break;
            case "year":
                art.setYears(Integer.parseInt(vv));
                break;
            case "journal":
                art.setJournal(vv);
                break;
            case "volume":
                art.setVolume(Integer.parseInt(vv));
                break;
            case "number":
                art.setNumber(Integer.parseInt(vv));
                break;
            default:
                break;
        }
    }

    public static Library BibtexParser(String path)
    {
        Library lib = new Library();
        System.out.println("Parsing Bibtext file from " + path);
        File file = new File("library.bib");
        System.out.println("Parsing...");
        try
        {
            Scanner in = new Scanner(file);
            String s;
            int state = 0; //0:未读入数据 1:正在读入 -1:拒绝读入
            Publication pub = null;
            ArrayList<Author> authors = null;
            while (in.hasNextLine())
            {
                s = in.nextLine();
                switch (state)
                {
                    /*
                      待机态 0:
                        ->  0   读入空行
                        ->  1   读入可识别的首行
                        -> -1   读入不可识别的首行
                     */
                    case 0:
                    {
                        if (s.trim().length() == 0)
                        {
                            state = 0;  //unnecessary
                        }
                        else
                        {
                            pub = makeOne(s);
                            if (pub == null)
                            {
                                state = -1;  //未识别的种类，转换拒绝态
                            }
                            else
                            {
                                authors = new ArrayList<>();
                                state = 1; //可以识别的种类，转换读入态
                            }
                        }
                        break;
                    }
                    /*
                      读入态 1:
                        ->  0   读入右大括号，当前次读取结束 -> 接受态
                        ->  1   otherwise
                     */
                    case 1:
                    {
                        if (s.trim().charAt(0) == '}')
                        {
                            for (String ss : pub.getAuthors().split(" and +"))
                            {
                                String[] name = ss.trim().split(",");
                                authors.add(new Author(name[0].trim(), name[1].trim()));
                            }
                            lib.addPublication(pub, authors);
                            state = 0;
                        }
                        else
                        {
                            KVPair cur = ParseLine(s);
                            fill(cur, pub);
                            state = 1; //unnecessary
                        }
                        break;
                    }
                    /*
                      拒绝态 -1:
                        ->   0  读入右大括号，当前次读取结束
                        ->  -1  otherwise
                     */
                    case -1:
                    {
                        if (s.trim().length() == 0)
                        {
                            state = 0;
                        }
                        else
                        {
                            state = -1;  //unnecessary
                        }
                        break;
                    }
                }
            }
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        System.out.println("\n======Parsing Completed=======\n\n");
        return lib;
    }
}
