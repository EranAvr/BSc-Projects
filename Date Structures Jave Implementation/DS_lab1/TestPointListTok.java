package com.company;

import java.awt.*;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestPointListTok {
    /*
     * 1) nextToken() is used to read the next byte(!!!) from stream. The byte can be stored in variable (int) if needed.
     * 2) TT_EOF and TT_EOL are used to indicate variations of stream endings.
     * 3) ttype is used to get the current token type.
     * 4) TT_Word constant indicates String, TT_NUMBER constant indicates double.
     * 5) tokenizer.sval returns the string read, tokenizer.nval returns the number read.
     */
    private InputStreamReader reader;
    private StreamTokenizer tok;

    public TestPointListTok() {
        this.reader = new InputStreamReader(System.in);
        this.tok = new StreamTokenizer(reader);
    }

    public void read_points(ArrayPointList points){
        try {
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    String in = tok.sval;
                    switch (in){
                        case "add":
                            int x, y;
                            tok.nextToken();
                            x = (int) tok.nval;
                            tok.nextToken();
                            y = (int) tok.nval;
                            points.append(new Point(x, y));
                            break;
                        case "curr":
                            System.out.println(points.getCursor());
                            break;
                        case "next":
                            System.out.println(points.goToNext());
                            break;
                        case "prev":
                            System.out.println(points.goToPrior());
                            break;
                        case "start":
                            System.out.println(points.goToBeginning());
                            break;
                        case "end":
                            System.out.println(points.goToEnd());
                            break;
                        case "empty":
                            System.out.println(points.isEmpty());
                            break;
                        case "full":
                            System.out.println(points.isFull());
                            break;
                        case "clear":
                            points.clear();
                            break;
                        case "quit":
                            return;
                    }
                }
                else{
                    System.out.println("Command must be a word");
                }
            }
        }
        catch (IOException e){
            System.out.println(e.getMessage());
        }
        finally {
            // just for final check
            System.out.println(points);
        }
    }
}
