package com.company;

public class Heap {
    // Constant
    private static final int DEF_MAX_HEAP_SIZE = 10;

    // Data members
    private int size;           // Actual number of elements in the heap
    private HeapData[] elements; // Array containing the heap elements\
    private int nextIndex;

    // Constructors and helper method setup
    public Heap()               // Constructor: default size
    {
        this(DEF_MAX_HEAP_SIZE);
    }
    public Heap(int maxNumber)  // Constructor: specific size
    {
        if (maxNumber<1)
            return;
        this.size = maxNumber;
        this.elements = new HeapData[size];
        //this.elements[0] = new HeapData(Integer.MIN_VALUE);  // Initialize first cell with minimum integer value
        this.nextIndex = 1;
    }

    // Heap manipulation methods
    public void insert(HeapData newElement) //  insert new element
    {
        if (isFull())
            return;
        this.elements[nextIndex] = newElement;
        this.pushNewUp(elements, nextIndex);
        this.nextIndex++;
    }
    public HeapData removeMin() // Remove min priority element
    {
        if (isEmpty())
            return null;
        HeapData temp_element = new HeapData(elements[1].getPriority());
        pushEmptyDown(elements, 1);
        this.nextIndex--;
        return temp_element;
    }
    public void clear()         // Clear heap: Make it efficient!!
    {
        this.elements = new HeapData[size];
        this.nextIndex = 1;
    }

    // Heap status methods
    public boolean isEmpty() {
        return (elements[1] == null);
    }
    public boolean isFull() {
        return (elements[size-1] != null);
    }

    // Helper methods
    private void pushNewUp(HeapData[] array, int i) {
        int parent = i / 2;
        if (parent == 0){
            return;
        }
        if (array[parent].getPriority() > array[i].getPriority()){
            swap_prios(array[parent], array[i]);
        }
        pushNewUp(array, parent);
    }
    private void pushEmptyDown(HeapData[] array, int root) {
        int l = root*2;
        int r = root*2 + 1;
        int min = findMinChildIndex(array, l, r);

        if (min==-1) {   // return condition
            array[root] = null;
            return;
        }

        array[root].setPriority(array[min].getPriority());     // copy min child priority to root of subtree
        pushEmptyDown(array, min);  // go and check subtree
    }
    private void swap_prios(HeapData a, HeapData b) {
        int temp_val = a.getPriority();
        a.setPriority(b.getPriority());
        b.setPriority(temp_val);
    }
    private int findMinChildIndex(HeapData[] array, int l, int r) {
        if (l>=array.length || (array[l]==null && array[r]==null))
            return -1;
        else if (r<array.length && (array[l]==null))
            return r;
        else if (r<array.length && (array[r]==null))
            return l;
        else
            return ( array[l].getPriority()<array[r].getPriority() ? l : r );
    }

    // Output the heap structure
    public String toString() {
        if (isEmpty()){
            return "Empty Heap";
        }
        String res = "";
        for (HeapData val : elements){
            if (val==null)
                continue;
            res += val.getPriority() + ", ";
        }
        return res;
    }
}
