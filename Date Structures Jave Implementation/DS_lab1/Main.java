package com.company;

import java.awt.*;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StreamTokenizer;

public class Main {

    public static void main(String[] args) {

        ArrayPointList points = new ArrayPointList();
        TestPointListTok test = new TestPointListTok();
        test.read_points(points);
    }
}
