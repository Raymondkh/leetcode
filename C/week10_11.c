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
