/*************************************************************************
	> File Name: 12.hash_table.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Feb 2021 01:05:34 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *str;
    struct Node *next;  
} Node;

// 哈希函数  BKDR_hash
typedef struct HashTable {
    Node **data; // 因为data里面存的是Node *,而不是Node
    int size;
} HashTable;

// 冲突处理方法 拉链法就是相同的就存在一个链表里，
// 就是在链表里搜索也不会有多少重复的吧？所以时间效率还是很高的
Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str); 
    // strdup是将str拷贝并返回拷贝后的地址
    // 这是因为str是传入的地址，之后要重新存在输入的新字符串，
    // 所以需要拷贝出来另外存放再插入链表当中
    // strdup()在内部调用了malloc()为变量分配内存，不需要使用返回的字符串时，需要用free()释放相应的内存空间，否则会造成内存泄漏。
    p->next = head; // 作为新的头节点
    return p;
}


HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = (n << 1); // 扩大一倍
    h->data = (Node **)calloc(h->size, sizeof(Node *));
    return h;
}

// 字符串的hash函数
int BKDRHash(char *str) {
    int seed = 31, hash = 0; // 设定给一个hash种子seek，要是素数
    // 这里设置hash = 0那seed不是没用了吗啊？
    for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
    return hash & 0x7fffffff; // hash可能威负数，&上这个值变为正数
}


int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;  // 得到的hash范围很广需要缩小在设定大小内
    h->data[ind] = init_node(str, h->data[ind]);  // 插入在对应位置的链表中
    return 1;
}

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind]; // 得到对应位置链表的首地址
    // strcmp一直对比，只有相等的时候才为0，否则就是>0 或 <0
    while (p && strcmp(p->str, str)) p = p->next;
    return p != NULL; 
    // 如果是遍历整个链表也没找到，p == NULL;
    // 否则就是中途找到strcmp返回值为0跳出循环
}

void clear_node(Node *node) {
    if (node == NULL) return ;
    Node *p = node, *q;
    while (p) {
        q = q->next;
        free(p->str); // 这个是strdup拷贝存在字符串的复制需要free掉，不然会内存泄漏
        free(p);
        p = q;
    }
    return ;
}

void clear(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) {
        clear_node(h->data[i]); // 每个i里都存着一个链表要逐一清空
    }
    free(h->data);
    free(h);
    return ;
}



int main() {

    int op; // 操作参数
    #define MAX_N 100
    char str[MAX_N + 5] = {0};
    HashTable *h = init_hashtable(MAX_N);
    while (~scanf("%d%s", &op, str)) {
        switch (op) {
            case 0:
                printf("insert %s to HashTable\n", str);
                insert(h, str);
                break;
            case 1:
            printf("search %s from the HashTable result = %d\n", str, search(h, str));
            break;
            }
        }
    #undef MAX_N
    clear(h);

    return 0;
}
