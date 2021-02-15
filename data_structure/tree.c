/*************************************************************************
	> File Name: 5.binary_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Feb 2021 11:16:07 AM CST
 ************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 节点
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

// 二叉树
typedef struct Tree {
    Node *root;
    int n; // 节点数量
} Tree;

// 节点初始化
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

// 树初始化
Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

void clearNode(Node *node) {
    if (node == NULL) return ;
    clearNode(node->lchild);   // 递归形式去释放内存！！！棒
    clearNode(node->rchild);
    free(node);
    return ;
}

// 释放内存
void clear(Tree *tree) {
    if (tree == NULL) return ;
    clearNode(tree->root);
    free(tree);
    return ;
}

Node *insert_node(Node *root, int val, int *flag) {
    if (root == NULL) { // 写=则发生了段错误
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root; // 若与根节点的数值相等则直接返回
    if (val < root->data) root->lchild = insert_node(root->lchild, val, flag);
    else root->rchild = insert_node(root->rchild, val, flag);
    return root;
}

// 插入节点   二叉排序树，二叉查找树
void insert(Tree *tree, int val) {
    int flag = 0;
    tree->root = insert_node(tree->root, val, &flag);  // 返回值是整棵树的根节点
    tree->n += flag;
    return ;
} 

// 前序遍历
void pre_order_node(Node *node) {
    if (node == NULL) return ;
    printf("%d ", node->data);
    pre_order_node(node->lchild);
    pre_order_node(node->rchild);
    return ;
    
}

void pre_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("pre_order: ");
    pre_order_node(tree->root);
    printf("\n");
    return ;
}

// 中序遍历
void in_order_node(Node *node) {
    if (node == NULL) return ;
    in_order_node(node->lchild);
    printf("%d ", node->data);
    in_order_node(node->rchild);
    return ;
}

void in_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("in_order: ");
    in_order_node(tree->root);
    printf("\n");
    return ;
}

// 后序遍历
void post_order_node(Node *node) {
    if (node == NULL) return ;
    post_order_node(node->lchild);
    post_order_node(node->rchild);
    printf("%d ", node->data);
    return ;  
}

void post_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("post_order: ");
    post_order_node(tree->root);
    printf("\n");
    return ;
}

// 输出广义表的方法

void output_node(Node *root) {
    if (root == NULL) return ;
    printf("%d", root->data);
    if (root->lchild == NULL && root->rchild == NULL) return ;
    printf("(");
    output_node(root->lchild);
    printf(",");
    output_node(root->rchild);
    printf(")");
    return ;
}

void output(Tree *tree){
    if (tree == NULL) return ;
    printf("tree(%d) : ", tree->n);
    output_node(tree->root);
    printf("\n");
    return ;
    
} 


int main() {
    
    srand(time(0));
    Tree *tree = getNewTree();
    #define max_op 10
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        insert(tree, val);
        output(tree);
    }
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    #undef max_op
    clear(tree);
    return 0;
}
