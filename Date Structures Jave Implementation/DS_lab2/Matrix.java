package com.company;

public interface Matrix {

    final static int MAX_SIZE = 100;

    int getSize();                          // return the number of rows )=number
                                            // of columns=N( of the matrix.
    double get (int i, int j);              // Precondition: 0 ≤ i,j ≤ N.
                                            // Postcondition: returns the value of the
                                            // element at the place )i,j(.
    void put(int i, int j, double x);       // Precondition: 0 ≤ i,j ≤ n
                                            //Postcondition: updates the value of the element
                                            // at the place )i,j( to be equal to x.
    void transpose();                       // Precondition: None.
                                            //Postcondition: configure the matrix to be
                                            // transpose matrix. Do it in O(1)!
    void multByConstant (int C);            // Precondition: C>0.
                                            // Postcondition: returns the matrix, in which every
                                            // element is multiplied by positive integer
                                            // constant C. Do it in O(1)!
}
