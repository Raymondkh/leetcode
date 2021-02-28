/*************************************************************************
	> File Name: 15.quick_find.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Feb 2021 02:57:29 PM CST
 ************************************************************************/
// hzoj71朋友圈题目结合来测试quick-find
#include <stdio.h>
#include <stdlib.h>

typedef struct UnionSet {
    int *color; // 用来存储对应目标代表的颜色
    int n;     // 元素的个数
} UnionSet;

// 并查集初始化
UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->color = (int *)malloc(sizeof(int) * (n + 1));  // 不想用0位
    u->n = n;
    // 赋予初值
    for (int i = 1; i <= n; i++) {
        u->color[i] = i;
    }
    return u;
}

// 查找这个节点的颜色
int find(UnionSet *u, int x) {
    return u->color[x];
}

// 合并
int merge(UnionSet *u, int a, int b) {
    if(find(u, a) == find(u, b)) return 0;
    int color_a = u->color[a];
    for (int i = 1; i <= u->n; i++) {
        // if (u->color[i] != color_a) continue;
        if (u->color[i] - color_a) continue;
        u->color[i] = u->color[b];
    }
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->color);
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
