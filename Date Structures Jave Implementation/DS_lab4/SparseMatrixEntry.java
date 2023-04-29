package com.company;

public class SparseMatrixEntry {

    private double value; // Sparse Matrix element
    private int i; // Index i
    private int j; // Index j

    public SparseMatrixEntry(double val, int i, int j) {
        setValue(val);
        setI(i);
        setJ(j);
        //this.next = null;
    }

    public int getI() {
        return this.i;
    } //
    public void setI(int i) {
        this.i = i;
    }
    public int getJ() {
        return this.j;
    }
    public void setJ(int j) {
        this.j = j;
    }
    public double getValue() {
        return this.value;
    }
    public void setValue(double newVal) {
        this.value = newVal;
    }

    @Override
    public String toString() {
        return "SparseMatrixEntry{ " + "value=" + value + ", i=" + i + ", j=" + j + '}';
    }
}
