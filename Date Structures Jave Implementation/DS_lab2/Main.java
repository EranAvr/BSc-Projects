package com.company;

public class Main {

    public static void main(String[] args) {

        try {
            DiagonalMatrix mat = new DiagonalMatrix(4);
            TestDiagMatrix tester = new TestDiagMatrix();
            tester.read_matrix(mat);
        }
        catch (dMatrixException e){
            System.out.println(e.getMessage());
        }
    }
}
