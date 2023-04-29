package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestDiagMatrix {
    private InputStreamReader reader;
    private StreamTokenizer tok;

    public TestDiagMatrix(){
        this.reader = new InputStreamReader(System.in);
        this.tok = new StreamTokenizer(reader);
    }

    public void read_matrix(DiagonalMatrix matrix){
        System.out.println("I stand ready for your command, sire! ;)");
        try {
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    String input = tok.sval;
                    int i, j;
                    switch (input){
                        case "Put":
                            double x;
                            tok.nextToken();
                            i = (int) tok.nval;
                            tok.nextToken();
                            j = (int) tok.nval;
                            tok.nextToken();
                            x = (int) tok.nval;
                            matrix.put(i, j, x);
                            break;
                        case "Get":
                            tok.nextToken();
                            i = (int) tok.nval;
                            tok.nextToken();
                            j = (int) tok.nval;
                            System.out.println(matrix.get(i, j));
                            break;
                        case "PrintM":
                            System.out.println(matrix);
                            break;
                        case "MultCons":
                            int cons;
                            tok.nextToken();
                            cons = (int) tok.nval;
                            matrix.multByConstant(cons);
                            break;
                        case "TransM":
                            matrix.transpose();
                            break;
                        case "Quit":
                            return;
                        default:
                            System.out.print("Please choose of the following commands: ");
                            System.out.print("Put, Get, PrintM, Multcons, TransM or Quit\n");
                    }
                }
                else {
                    System.out.println("Command must be a word");
                }
            }
        }
        catch (IOException e){
            System.out.println(e.getMessage());
        }
    }
}
