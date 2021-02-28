/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 11:23:27 AM CST
 ************************************************************************/
// 添加了原地翻转的功能函数
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next; // 因为此时类型别名还未生效，所以需要完整的结构体定义
} ListNode; 

typedef struct List {
    //ListNode *head;  
    //  为了方便插入定义成一个虚拟头节点, 而不是指向头节点
    ListNode head; 
    int length; // 当前链表的长度
} List;

// 函数声明
ListNode *getNewNode(int); // 去生成一个节点
List *getLinkList(); // 获得一个链表
void clear_node(ListNode *); //释放节点的空间
void clear(List *);  // 释放链表的空间
int insert(List *, int, int); //插入
int erase(List *, int); // 删除一个节点
void output(List *);

int main() {

    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int ind = rand() % (l->length + 3) - 1;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert, ind = %d\n", ind);
                printf("insert %d at %d to list = %d\n", val, ind, insert(l, ind, val));
            } break;
            case 3: {
                printf("erase, ind = %d\n", ind);
                printf("erase a item at %d from list = %d\n", ind, erase(l, ind));
            } break;
        }
        output(l);
        printf("\n");
    }
    #undef max_op
    clear(l);

    return 0;
}
// 函数定义

// 生成一个节点
ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

// 初始化一个链表
List *getLinkList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL; // 虚拟头节点
    l->length = 0;
    return l;
}

// 插入操作
int insert(List *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next; // 从虚拟节点开始走的，所以会走到需要插入的前一个节点
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

// 删除一个节点
int erase(List *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 1;
}

void output(List *l) {
    if (l == NULL) return ;
    printf("List: [");
    ListNode *p = l->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return ;
}

void clear_node(ListNode * node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while(p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(l);
    return ;
}

/////////////////////////////////////////////////////////////////////////////
/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 11:23:27 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)


typedef struct ListNode {
    int data;
    struct ListNode *next; // 因为此时类型别名还未生效，所以需要完整的结构体定义
} ListNode; 

typedef struct List {
    //ListNode *head;  
    //  为了方便插入定义成一个虚拟头节点, 而不是指向头节点
    ListNode head; 
    int length; // 当前链表的长度
} List;

// 函数声明
ListNode *getNewNode(int); // 去生成一个节点
List *getLinkList(); // 获得一个链表
void clear_node(ListNode *); //释放节点的空间
void clear(List *);  // 释放链表的空间
int insert(List *, int, int); //插入
int erase(List *, int); // 删除一个节点
void output(List *);
void reverse(List *); // 原地翻转链表


int main() {

    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int ind = rand() % (l->length + 3) - 1;
        int op = rand() % 5;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert, ind = %d\n", ind);
                printf("insert %d at %d to list = %d\n", val, ind, insert(l, ind, val));
            } break;
            case 3: {
                printf("erase, ind = %d\n", ind);
                printf("erase a item at %d from list = %d\n", ind, erase(l, ind));
            } break;
            case 4: {
                printf(GREEN("reverse the list\n"));
                reverse(l);
            }
        }

        output(l);
        printf("\n");
    }
    #undef max_op
    clear(l);

    return 0;
}
// 函数定义

// 生成一个节点
ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

// 初始化一个链表
List *getLinkList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL; // 虚拟头节点
    l->length = 0;
    return l;
}

// 插入操作
int insert(List *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next; // 从虚拟节点开始走的，所以会走到需要插入的前一个节点
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

// 删除一个节点
int erase(List *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 1;
}

void reverse(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    l->head.next = NULL;
    while (p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return ;
}


void output(List *l) {
    if (l == NULL) return ;
    printf("List: [");
    ListNode *p = l->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return ;
}

void clear_node(ListNode * node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while(p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(l);
    return ;
}
