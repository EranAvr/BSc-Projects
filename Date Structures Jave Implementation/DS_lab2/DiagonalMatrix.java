package com.company;

class dMatrixException extends Exception{
    public dMatrixException(String msg){
        super("dMatrixException: " + msg);
    }
}

public class DiagonalMatrix implements Matrix {

    private double[] dMatrix;
    private final int N;
    private int constant = 1;

    public DiagonalMatrix(int size) throws dMatrixException{
        this.N = size;
        if (size <= 0){
            throw new dMatrixException("Can't initialize matrix. Size should be greater than 0");
        }
        this.dMatrix = new double[2*N -1];
    }

    public DiagonalMatrix() throws dMatrixException {
        this(MAX_SIZE);
    }

    @Override
    public int getSize() {
        return this.N;
    }

    @Override
    public double get(int i, int j) {
        if (i<0 || j<0 || i>=getSize() || j>=getSize()){
            System.out.println("Can't get item from matrix. Indexes are out of bound");
            return -1;
        }
        return dMatrix[i + j] * this.constant;
    }

    @Override
    public void put(int i, int j, double x) {
        if (i<0 || j<0 || i>=getSize() || j>=getSize()){
            System.out.println("Can't get item from matrix. Indexes are out of bound");
        }
        else {
            dMatrix[i + j] = (x / this.constant);
            System.out.println("Matrix changed successfully");
        }
    }

    @Override
    public void transpose() {
        // Symmetric matrix doesn't change in transpose.
    }

    @Override
    public void multByConstant(int C) {
        if (C <= 0){
            System.out.println("The multiplier must be greater than 0");
        }
        else {
            this.constant = C;
            System.out.println("Matrix multiplied successfully");
        }
    }

    @Override
    public String toString() {
        String matrix_str = "";
        for (int i=0 ; i<getSize() ; i++){
            for (int j=0 ; j<getSize() ; j++){
                matrix_str += (this.get(i, j) + "\t");
            }
            matrix_str += "\n";
        }
        return matrix_str;
    }
}
