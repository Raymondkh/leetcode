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


/*************************************************************************
	> File Name: 25.pointer.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Feb 2021 04:19:32 PM CST
 ************************************************************************/

#include <stdio.h>
// 测试#define和typedef的区别
#define ppchar char *
typedef char * pchar; //注意这个是语句需要分号;!!!!

/*
#define offset(T, a) ({\
    T temp;\
    (char *)(&temp.a) - (char *)(&temp);\
})
// 用括号是因为可以将宏定义的最后一个表达式的值输出
*/

// 一种更优秀的方法
#define offset(T, a)  ((long)(&(((T *)(NULL))->a)))

// NULL <==> 0 <==> '\0' 三者等价


struct Data {
    int a;
    double b;
    char c;
};

int main() {

    int num = 0x0626364;
    printf("%s\n", (char *)(&num)); //  (char *)转化为字符串的形式
    // 查看三个成员的地址偏移量  
    printf("%ld\n", offset(struct Data, a)); 
    // 这里用之所以没有预先定义是因为宏替换直接带入就能知道是结构体的成员
    printf("%ld\n", offset(struct Data, b));
    printf("%ld\n", offset(struct Data, c));
    
    pchar p1, p2;
    ppchar p3, p4;
    printf("p1 = %lu, p2 = %lu\n", sizeof(p1), sizeof(p2));
    printf("p3 = %lu, p4 = %lu\n", sizeof(p3), sizeof(p4));
    // p1 = 8, p2 = 8
    // p3 = 8, p4 = 1

    return 0;
}
