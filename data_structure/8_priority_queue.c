/*************************************************************************
	> File Name: 13.priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 17 Feb 2021 01:29:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}


// 优先队列 
typedef struct priority_queue {
    int *data;   // 数组实现
    int cnt, size;  //  cnt当前元素个数   size数组的容量
} priority_queue;

// 初始化优先队列
priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    // 开n + 1是因为从1开始，这样可以根据编号去索引
    // 左孩子 i * 2; 右孩子 i * 2 + 1;
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

// 判空
int empty(priority_queue *q) {
    return q->cnt == 0;
}

// 返回堆顶元素值
int top(priority_queue *q) {
    return q->data[1];
}

// 插入
int push(priority_queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0; // 已满， 可以考虑自己扩容
    q->data[++(q->cnt)] = val;
    // 然后开始维护堆的性质--- 大顶堆 
    int ind = q->cnt; // 刚插入的位置
    while (ind >> 1 &&  q->data[ind] > q->data[ind >> 1]) {
        // q->data[ind >> 1] 右移除以2， (2*i+1) / 2 = i+0.5 自动向下取整
        // 也还是能取到双亲节点
        // 只要足够大就能一直向上交换移动
        swap(q->data[ind], q->data[ind >> 1]); 
        ind >>= 1;
    }
    return 1;
}

int pop(priority_queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0; // 堆空返0
    // 用最后的元素去覆盖原来的堆顶,同时q->cnt减少一个
    q->data[1] = q->data[q->cnt--]; 
    // 开始维护堆的性质，自上向下调整
    int ind = 1;
    // 还有元素时
    while ((ind << 1) <= q->cnt) {
        // r = ind << 1 | 1因为ind << 1一定是偶数，最后一位为0，|1则1
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (q->data[l] > q->data[temp]) temp = l;
        // 此时要注意，while (ind << 1) 这里已经判断有左孩子了
        // 但不确定有无右孩子，需判断
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
        // 此时temp就是根，左，右中值最大的序号了
        if (temp == ind) break; // 如果还是跟节点最大则无需调整了
        swap(q->data[ind], q->data[temp]);
        ind = temp;
    }
    return 1;
}



// 回收内存
void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}


int main() {
    srand(time(0));
    #define MAX_OP 20 // 操作次数
    priority_queue *q = init(MAX_OP);
    // 插入随机值元素
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        push(q, val);
        printf("insert %d to the priority_queue!\n", val);
    }
    // 弹出值
    for (int i = 0; i < MAX_OP; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    printf("\n");
    #undef MAX_N
    clear(q);
    return 0;
}

/*
output:
insert 48 to the priority_queue!
insert 9 to the priority_queue!
insert 64 to the priority_queue!
insert 71 to the priority_queue!
insert 93 to the priority_queue!
insert 58 to the priority_queue!
insert 11 to the priority_queue!
insert 84 to the priority_queue!
insert 0 to the priority_queue!
insert 99 to the priority_queue!
insert 14 to the priority_queue!
insert 65 to the priority_queue!
insert 48 to the priority_queue!
insert 64 to the priority_queue!
insert 39 to the priority_queue!
insert 58 to the priority_queue!
insert 48 to the priority_queue!
insert 7 to the priority_queue!
insert 79 to the priority_queue!
insert 80 to the priority_queue!
99 93 84 80 79 71 65 64 64 58 58 48 48 48 39 14 11 9 7 0 
*/
