package com.company;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class TestHashTable {
    private HashTable table;
    private InputStreamReader reader;
    private StreamTokenizer tok;

    public TestHashTable() {
        reader = new InputStreamReader(System.in);
        tok = new StreamTokenizer(reader);
    }

    public void start() {
        try {
            // Initialize table
            System.out.println("Enter table size (default is 10)");
            tok.nextToken();
            if (tok.ttype == StreamTokenizer.TT_NUMBER && tok.nval > 0) {
                table = new HashTable((int) tok.nval);
                System.out.println("Table created with size " + (int)tok.nval);
            }
            else {
                table = new HashTable();
                System.out.println("Table created with size 10");
            }

            // User interface
            System.out.println("\nWelcome to the Hash Table interface");
            System.out.println("ret <id>, in <id, first, last, age, average>, rem <id>, C, E, F, P, Options");

            while (tok.nextToken() != StreamTokenizer.TT_EOF){
                if (tok.ttype == StreamTokenizer.TT_WORD){
                    int t_id, t_age;
                    double t_avg;
                    String t_fname, t_lname;
                    switch (tok.sval){
                        case "ret":
                            tok.nextToken();
                            if (tok.ttype == StreamTokenizer.TT_NUMBER)
                                t_id = (int)tok.nval;
                            else
                                break;
                            boolean res = table.retrieve(new HashTableData(Integer.toString(t_id)));
                            System.out.println("Is " + t_id + " in list? " + res);
                            break;
                        case "in":
                            tok.nextToken();
                            if (tok.ttype==StreamTokenizer.TT_NUMBER)
                                t_id = (int)tok.nval;
                            else {
                                System.out.println("Id must be a number");
                                break;
                            }
                            tok.nextToken();
                            if (tok.ttype==StreamTokenizer.TT_WORD)
                                t_fname = tok.sval;
                            else {
                                System.out.println("First name must be a ord");
                                break;
                            }
                            tok.nextToken();
                            if (tok.ttype==StreamTokenizer.TT_WORD)
                                t_lname = tok.sval;
                            else {
                                System.out.println("Last name must be a word");
                                break;
                            }
                            tok.nextToken();
                            if (tok.ttype==StreamTokenizer.TT_NUMBER)
                                t_age = (int)tok.nval;
                            else {
                                System.out.println("Age must be a number");
                                break;
                            }
                            tok.nextToken();
                            if (tok.ttype==StreamTokenizer.TT_NUMBER)
                                t_avg = tok.nval;
                            else {
                                System.out.println("Average must be a number");
                                break;
                            }
                            Student s = new Student(t_id, t_fname, t_lname, t_age, t_avg);
                            table.insert(s);
                            System.out.println(s + " was added");
                            break;
                        case "rem":
                            tok.nextToken();
                            if (tok.ttype == StreamTokenizer.TT_NUMBER)
                                t_id = (int)tok.nval;
                            else
                                break;
                            table.remove(new HashTableData(Integer.toString(t_id)));
                            System.out.println(t_id + " was removed");
                            break;
                        case "C":
                            table.clear();
                            System.out.println("Tale was cleared");
                            break;
                        case "E":
                            System.out.println(table.isEmpty());
                            break;
                        case "F":
                            System.out.println(table.isFull());
                            break;
                        case "P":
                            System.out.println(table);
                            break;
                        case "Options":
                            System.out.println("ret <id>, in <student details>, rem <id>, C, E, F, P, Options");
                            break;
                    }
                }
                else {
                    System.out.println("Command must be a word or a character");
                }
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
