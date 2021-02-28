/*************************************************************************
	> File Name: 16.quick_union.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Feb 2021 02:57:29 PM CST
 ************************************************************************/
// hzoj71朋友圈题目结合来测试quick-find
#include <stdio.h>
#include <stdlib.h>

typedef struct UnionSet {
    int *father; 
    int n;     // 元素的个数
} UnionSet;

// 并查集初始化
UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * (n + 1));  // 不想用0位
    u->n = n;
    // 赋予初值
    for (int i = 1; i <= n; i++) {
        u->father[i] = i;
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
    // 不然就修改一则的代表元素，注意是代表元素
    u->father[fa] = fb;
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->father);
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
