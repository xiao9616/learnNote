package com.xiao;


public class node {

    int value;

    node leftChild;

    node rightChild;

    public node(int value) {
        this.value = value;
    }

    public node(int value, node leftChild, node rightChild) {
        this.value = value;
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }

    @Override
    public String toString() {
        return "node{" +
                "value=" + value +
                ", leftChild=" + leftChild +
                ", rightChild=" + rightChild +
                '}';
    }
}
