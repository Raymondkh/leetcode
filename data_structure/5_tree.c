/*************************************************************************
	>文件名：5.binary_tree.cpp
	作者：  
	> Mail: 
	> Created Time: Mon 15 Feb 2021 11:16:07 AM CST
 ************************************************************************/
// 二叉树代码及周边，链表形式
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
	// 递归的返回条件
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root; // 若与根节点的数值相等则直接返回
	// [1]    32137 segmentation fault  ./a.out
	// 递归回不来，爆栈
    if (val < root->data) root->lchild = insert_node(root->lchild, val, flag);
    else root->rchild = insert_node(root->rchild, val, flag);
    return root;
}

// 插入节点   二叉排序树，二叉查找树
// 即在root, lchild, rchild中，lchild->data < root->data < rchild->data
// 那是中序遍历会是递增的情况？？
/*pre_order: 57 25 10 9 27 96 71 64 59 77 
in_order: 9 10 25 27 57 59 64 71 77 96  确实是的vim
post_order: 9 10 27 25 59 64 77 71 96 57 */

void insert(Tree *tree, int val) {
    int flag = 0; // 去判断是否成功插入节点，用来计算tree->n
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
////////////////////////////////////////////////////////////////////////////////
/*************************************************************************
	> File Name: 8.table_to_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Feb 2021 02:48:25 PM CST
 ************************************************************************/
// 将广义表转化为二叉树代码，使用了栈的结构
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 方法定义一个栈 或 使用系统栈（递归）

// 树
typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int length;
} Tree;

// 树的结构操作
Node *getNewNode(char c) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = c;
    p->lchild = p->rchild = NULL; 
    return p;
// 这里返回的是结构体指针，而栈是存储这个的话，
}

Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->length = 0;
    return tree;
}

void clear_node(Node *node) {
    if (node == NULL) return ;
    clear_node(node->lchild);
    clear_node(node->rchild);
    free(node);
    return ;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

// 栈
typedef struct Stack {
    int top, size;
    //char *data; // 但在此时因为是存储树形节点的地址
    Node **data; // 注意是存地址而不是直接的节点
} Stack;

/*
压入栈的是这个temp = getNewNode(str[0]);返回值是Node *是一个指针
Node *getNewNode(char c) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = c;
    p->lchild = p->rchild = NULL; 
    return p;
// 这里返回的是结构体指针，而栈是存的是结构体指针
}
Node *data;   // data存放的是指向Node的指针
Node **data;   // data存放的是指向Node指针的指针，虽然有点绕口，但是这个是指向指针的，所以就是Node **

类比：
int *a; // 变量a存放的是指向整形的指针
int **a; // 变量a存放的是指正整形指针的指针

在于之前的写的栈的代码对比：
typedef struct Stack {
    int *data; // 指向整形元素的data
    int top, size; // 栈顶指针， 栈的容量size
} Stack;
这里面的是int *data; 因为下面入栈的是整形值, 所以data就是指向整形的指针
// 入栈
int push(Stack *s, int val) {
    if (s == NULL) return 0;
    //if (s->top + 1 == s->size) return 0; // 满了
    if (s->top + 1 == s->size) {
        // 自动扩容
        if (!expand(s)) return 0;
        printf(GREEN("success expend Stack!, size = %d\n"), s->size);
    } 
    s->data[++(s->top)] = val;
    return 1;
}
*/


Stack *init_stack(int n) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (Node **)malloc(sizeof(Node *) * n);  // sizeof(Node *)
    stack->top = -1;
    stack->size = n;
    return stack;
}

void clear_stack(Stack *stack) {
    if (stack == NULL) return ;
    free(stack->data);
    free(stack);
    return ;
}

Node *top(Stack *stack) {
    return stack->data[stack->top];
}

int empty(Stack *stack) {    
    return stack->top == -1;
}

int push(Stack *stack, Node *val) {
    if (stack == NULL) return 0;
    if (stack->top + 1 == stack->size) return 0; // 已满，需要自动扩容
    // 不过建立栈的时候都是按照字符串长度来创建的，所以肯定是足够大的
    stack->data[++(stack->top)] = val;
    return 1;
}

int pop(Stack *stack) {
    if (stack == NULL) return 0;
    if (empty(stack)) return 0; // 栈是空的
    stack->top -= 1;
    return 1;
}

// 前序遍历
void pre_order_node(Node *root) {
    if (root == NULL) return ;
    printf("%c ", root->data);
    pre_order_node(root->lchild);
    pre_order_node(root->rchild);
    return ;
}

void pre_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("pre_order(%d): ", tree->length);
    pre_order_node(tree->root);
    printf("\n");
    return ;
}

// 中序遍历
void in_order_node(Node *root) {
    if (root == NULL) return ;
    in_order_node(root->lchild);
    printf("%c ", root->data);
    in_order_node(root->rchild);
    return ;
}

void in_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("in_order(%d) : ", tree->length);
    in_order_node(tree->root);
    printf("\n");
    return ;
}


// 后序遍历
void post_order_node(Node *root) {
    if (root == NULL) return ;
    post_order_node(root->lchild);
    post_order_node(root->rchild);
    printf("%c ", root->data);
    return ;
}

void post_order(Tree *tree) {
    if (tree == NULL) return ;
    printf("post_order(%d) : ",tree->length);
    post_order_node(tree->root);
    printf("\n");
    return ;
}

Node *build(const char *str, int *node_num) {
    Stack *s = init_stack(strlen(str)); // str有多长栈就开多大
    int flag = 0;
    Node *temp = NULL, *p = NULL;
    while (str[0]) {
        switch (str[0]) {
            case '(': {
                push(s, temp);
                flag = 0;
            } break;
            case ')': {
                p = top(s); 
		// 这里为什么要记录，有一种特殊情况,用于存放之后一个根节点
                pop(s);
            } break;
            case ',': {
                flag = 1;  // 经过,号则为右孩子
            } break;
            case ' ': break;
            default:
                temp = getNewNode(str[0]);
		//!empty(s)即栈非空为真, flag判断是左孩子还是右孩子
            	if (!empty(s) && flag == 0) {
               		top(s)->lchild = temp; // top(s)上一个字母
            	} else if (!empty(s) && flag == 1) {
                	top(s)->rchild = temp;
            	}
            	++(*node_num);  // 记录节点数的增加
             } break;
    	}
        ++str; // str的首地址移动，相当于一只向后去读字符
    }
    clear_stack(s);
    if (temp && !p) p = temp; // 此时就是整棵树只有根节点一个节点
    return p; // 最后一个元素就是根节点, 但假设整个广义表只有一个根节点，这样写就会出错,所以需要上面判断

}

int main() {
    char str[1000] = {0};
    int node_num = 0; // 记录节点的个数
    // %[^\n]s  ^非 \n换行 即除了换行”
    scanf("%[^\n]s", str);   // 注意不要写成%s[^\n]会被空格打断的
    printf("test: %s\n", str);
    getchar(); // 吞掉上一个换行
    Tree *tree = getNewTree();
    // build()方法就是讲字符串还原成二叉树然后返回根节点
    tree->root = build(str, &node_num);
    tree->length = node_num;
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    return 0;
}
