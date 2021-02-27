/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 04:37:55 PM CST
 ************************************************************************/

#include <stdio.h>
#pragma pack(1)


#define P(a) printf("%s = %d\n", #a, a)

// 结构体一般是大写开头
struct data {
    int x, y;
};


int main() {
    struct data a[2], *p = a;
    a[0].x = 49, a[0].y = 50;
    a[1].x = 99, a[1].y = 100; 

    P(a[1].x);
    P((a + 1)->x);
    P((*(a + 1)).x);  // * 和 . 的优先级可能出现错误，所以必须要加括号明确优先级
    P(p[1].x);
    P((p + 1)->x);
    P((*(p + 1)).x);
    P((&a[0] + 1)->x);
    P(*(&a[0 + 1].x));

    /*
    printf("a[1].x -> %d\n", a[1].x);
    printf("a[1].x -> %d\n", (*(a + 1)).x);
    printf("a[1].x -> %d\n", (a + 1)->x);
    printf("a[1].x -> %d\n", (*(p + 1)).x);
    printf("a[1].x -> %d\n", (p + 1)->x);
    printf("a[1].x -> %d\n", );
    printf("a[1].x -> %d\n", );
    */
}

/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 04:37:55 PM CST
 ************************************************************************/
// 测试一下函数指针，函数指针类型怎么用
#include <stdio.h>
typedef int (*add)(int, int);

/*
int (*add1)(int a, int b) {
    printf("a + b = %d\n", a + b);
    return 1;
}
// 这里是我理解错误了，因为这样就是函数指针
// 这样其实是一个函数指针变量，是变量，去承载别的函数
// 本身只是一个指针，而不是函数
// 所以是想相面那样去定义一个正常的函数，传地址去实现功能
*/
int add1(int a1, int b1) {
    printf("a + b =  %d\n", (a1 + b1));
    return 1;
}

int add2(int a, int b) {
    printf("a + b + 1 = %d\n", a + b + 1);
    return  1; 
}

int f(int (*func)(int, int),int a, int  b) {
    func(a, b);
    return 1;
}

int main() {
    int a = 1, b = 2;
    add func1, func2; // 函数指针就能定义多个类型这样函数的变量来存放函数地址
    func1 = &add1;
    func2 = add2; // &取地址可有，也可以没有
    f(func1, a, b);
    f(func2, a, b);
    
    return 0;
}
