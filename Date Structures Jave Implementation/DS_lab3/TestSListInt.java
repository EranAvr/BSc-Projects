package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestSListInt<T> {
    SLinkedList<T> linkedList;
    InputStreamReader reader;
    StreamTokenizer tok;

    public TestSListInt(){
        linkedList = new SLinkedList<>();
        this.reader = new InputStreamReader(System.in);
        this.tok = new StreamTokenizer(reader);
    }

    public void startTestListInt(){
        System.out.println("Welcome to TestSListChar");
        System.out.println("Type 'options' to see possible commands");
        try {
            SNode<T> tempNode;
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    String choice = tok.sval;
                    Integer tempVal;
                    switch (choice){
                        case "Add":
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_NUMBER){
                                System.out.println("Input must be an integer");
                                break;
                            }
                            tempVal = (int) tok.nval;
                            tempNode = new SNode(tempVal, null);
                            linkedList.insert(tempNode);
                            break;
                        case "Del":
                            linkedList.remove();
                            break;
                        case "Mv":
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_NUMBER){
                                System.out.println("Input must be an integer");
                                break;
                            }
                            tempVal = (int) tok.nval;
                            tempNode = new SNode(tempVal, null);
                            linkedList.replace(tempNode);
                            break;
                        case "Cur":
                            System.out.println(linkedList.getCursor());
                            break;
                        case "N":
                            linkedList.gotoNext();
                            break;
                        case "P":
                            linkedList.gotoPrior();
                            break;
                        case "B":
                            linkedList.gotoBeginning();
                            break;
                        case "End":
                            linkedList.gotoEnd();
                            break;
                        case "E":
                            System.out.println(linkedList.isEmpty());
                            break;
                        case "C":
                            linkedList.clear();
                            break;
                        case "Print":
                            linkedList.printSLinkedList();
                            break;
                        case "Q":
                            System.out.println("Bye Bye..");
                            return;
                        case "options":
                            System.out.println("Please choose from the following commands:");
                            System.out.println("Add, Del, Mv, Cur, N, P, B, End, E, C, Print, Q");
                            break;
                        default:
                            System.out.println("Unknown command");
                    }
                }
                else {
                    System.out.println("Command must be a word");
                }

            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
