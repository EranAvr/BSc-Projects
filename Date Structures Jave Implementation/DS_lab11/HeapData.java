package com.company;

public class HeapData {
    private int priority;

    public HeapData(int val){
        this.priority = val;
    }

    public void setPriority(int p) {
        this.priority = p;
    }
    public int getPriority() {
        return priority;
    }

    @Override
    public String toString() {
        return "HeapData{" + getPriority() + '}';
    }
}
