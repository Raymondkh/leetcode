/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 14 Feb 2021 09:03:50 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)


typedef struct Stack {
    int *data; // 指向整形元素的data
    int top, size; // 栈顶指针， 栈的容量size
} Stack;

// 初始化栈
Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

// 打印栈顶元素的值
int top(Stack *s) {
	// 这里其实不够严谨，万一是空栈呢？
	// 需要在外面判断好了再用这个函数
    return s->data[s->top];
}

// 如何去判断空
int empty(Stack *s) {
    return s->top == -1;
}

int expand(Stack *s) {
    int extr_size = s->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(s->data, sizeof(int) * (extr_size + s->size));
        if (p) break; // 扩容成功
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
	// 注意realloc会自动释放内存
	// 如果能原地扩容成功，那s->data == p? 经测试，是对的
    s->data = p;
    s->size += extr_size;
    return 1;
}


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

// 出栈
int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0; // 栈是空的也无法pop
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    if (s == NULL) return ;
    printf("Stack: [");
    for (int i = 0; i <= s->top; i++) {
        i && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}


int main() {

    srand(time(0));
    #define max_op 20
    Stack *s = init(4);
    int flag;
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Stack = %d\n", val, push(s, val));
            } break;
            case 3: {
                flag = !empty(s);
                flag && printf("pop %d from the Stack\n", top(s));
                printf("result = %d\n", pop(s));
                // printf("pop %d from the Stack = %d\n", top(s), pop(s));
                // 为什么不能这样写一行呢？因为一行会先调用了pop(s), 与系统栈设计有关
            } break;
        }
        output(s), printf("\n");
    }
    #undef max_op
    clear(s);
    return 0;
}
