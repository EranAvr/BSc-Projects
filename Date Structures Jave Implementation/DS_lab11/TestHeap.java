package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestHeap {
    private Heap heap;
    private InputStreamReader reader;
    private StreamTokenizer tok;

    TestHeap() {
        this.reader = new InputStreamReader(System.in);
        this.tok = new StreamTokenizer(reader);
    }

    public void start() {
        try {
            System.out.println("Welcome to the Integer-Heap test interface :)");
            System.out.println("Enter size of heap (default is 10)");
            tok.nextToken();
            if (tok.ttype==StreamTokenizer.TT_NUMBER && tok.nval>0){
                heap = new Heap((int) tok.nval);
            }
            else {
                heap = new Heap();
            }
            System.out.println("Choose from the following:");
            System.out.println("in <int val>, R, C, E, F, P, options");
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype==StreamTokenizer.TT_WORD){
                    switch (tok.sval){
                        case "in":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_NUMBER){
                                System.out.println("Element value must be an integer");
                                break;
                            }
                            heap.insert(new HeapData((int)tok.nval));
                            break;
                        case "R":
                            System.out.println("Removing minimum priority: " + (heap.removeMin()));
                            break;
                        case "C":
                            heap.clear();
                            System.out.println("Heap was cleared");
                            break;
                        case "E":
                            System.out.println("Is heap empty? " + heap.isEmpty());
                            break;
                        case "F":
                            System.out.println("Is heap full? " + heap.isFull());
                            break;
                        case "P":
                            System.out.println(heap);
                            break;
                        case "Options":
                        case "options":
                            System.out.println("in <int val>, R, C, E, F, P, options");
                            break;
                    }
                }
                else {
                    System.out.println("Command must be a word/letter");
                }
            }

        }
        catch (IOException e){
            System.out.println(e.getMessage());
        }
        catch (Exception e){
            System.out.println(e.getCause());
        }
    }
}
