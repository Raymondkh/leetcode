/*************************************************************************
	> File Name: 17.weighted_quick_union.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Feb 2021 02:57:29 PM CST
 ************************************************************************/
// hzoj71朋友圈题目结合来测试
#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct UnionSet {
    int *father;
    int *size; // 去存储节点下面挂载的节点个数
    int n;     // 元素的个数
} UnionSet;

// 并查集初始化
UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * (n + 1));  // 不想用0位
    u->size = (int *)malloc(sizeof(int) * (n + 1));  // 不想用0位
    u->n = n;
    // 赋予初值
    for (int i = 1; i <= n; i++) {
        u->father[i] = i;
        u->size[i] = 1;
    }
    return u;
}

int find(UnionSet *u, int x) {
    if (u->father[x] == x) return x;
    return find(u, u->father[x]);

    // 自想循环实现,就是一直找到与自己相等的元素
    // 测试了一下循环会快一点点
    /* 
    while (u->father[x] != x) {
        x = u->father[x];
    }
    return x;
    */
}

// 合并
int merge(UnionSet *u, int a, int b) {
    int fa =find(u, a), fb = find(u, b);
    if (fa == fb) return 0;
    // fa始终为节点数比较多的一个代表元素
    if (u->size[fa] < u->size[fb]) swap(fa, fb); 
    // 不然就修改一则的代表元素，注意是代表元素
    u->father[fb] = fa; // 将节点数少的fb变成fa的子树
    u->size[fa] += u->size[fb]; // 将fa的节点数增加fb的数量
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->father);
    free(u->size);
    free(u);
    return ;
}

int main() {
    int n, m; // n个朋友，m次操作
    scanf("%d%d", &n, &m);
    UnionSet *u = init(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        switch (a) {
            case 1: merge(u, b, c); break;
            case 2: printf("%s\n", find(u, b) == find(u, c) ? "Yes" : "No");
                    break;
        }
    }
    clear(u);
    return 0;
}
