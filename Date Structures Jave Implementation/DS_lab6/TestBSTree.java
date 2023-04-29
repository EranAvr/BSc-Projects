package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestBSTree {
    private BSTree tree;
    private InputStreamReader reader;
    private StreamTokenizer tok;

    public TestBSTree(){
        reader = new InputStreamReader(System.in);
        tok = new StreamTokenizer(reader);
    }

    public void startTest(){
        try {
            tree = new BSTree();

            // User interface
            System.out.println("Enter command from the following:");
            System.out.println("+<val to insert>, ?<val to retrieve>, K, E, F, C, Q, Options");
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    switch (tok.sval){
                        case "+":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_NUMBER){
                                System.out.println("Input must be a number");
                                break;
                            }
                            tree.insert((int)tok.nval);
                            break;
                        case "?":
                            if (tree.isEmpty()){
                                System.out.println("Tree is empty");
                                break;
                            }
                            tree.retrieve((int)tok.nval);
                            break;
                        case "D":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_NUMBER){
                                System.out.println("Input must be a number");
                                break;
                            }
                            tree.delete((int)tok.nval);
                            break;
                        case "K":
                            if (tree.isEmpty()){
                                System.out.println("Tree is empty");
                                break;
                            }
                            tree.Inorder();
                            break;
                        case "E":
                            System.out.println(tree.isEmpty());
                            break;
                        case "F":
                            System.out.println(tree.isFull());
                            break;
                        case "C":
                            tree.clear();
                            System.out.println("Stack was cleared");
                            break;
                        case "Q":
                            System.out.println("Bye Bye.. ;)");
                            return;
                        case "Options":
                            System.out.println("+<val to insert>, ?<val to retrieve>, K, E, F, C, Q, Options");
                            break;
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
