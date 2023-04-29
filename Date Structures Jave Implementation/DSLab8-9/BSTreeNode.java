package com.company;

public class BSTreeNode {

    private int key;
    private BSTreeNode left, right;

    public BSTreeNode ( int key, BSTreeNode leftPtr, BSTreeNode rightPtr ){
        this.setKey(key);
        this.setLeft(leftPtr);
        this.setRight(rightPtr);
    }

    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public BSTreeNode getLeft() {
        return left;
    }

    public void setLeft(BSTreeNode left) {
        this.left = left;
    }

    public BSTreeNode getRight() {
        return right;
    }

    public void setRight(BSTreeNode right) {
        this.right = right;
    }

    @Override
    public String toString() {
        String leftK = (left == null ? "null" : left.getKey()) + "";
        String rightK = (right == null ? "null" : right.getKey()) + "";
        return "BSTreeNode{" +"key=" + key +", left=" + leftK +", right=" + rightK +'}';
    }
}
