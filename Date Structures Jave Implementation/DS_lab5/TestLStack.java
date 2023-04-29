package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestLStack {
    private StackList<Integer> stack;
    private InputStreamReader reader;
    private StreamTokenizer tok;

    public TestLStack(){
        reader = new InputStreamReader(System.in);
        tok = new StreamTokenizer(reader);
    }

    public void startTest(){
        try {
            // Stack initialization
            do {
                System.out.println("Enter number for stack size: ");
                tok.nextToken();
            } while (tok.ttype != StreamTokenizer.TT_NUMBER);
            stack = new StackList<>((int)tok.nval);

            // User interface
            System.out.println("Enter command from the following:");
            System.out.println("Push, Pop, P, F, E, C, Q, Options");
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    switch (tok.sval){
                        case "Push":
                            tok.nextToken();
                            if (stack.isFull()){
                                System.out.println("Stack is full");
                                break;
                            }
                            if (tok.ttype != StreamTokenizer.TT_NUMBER){
                                System.out.println("Input must be a number");
                                break;
                            }
                            stack.push((int)tok.nval);
                            break;
                        case "Pop":
                            if (stack.isEmpty()){
                                System.out.println("Stack is empty");
                                break;
                            }
                            stack.pop();
                            break;
                        case "P":
                            if (stack.isEmpty()){
                                System.out.println("Stack is empty");
                                break;
                            }
                            System.out.println(stack);
                            break;
                        case "F":
                            System.out.println(stack.isFull());
                            break;
                        case "E":
                            System.out.println(stack.isEmpty());
                            break;
                        case "C":
                            stack.clear();
                            System.out.println("Stack was cleared");
                            break;
                        case "Q":
                            System.out.println("Bye Bye.. ;)");
                            return;
                        case "Options":
                            System.out.println("Push, Pop, P, F, E, C, Q, Options");
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
