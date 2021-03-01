/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 05:00:27 PM CST
 ************************************************************************/
 // 普通队列的代码，还存在假溢出的问题
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail; // 头指针为指针的下标
    int length;    // 总长度
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->head = q->tail = 0;
    return q;
}

int front(Queue *q) {
    return q->data[q->head];
}

// 判断是否为空
int empty(Queue *q) {
    return q->head == q->tail;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->tail + 1 == q->length) return 0; // 
    q->data[q->tail++] = val; // 这里使用的是tail执行最后一个元素的下一个位置，所以可直接存放
    return 1;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0; // 判断是否为空，如果为空则出队失败
    q->head++; // 出队直接就head加一位，之前需要用front去读取出队数据
    return 1;
}

void output(Queue *q) {
    if (q == NULL) return ;
    printf("queue:[");
    for (int j = 0, i = q->head; i < q->tail; i++, j++) {
        j && printf(", ");
        printf("%d", q->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Queue *q = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Queue!", val);
                printf("result = %d\n", push(q, val));
            } break;
            case 3: {
                printf("pop %d from the Queue", front(q));
                printf("result = %d\n", pop(q));
                // 这里分成两步是因为需要之后pop是否成功需要返回值吧？
            } break;
        }
        output(q), printf("\n");
    }
    #undef max_op
    clear(q);
    return 0;
}
//////////////////////////////////////////////////////////
/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 05:00:27 PM CST
 ************************************************************************/
// 解决假溢出问题-->修改为循环队列
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail; // 头指针为指针的下标
    int length, cnt; // length总长度，cnt总长度
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->head = q->tail = 0;
    q->cnt = 0;
    return q;
}

int front(Queue *q) {
    return q->data[q->head];
}

// 判断是否为空
int empty(Queue *q) {
    return q->cnt == 0;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->length) return 0; // 
    q->data[q->tail++] = val; //这里使用的是tail执行最后一个元素的下一个位置，所以可直接存放
    if (q->tail == q->length) q->tail = 0; // 赋值运算比求余运算快多了
    // 若是求余：q->tail %= q->length;
    q->cnt += 1;
    return 1;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0; // 判断是否为空，如果为空则出队失败
    q->head++; // 出队直接就head加一位，之前需要用front去读取出队数据
	q->cnt--;
    if (q->head == q->length) q->head = 0;
    return 1;
}

void output(Queue *q) {
    if (q == NULL) return ;
    printf("queue:[");
	// 注意j < q->cnt是因为如果还是q->tail，循环是q->tail已经在0，即一直小了
	// 注意已经换成了j，因为对应的是q->cnt计数
    for (int j = 0, i = q->head; j < q->cnt; i++, j++) {
        j && printf(", ");
        printf("%d", q->data[i % q->length]);
    }
    printf("]\n");
    return ;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}



int main() {
    srand(time(0));
    #define max_op 20
    Queue *q = init(10);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Queue!", val);
                printf("result = %d\n", push(q, val));
            } break;
            case 3: {
                printf("pop %d from the Queue", front(q));
                printf("result = %d\n", pop(q));
                // 这里分成两步是因为需要之后pop是否成功需要返回值吧？
            } break;
        }
        output(q), printf("\n");
    }
    #undef max_op
    clear(q);
    return 0;
}
////////////////////////////////////////////////////////////
// 解决真溢出问题-->自动扩容
/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 05:00:27 PM CST
 ************************************************************************/
// 解决假溢出问题-->修改为循环队列
// 添加扩容方法
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)


typedef struct Queue {
    int *data;
    int head, tail; // 头指针为指针的下标
    int length, cnt; // length总长度，cnt总长度
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->head = q->tail = 0;
    q->cnt = 0;
    return q;
}

int front(Queue *q) {
    return q->data[q->head];
}

// 判断是否为空
int empty(Queue *q) {
    return q->cnt == 0;
}

int expend(Queue *q) {
    int extr_size = q->length;
    int *p = NULL; // 记得初始化
    while (extr_size) {
        p = (int *)malloc(sizeof(int) * (q->length + extr_size));
        if (p) break; // 开辟成功
        extr_size >>= 1;
    }
    if (!extr_size) return 0; // 此时extr_size为0是开辟不成功的
    // 开辟成功之后需要将数据转移过来，由于循环队列所以不一定是按顺序的
    for (int j = 0, i = q->head; j < q->cnt; j++, i++) {
        p[j] = q->data[i % q->length];
    }
    free(q->data); // 要记得释放空间
    q->data = p;
    q->length += extr_size; // 记得更新q->length,q->head,q->tail
    q->head = 0;    
    q->tail = q->cnt;
    return 1;
}


int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->length) {
        // 此时队列已满需要扩容
        if (!expend(q)) return 0; // 扩容失败
        // 否则会扩容成功
        printf(GREEN("\nsuccess to expend the queue!, length = %d\n"), q->length);
    }
    q->data[q->tail++] = val; //这里使用的是tail执行最后一个元素的下一个位置，所以可直接存放
    if (q->tail == q->length) q->tail = 0; // 赋值运算比求余运算快多了
    // 若是求余：q->tail %= q->length;
    q->cnt += 1;
    return 1;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0; // 判断是否为空，如果为空则出队失败
    q->head++; // 出队直接就head加一位，之前需要用front去读取出队数据
    if (q->head == q->length) q->head = 0;
    q->cnt -= 1;
    return 1;
}

void output(Queue *q) {
    if (q == NULL) return ;
    printf("queue:[");
    for (int j = 0, i = q->head; j < q->cnt; i++, j++) {
        j && printf(", ");
        printf("%d", q->data[i % q->length]);
    }
    printf("]\n");
    return ;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}



int main() {
    srand(time(0));
    #define max_op 20
    Queue *q = init(10);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Queue!", val);
                printf("result = %d\n", push(q, val));
            } break;
            case 3: {
                printf("pop %d from the Queue", front(q));
                printf("result = %d\n", pop(q));
                // 这里分成两步是因为需要之后pop是否成功需要返回值吧？
            } break;
        }
        output(q), printf("\n");
    }
    #undef max_op
    clear(q);
    return 0;
}

