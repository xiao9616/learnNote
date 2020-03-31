#include <iostream>
// 面试题26：树的子结构
// 题目：输入两棵二叉树A和B，判断B是不是A的子结构。
#include "binaryTree.h"

using namespace std;

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2);

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2){
    bool result = false;
    if (pRoot1 != nullptr && pRoot2 != nullptr) {
        if (pRoot1->m_value == pRoot2->m_value) {
            result=DoesTree1HaveTree2(pRoot1, pRoot2);
        }
        if (!result) {
            result = HasSubtree(pRoot1->m_pLeft, pRoot2);
        }
        if (!result) {
            result = HasSubtree(pRoot1->m_pRight, pRoot2);
        }
    }
    return result;
}

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2){
    if (pRoot2 == nullptr) {
        return true;
    }
    if (pRoot1 == nullptr) {
        return false;
    }
    if (pRoot1->m_value != pRoot2->m_value) {
        return false;
    }
    return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
           DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}