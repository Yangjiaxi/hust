import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class BillParser {
    public static Billboard readBillboard(String path) {
        Billboard result = new Billboard();
        System.out.println("Parsing Billboard file from " + path);
        File file = new File(path);
        System.out.println("Parsing...");
        try {
            Scanner in = new Scanner(file);
            String s;
            s = in.nextLine();
            System.out.println(s);
            while (in.hasNextLine()) {
                s = in.nextLine();
                String[] para = s.split("\t");
                Song cur = new Song(para[1], para[2], Integer.parseInt(para[3]));
                result.addSong(cur);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println("\n======Parsing Completed=======\n\n");
        return result;
    }

    // public static void main(String[] args)
    // {
    // readBillboard("wiki_hot_100s.txt");
    // }
}
