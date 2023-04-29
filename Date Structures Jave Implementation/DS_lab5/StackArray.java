package com.company;

import java.util.Objects;

public class StackArray<T> implements Stack<T> {

    private int top;            // Top Of Stack: Index for the top element
    private int bottom = -1;    // Points to last occupied cell. bottom=-1 means empty stack
    private T[] elements;       // Array containing stack elements

    public StackArray(int size){
        this.top = 0;
        if (size > 0){
            this.elements = (T[]) new Object[size];
        }
        else {
            this.elements = (T[]) new Object[DEF_MAX_STACK_SIZE];
        }
    }

    @Override
    public void push(T newElement) {
        if (!isFull()){
            this.bottom += 1;
            this.elements[bottom] = newElement;
        }
    }

    @Override
    public T pop() {
        if (isEmpty()){
            return null;
        }
        else {
            T temp = this.elements[bottom];
            this.elements[bottom] = null;   // To erase the popped element from stack.
            this.bottom -= 1;
            return temp;
        }
    }

    @Override
    public void clear() {
        while (pop() != null);
    }

    @Override
    public boolean isEmpty() {
        return (this.bottom == -1);
    }

    @Override
    public boolean isFull() {
        return (this.bottom == elements.length-1);
    }

    @Override
    public String toString() {
        String res = "---STACK---\n";
        for (int i=0 ; i<=bottom ; i++){
            res += "#" + i + " : " + elements[i] + "\n";
            res += "-----------\n";
        }
        res += "---e-n-d---\n";
        return res;
    }
}
