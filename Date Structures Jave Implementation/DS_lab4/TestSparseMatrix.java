package com.company;

public class TestSparseMatrix {

    private SparseMatrix[] matricesArray;

    public TestSparseMatrix(){}

    public void startTest(){
        SparseMatrix mat1 = new SparseMatrix(4, 0);
        System.out.println(mat1);

        mat1.put(1, 2, 1);
        mat1.put(1, 4, 4);
        mat1.put(4, 2, 6);
        System.out.println(mat1);
        /*
        mat1.transpose();
        System.out.println(mat1);

        mat1.transpose();
        mat1.multByConstant(2);
        System.out.println(mat1);
*/
        // ------- TEST NEW FUNCTION -------
        SparseMatrix mat1_t = new SparseMatrix(4, 0);
        mat1_t.put(4, 1, 4);
        mat1_t.put(2, 1, 1);

        mat1_t.put(2, 4, 6);
        System.out.println(mat1_t);

        System.out.println("is mat1_t good? " + mat1.isAequalBt(mat1, mat1_t));
    }
}
