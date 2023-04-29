package com.company;

public class Main {

    public static void main(String[] args) {
	// write your code here

        TestBSTree test = new TestBSTree();
        test.startTest();
        BSTree tree = new BSTree();
        tree.insert(1);
        tree.insert(2);
        tree.insert(5);
        tree.insert(3);
        tree.insert(4);
        tree.insert(-1);
        tree.insert(-5);
        tree.insert(-3);
        tree.insert(-6);
        System.out.println("Tree root: " + tree.getRoot());
        System.out.println(tree.Inorder());
        System.out.println("Min: " + tree.findMin(tree.getRoot()));
        System.out.println("Max: " + tree.findMax(tree.getRoot()));
        System.out.println("Parent: " + tree.findParent(17));
        System.out.println("Retrieve: " + tree.retrieve(3));
    }
}
