import java.util.Collections;

public class Main
{

    public static void main(String[] args)
    {
        Library lib = Parser.BibtexParser("library.bib");
//        lib.show();  // for test
        lib.showAPA();  //quiz.01

        Library qres = lib.query("Azmandian, Mahdi");
        qres.showAPA(); //quiz.02

        System.out.println(lib.hasBoth("Azmandian", "Grechkin")); //quiz.03

        Library dplt = lib.copy();
        Collections.sort(dplt.getPublications()); //quiz.04
        dplt.showInfo();
    }

}
