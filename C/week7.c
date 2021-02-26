/*************************************************************************
	> File Name: 19.MAX.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 04:37:55 PM CST
 ************************************************************************/
#include <stdio.h>

/*
#define MAX(a, b) { \
    if ((a) > (b)) return a; \
    return b; \
}
// 不知道为什么出错了
*/
// __typeof 是系统定义的宏 __typeof(a) 去获取a的类型

#define MAX(a, b) ({\
    __typeof(a) __a = (a);\
    __typeof(b) __b = (b);\
    __a > __b ? __a : __b;\
})
// 这里用({}) 是为了一个表达式去返回值
// 这个表达式的值就是最后一行代码的值

#define P(func) {\
    printf("%s = %d\n", #func, func);\
}
// #是名称化 


int main() {
    // 用宏的方法代替下面字符串的输出，同样效果更少代码
    P(MAX(2, 3));
    P(5 + MAX(2, 3));
    P(MAX(2, MAX(3, 4)));
    P(MAX(2, 3 > 4 ? 3 : 4));
    int a = 7;
    P(MAX(a++, 6));
    P(a);
    
    /*
    printf("MAX(2, 3) = %d\n", MAX(2, 3));
    printf("5 + MAX(2, 3) = %d\n", 5 + MAX(2, 3));
    printf("MAX(2, MAX(3, 4)) = %d\n", MAX(2, MAX(3, 4)));
    printf("MAX(2, 3 > 4 ? 3 : 4) = %d\n", MAX(2, 3 > 4 ? 3 : 4));
    int a = 7;
    printf("MAX(a++, 6) = %d\n", MAX(a++, 6));
    printf("a = %d\n", a);
    */
    return 0;
}

/*************************************************************************
	> File Name: 20.LOG.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Feb 2021 04:24:20 PM CST
 ************************************************************************/

#include <stdio.h>

// 方法一：显式的去定义DEBUG  #define DEBUG 
// 方法二：编译的时候g++ -DDEBUG 20.LOG.cpp 
// 这样会帮你嵌入一个DEBUG宏

#ifdef DEBUG
#define log(frm, args...) {\
    printf("[%s-->%s : %d]",__FILE__, __func__, __LINE__);\
    printf(frm, ##args);\
}
// # 一个井号为名称化
// ## 两个井号为连接，容许##args为空的情况
// args这只是一个名字，不固定
#else
#define log(frm, args...) 
// 如果没有定义DEBUG就替换为空，即将log语句全部替换为空
#endif




//#define contact(a, b) a##b  // 这个是正确的连接
// #define contact(a, b) ab  // 这样不是链接，而是字符的拼接，报错的

int main() {
    int a = 123;
    int abcdef = 0;
    printf("hello kaikeba\n");
    log("hello kaikeba\n");
    log("%d\n", a);
    //contact(abc, def) = 234;
    log("%d\n", abcdef);
    return 0;
}

