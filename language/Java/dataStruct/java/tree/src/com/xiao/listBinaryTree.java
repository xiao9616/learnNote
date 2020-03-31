package com.xiao;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Queue;

public class listBinaryTree implements BinaryTree {

    public node root;

    public listBinaryTree(node root) {
        this.root = root;
    }

    @Override
    public boolean isEmpty() {
        return this.root == null;
    }

    @Override
    public int size(node root) {
        if (root == null) {
            return 0;
        } else {
            int nl = this.size(root.leftChild);
            int nr = this.size(root.rightChild);
            return nl + nr;
        }
    }

    @Override
    public int getHeight(node root) {
        if (root != null) {
            int nl = this.getHeight(root.leftChild);
            int nr = this.getHeight(root.rightChild);
            return nl > nr ? nl + 1 : nr + 1;
        } else {
            return 0;
        }

    }

    @Override
    public node findKey(int val, node root) {
        if (root == null) {
            return null;
        } else if (root.value == val) {
            return root;
        } else {
            node node1 = this.findKey(val, root.leftChild);
            node node2 = this.findKey(val, root.rightChild);
            if (node1 != null && node1.value == val) {
                return node1;
            } else if (node2 != null && node2.value == val) {
                return node2;
            } else {
                return null;
            }
        }
    }

    @Override
    public void preOrderTraverse(node root) {
        if (root != null) {
            System.out.print(root.value + "  ");
            this.preOrderTraverse(root.leftChild);
            this.preOrderTraverse(root.rightChild);
        }
    }

    @Override
    public void inOrderTraverse(node root) {
        if (root != null) {
            this.inOrderTraverse(root.leftChild);
            System.out.print(root.value + "  ");
            this.inOrderTraverse(root.rightChild);
        }
    }

    @Override
    public void postOrderTraverse(node root) {
        if (root != null) {
            this.postOrderTraverse(root.leftChild);
            this.postOrderTraverse(root.rightChild);
            System.out.print(root.value + "  ");
        }
    }

    @Override
    public void preOrderByStack() {

    }

    @Override
    public void inOrderByStack() {
        Deque<node> stack = new LinkedList<>();
        node current = root;
        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.push(current);
                current = current.leftChild;
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
                System.out.println(current.value);
                current = current.rightChild;
            }
        }
    }

    @Override
    public void postOrderByStack() {

    }

    @Override
    public void insert(int val,node root) {
        if (root == null) {
            root = new node(val);
        } else {
            if (root.value == val) {
                return;
            }

            if (val < root.value) {
                if (root.leftChild == null) {
                    root.leftChild = new node(val);
                } else {
                    this.insert(val, root.leftChild);
                }
            } else {
                if (root.rightChild == null) {
                    root.rightChild = new node(val);
                } else {
                    this.insert(val,root.rightChild);
                }
            }
        }
    }

    @Override
    public void levelOrderByStack() {
        if (root == null) {
            return;
        }
        Queue<node> queue = new LinkedList<>();
        queue.add(root);
        while (queue.size() != 0) {
            int len = queue.size();
            for (int i = 0; i < len; i++) {
                node temp = queue.poll();
                System.out.println(temp.value);
                if (temp.leftChild != null) {
                    queue.add(temp.leftChild);
                }
                if (temp.rightChild != null) {
                    queue.add(temp.rightChild);
                }
            }
        }
    }
}
