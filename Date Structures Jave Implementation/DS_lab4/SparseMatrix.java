package com.company;

public class SparseMatrix implements Matrix {

    private int constant = 1;
    private SLinkedList<SparseMatrixEntry> vList;
    private int size;
    private int N;
    private boolean transposed;

    SparseMatrix (int size, double defaultValue){
        this.vList = new SLinkedList<>();
        this.N = size;
        this.size = N*N;
        this.transposed = false;

        put(-1, -1, defaultValue);  // Saves the common value.
    }

    public SparseMatrix MatrixAddition(SparseMatrix A, SparseMatrix B){
        SparseMatrix res = new SparseMatrix(A.size, A.get(-1, -1) + B.get(-1, -1));

        /*  NOT FINISHED
        A.vList.gotoBeginning();
        B.vList.gotoBeginning();
        do {

        } while (A.vList.gotoNext());
        */

        return res;
    }
    public SparseMatrix MatrixSubtraction(SparseMatrix A, SparseMatrix B){
        SparseMatrix res = new SparseMatrix(A.size, A.get(-1, -1) - B.get(-1, -1));
        return res;
    }

    public boolean isAequalBt(SparseMatrix A, SparseMatrix B){
        A.vList.gotoBeginning();
        B.vList.gotoBeginning();
        do {
            if (!areEntriesEqual(A.vList.getCursor(), B.vList.getCursor())){
                return false;
            }
        } while (A.vList.gotoNext() && B.vList.gotoNext());

        return true;
    }
    private boolean areEntriesEqual(SparseMatrixEntry e1, SparseMatrixEntry e2){
        if (e1.getI()==e2.getJ() && e1.getJ()==e2.getI() && e1.getValue()==e2.getValue())
            return true;
        else
            return false;
    }

    @Override
    public int getSize() {
        return this.N;
    }

    @Override
    public double get(int i, int j) {
        if (this.transposed){
            int tempIndex = i;
            i = j;
            j = tempIndex;
        }
        this.vList.gotoBeginning();
        if (i == -1 && j == -1){    // For inner purposes, to get the default value quickly.
            return this.vList.getCursor().getValue() * constant;
        }
        SparseMatrixEntry tempEntry;
        if ((i>=0 && i<N) && (j>=0 && j<N)){
            do {
                tempEntry = this.vList.getCursor();
                if (tempEntry.getI()==i && tempEntry.getJ()==j){
                    return this.vList.getCursor().getValue() * constant;
                }
            } while (this.vList.gotoNext());
            // For the default value:
            this.vList.gotoBeginning();
            return this.vList.getCursor().getValue() * constant;
        }
        System.out.println("indexes are out of bound");
        return -1;
    }

    @Override
    public void put(int i, int j, double x) {
        i -= 1; j -= 1; // Convert 2D array indexes to matrix indexes
        SparseMatrixEntry tempEntry = new SparseMatrixEntry(x/this.constant, i, j);
        SNode<SparseMatrixEntry> tempNode = new SNode<>(tempEntry, null);
        this.vList.insert(tempNode);
    }

    @Override
    public void transpose() {
        /*
         * To achieve O(1), I created a flag variable.
         * In case transpose=true, a condition will be activated in function get().
         */
        this.transposed = !this.transposed;
    }

    @Override
    public void multByConstant(int C) {
        this.constant = C;
    }

    @Override
    public String toString() {
        String res = "";
        for (int i=0 ; i<N ; i++){
            for (int j=0 ; j<N ; j++){
                res += (this.get(i, j) + "\t");
            }
            res += "\n";
        }

        return res;
    }
}
