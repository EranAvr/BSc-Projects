package com.company;

import java.awt.Point;
import java.util.Arrays;

public class ArrayPointList implements PointList {
    private Point[] points;
    private int size;
    private int cursor;

    public ArrayPointList() {
        this.points = new Point[PointList.MAX_SIZE];
        Arrays.fill(points, null);
        this.size = points.length;
    }

    public ArrayPointList(int maxSize) {
        this.points = new Point[maxSize];
        Arrays.fill(points, null);
        this.size = points.length;
    }

    @Override
    public void append(Point newPoint) {
        if (isFull()){
            System.out.println("storage is full! can't add point.");
        }
        else {
            if (goToEnd()){
                cursor++;
            }
            this.points[cursor] = newPoint;
        }
    }

    @Override
    public void clear() {
        if (isEmpty()){
            System.out.println("storage is already empty.");
        }
        else {
            Arrays.fill(points, null);
        }
    }

    @Override
    public boolean isEmpty() {
        return (this.points[0] == null);
    }

    @Override
    public boolean isFull() {
        return (this.points[MAX_SIZE - 1] != null);
    }

    @Override
    public boolean goToBeginning() {
        if (isEmpty()){
            return false;
        }
        else {
            cursor = 0;
            return true;
        }
    }

    @Override
    public boolean goToEnd() {
        if (isEmpty()){
            this.cursor = 0;
            return false;
        }
        else {
            this.cursor = MAX_SIZE - 1;
            for (; cursor>0 ; cursor--){
                if (this.points[cursor] == null){
                    continue;
                }
                else {
                    break;
                }
            }
            return true;
        }
    }

    @Override
    public boolean goToNext() {
        if ((cursor < MAX_SIZE-1) && (points[cursor+1] != null)){
            cursor++;
            return true;
        }
        else {
            return false;
        }
    }

    @Override
    public boolean goToPrior() {
        if (cursor > 0){
            cursor--;
            return true;
        }
        else {
            return false;
        }
    }

    @Override
    public Point getCursor() {
        if (isEmpty()){
            return null;
        }
        else {
            return new Point(points[cursor].x, points[cursor].y);
        }
    }

    @Override
    public String toString() {
        String temp_res = "[";
        if (isEmpty()){
            return "Empty list";
        }
        else {
            for (Point p: this.points){
                if (p != null) {
                    temp_res += "(" + p.x + ", " + p.y + "),";
                }
                else {
                    break;
                }
            }
            temp_res += "]";
        }
        return temp_res;
    }
}
