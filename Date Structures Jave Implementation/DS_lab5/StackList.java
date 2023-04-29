package com.company;

public class StackList<T> implements Stack<T>{

    private SNode<T> top;            // Top Of Stack: Index for the top element
    private SLinkedList<T> elements;       // Array containing stack elements
    private int size;

    public StackList(int size){
        this.size = 0;
        this.top = null;
        this.elements = new SLinkedList<>();
    }

    @Override
    public void push(T newElement) {
        SNode<T> elToInsert = new SNode<>(newElement, null);
        this.elements.insert(elToInsert);
        this. size++;
    }

    @Override
    public T pop() {
        this.elements.gotoEnd();
        SNode<T> elToPop = this.elements.getCursor();
        this.elements.remove();
        this.size--;
        return elToPop.getElement();
    }

    @Override
    public void clear() {
        this.elements.clear();
        this.size = 0;
    }

    @Override
    public boolean isEmpty() {
        return this.elements.isEmpty();
    }

    @Override
    public boolean isFull() {
        return false;
    }

    @Override
    public String toString() {
        String res = "---STACK---\n";
        this.elements.gotoBeginning();
        for (int i = 0; i<this.size ; i++){
            res += "#" + i + " : " + elements.getCursor().getElement() + "\n";
            res += "-----------\n";
            elements.gotoNext();
        }
        res += "---e-n-d---\n";
        return res;
    }
}
