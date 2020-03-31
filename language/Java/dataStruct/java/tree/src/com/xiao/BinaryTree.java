package com.xiao;

public interface BinaryTree {

    public boolean isEmpty();

    public int size(node root);

    public int getHeight(node root);

    public node findKey(int val, node root);

    public void preOrderTraverse(node root);

    public void inOrderTraverse(node root);

    public void postOrderTraverse(node root);

    public void preOrderByStack();

    public void inOrderByStack();

    public void postOrderByStack();

    public void levelOrderByStack();

    public void insert(int val, node root);

}
