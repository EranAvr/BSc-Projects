package com.company;

public class SLinkedList<T> implements List{
    private SNode<T> head;      // Reference to the beginning of the list
    private SNode<T> cursor;    // Reference to current cursor position

    public SLinkedList(){
        this.head = null;
        this.cursor = null;
    }

    @Override
    public void insert(SNode newElement) {
        if (newElement == null){
            System.out.println("Can't insert a null element");
            return;
        }
        if (this.isEmpty()){     // The list is empty
            newElement.setNext(null);
            this.head = newElement;
            this.cursor = newElement;
        }
        else {                  // The list is NOT empty
            newElement.setNext(this.cursor.getNext());
            this.cursor.setNext(newElement);
            this.cursor = newElement;
        }
    }

    @Override
    public void remove() {
        if (this.isEmpty()){    // empty list
            return;
        }
        if (this.cursor == this.head){   // remove first element
            this.cursor = this.cursor.getNext();
            this.head = this.cursor;
        }
        else if (this.cursor.getNext() == null){    // remove last element
            gotoPrior(); // moves cursor one element before the last
            this.cursor.setNext(null); // deletes the remaining reference to the required element
            this.cursor = this.head; // moves cursor back to the start
        }
        else {      // remove element from the middle
            SNode<T> followingNode = this.cursor.getNext();
            gotoPrior(); // moves cursor one element before the one we delete
            this.cursor.setNext(followingNode); // deletes the remaining reference to the required element
            gotoNext(); // moves cursor to the new net element
        }
    }

    @Override
    public void replace(Object newElement) {
        if (this.isEmpty()){
            return;
        }
        if (newElement == null){
            System.out.println("Can't insert a null element");
            return;
        }
        this.cursor.setElement( ((SNode<T>) newElement).getElement() );
    }

    @Override
    public void clear() {
        /*
         * We clear the list by deleting the reference to the first element.
         * Because the first element isn't referenced by any object anymore,
         * it will be removed by the Garbage Collector.
         * Thus- the list will collapse and all the elements will be removed
         * by the Garbage Collector.
         */
        this.cursor = null;
        this.head = null;
    }

    @Override
    public boolean isEmpty() {
        if (this.head == null){
            // System.out.println("List is empty");
            return true;
        }
        return false;
    }

    @Override
    public boolean gotoBeginning() {
        if (!this.isEmpty()){
            this.cursor = this.head;
            return true;
        }
        else {
            return false;
        }
    }

    @Override
    public boolean gotoEnd() {
        if (!this.isEmpty()){
            while (this.cursor.getNext() != null){
                this.cursor = this.cursor.getNext();
            }
            return true;
        }
        else {
            return false;
        }
    }

    @Override
    public boolean gotoNext() {
        if (this.isEmpty()){
            return false;
        }
        if (this.cursor.getNext() != null){
            this.cursor = this.cursor.getNext();
            return true;
        }
        return false;
    }

    @Override
    public boolean gotoPrior() {
        if (this.isEmpty()){
            return false;
        }
        if (this.cursor == this.head){
            return false;
        }
        else {
            SNode<T> temp = this.head;
            while (temp.getNext() != this.cursor){
                temp = temp.getNext();
            }
            this.cursor = temp;
            return true;
        }
    }

    @Override
    public SNode<T> getCursor() {
        if (this.isEmpty()){
            return null;
        }
        return this.cursor;
    }

    @Override
    public String toString() {
        String res = "{";
        SNode<T> tempCursor = this.head;
        while (tempCursor != null){
            res += tempCursor;
            tempCursor = tempCursor.getNext();
            if (tempCursor!=null)
                res += ",";
        }
        return res;
    }

    public void printSLinkedList(){
        SNode<T> tempCursor = this.head;
        System.out.print("{");
        while (tempCursor != null){
            System.out.print(tempCursor);
            tempCursor = tempCursor.getNext();
            if (tempCursor!=null)
                System.out.print(",");
        }
        System.out.print("}\n");
    }
}
