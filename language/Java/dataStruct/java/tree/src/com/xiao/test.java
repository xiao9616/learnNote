package com.xiao;

public class test {
    public static void main(String[] args) {
        listBinaryTree binaryTree = new listBinaryTree(new node(1));
        node root = binaryTree.root;
        binaryTree.insert(10,root);
        binaryTree.insert(2,root);
        binaryTree.insert(3,root);
        binaryTree.insert(7,root);
        binaryTree.insert(8,root);
        binaryTree.insert(3,root);
        binaryTree.insert(5,root);
        binaryTree.insert(6,root);
        binaryTree.inOrderTraverse(binaryTree.root);

    }
}
