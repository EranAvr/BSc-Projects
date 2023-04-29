package com.company;

import java.io.InputStreamReader;
import java.io.StreamTokenizer;
import java.util.Scanner;

public class CheckBalancedBrackets {
    private Scanner scanner;
    private StackArray<Character> stack;

    public CheckBalancedBrackets(){
        scanner = new Scanner(System.in);
    }

    public void checkExpression(){
        System.out.println("Enter expression:");
        String input = scanner.nextLine();
        stack = new StackArray<>(input.length());
        for (int i=0 ; i<input.length() ; i++){
            char c = input.charAt(i);
            switch (c){
                case '{':
                case '[':
                case '(':
                    stack.push(input.charAt(i));
                    break;
                case ')':
                    if (stack.isEmpty() || stack.pop()!='('){
                        System.out.println("Not balanced");
                        return;
                    }
                    break;
                case ']':
                    if (stack.isEmpty() || stack.pop()!='['){
                        System.out.println("Not balanced");
                        return;
                    }
                    break;
                case '}':
                    if (stack.isEmpty() || stack.pop()!='{'){
                        System.out.println("Not balanced");
                        return;
                    }
                    break;
            }
        }
        // Final check-
        if (stack.isEmpty()){
            System.out.println("Expression is balanced !!");
        }
        else {
            System.out.println("Not balanced");
        }
    }
}
