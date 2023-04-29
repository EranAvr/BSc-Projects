package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestGraph {
    Graph graph;
    InputStreamReader reader;
    StreamTokenizer tok;

    public TestGraph(){
        reader = new InputStreamReader(System.in);
        tok = new StreamTokenizer(reader);
    }

    void start(){
        try {
            System.out.println("Welcome to the Integer-Heap test interface :)");
            System.out.println("Enter size of heap (default is 10)");
            tok.nextToken();
            if (tok.ttype==StreamTokenizer.TT_NUMBER && tok.nval>0){
                graph = new Graph((int) tok.nval);
            }
            else {
                graph = new Graph();
            }
            System.out.println("Enter command:");
            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype==StreamTokenizer.TT_WORD){
                    String v, w;
                    switch (tok.sval){
                        case "Add":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_WORD){
                                System.out.println("Input must be a string");
                                break;
                            }
                            graph.insertVertex(new Vertex(tok.sval));
                            break;
                        case "AddE":
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'v' must be a string");
                                break;
                            }
                            v = tok.sval;
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'w' must be a string");
                                break;
                            }
                            w = tok.sval;
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_NUMBER){
                                System.out.println("weight must be a number");
                                break;
                            }
                            graph.insertEdge(v, w, (int)tok.nval);
                            break;
                        case "Ret":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_WORD){
                                System.out.println("Vertex must be a word");
                                break;
                            }
                            graph.retrieveVertex(tok.sval);
                            break;
                        case "RetE":
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'v' must be a string");
                                break;
                            }
                            v = tok.sval;
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'w' must be a string");
                                break;
                            }
                            w = tok.sval;
                            System.out.println(graph.edgeWeight(v, w));
                            break;
                        case "Rem":
                            tok.nextToken();
                            if (tok.ttype != StreamTokenizer.TT_WORD){
                                System.out.println("Vertex must be a word");
                                break;
                            }
                            graph.removeVertex(tok.sval);
                            break;
                        case "RemE":
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'v' must be a string");
                                break;
                            }
                            v = tok.sval;
                            tok.nextToken();
                            if (tok.ttype!=StreamTokenizer.TT_WORD){
                                System.out.println("Edge 'w' must be a string");
                                break;
                            }
                            w = tok.sval;
                            graph.removeEdge(v, w);
                            break;
                        case "E":
                            System.out.println(graph.isEmpty());
                            break;
                        case "F":
                            System.out.println(graph.isFull());
                            break;
                        case "C":
                            graph.clear();
                            break;
                        case "P":
                            System.out.println(graph);
                            break;
                        case "Q":
                            System.out.println("Bye Bye.. ;)");
                            return;
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
    }
}
