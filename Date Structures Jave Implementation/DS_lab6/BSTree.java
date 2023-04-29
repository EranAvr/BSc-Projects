package com.company;

public class BSTree {

    private BSTreeNode root;

    public BSTree (){
        this.root = null;
    }

    // Binary search tree manipulation methods
    public void insert ( int newKey ){
        BSTreeNode node = new BSTreeNode(newKey, null, null);
        /*if (this.root==null){
            this.root = node;
            return;
        }*/
        this.root = this.recInsert(this.root, node);
    }
    public BSTreeNode retrieve ( int searchKey ){
        return this.recRetrieve(this.root, searchKey);
    }
    public void clear (){
        /*
         * We delete the only reference to root's left and right nodes.
         * That way the Garbage Collector deletes the first un-referenced nodes
         * and so forth to the next ones, until all nodes are erased.
         */
        this.root.setLeft(null);
        this.root.setRight(null);
        this.root = null;
    }
    public void delete (int key) {
        recDelete(root, key);
    }
    public BSTreeNode getRoot(){ return this.root; }

    // Binary search tree status methods
    public boolean isEmpty (){
        return (this.root==null);
    }
    public boolean isFull (){
        return false;
    }

    // find methods
    public BSTreeNode findMin(BSTreeNode root) {
        return recFindMin(root);
    }
    public BSTreeNode findMax(BSTreeNode root) {
        return recFindMax(root);
    }
    public BSTreeNode findParent(int key) {
        return recFindParent(root, key);
    }

    // Print tree methods
    public String Preorder(){
        String res = "";
        recPreorder(this.root, res);
        System.out.println();
        return res;
    }
    public String Inorder(){
        String res = "";
        recInorder(this.root, res);
        System.out.println();
        return res;
    }
    public String Postorder(){
        String res = "";
        recPostorder(this.root, res);
        System.out.println();
        return res;
    }

    // Recursive partners of the public member methods --- Insert these methods here.
    private BSTreeNode recInsert(BSTreeNode root, BSTreeNode node){
        if (root==null){
            return node;
        }
        else if (node.getKey()<root.getKey()){
            root.setLeft(recInsert(root.getLeft(), node));
        }
        else if (node.getKey()>root.getKey()){
            root.setRight(recInsert(root.getRight(), node));
        }
        return root;
    }
    private BSTreeNode recRetrieve(BSTreeNode root, int key){
        if (root==null){
            return null;
        }
        if (key == root.getKey()){
            return root;
        }
        else if (key<root.getKey()){
            return recRetrieve(root.getLeft(), key);
        }
        else if (key>root.getKey()){
            return recRetrieve(root.getRight(), key);
        }
        return root;
    }
    private void recPreorder(BSTreeNode root, String res){
        if (root == null){
            return;
        }
        System.out.print(root.getKey() + " ");
        recPreorder(root.getLeft(), res);
        recPreorder(root.getRight(), res);
    }
    private void recInorder(BSTreeNode root, String res){
        if (root == null){
            return;
        }
        recPreorder(root.getLeft(), res);
        System.out.print(root.getKey() + " ");
        recPreorder(root.getRight(), res);
    }
    private void recPostorder(BSTreeNode root, String res){
        if (root == null){
            return;
        }
        recPreorder(root.getLeft(), res);
        recPreorder(root.getRight(), res);
        System.out.print(root.getKey() + " ");
    }
    private BSTreeNode recFindMin(BSTreeNode root){
        if (root.getLeft() == null){
            return root;
        }
        else {
            return recFindMin(root.getLeft());
        }
    }
    private BSTreeNode recFindMax(BSTreeNode root){
        if (root.getRight() == null){
            return root;
        }
        else {
            return recFindMax(root.getRight());
        }
    }
    private BSTreeNode recFindParent(BSTreeNode root, int key){
        if ((root.getLeft()!=null && key == root.getLeft().getKey())
                || (root.getRight()!=null && key == root.getRight().getKey())){
            return root;
        }
        else if (root.getLeft()!=null && key < root.getKey()){
            return recFindParent(root.getLeft(), key);
        }
        else if (root.getRight()!=null && key > root.getKey()){
            return recFindParent(root.getRight(), key);
        }
        return null;    // In case the key doesn't exists in tree
    }
    private BSTreeNode recDelete(BSTreeNode root, int key){
        if (root == null)
            return root;

        if (key < root.getKey())
            root.setLeft(recDelete(root.getLeft(), key));
        else if (key > root.getKey())
            root.setRight(recDelete(root.getRight(), key));
        else {
            if (root.getLeft() == null)
                return root.getRight();
            else if (root.getRight() == null)
                return root.getLeft();

            root.setKey(findMin(root.getRight()).getKey());
            root.setRight(recDelete(root.getRight(), root.getKey()));
        }
        return root;
    }
}
