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
