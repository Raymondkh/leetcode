/*************************************************************************
	> File Name: 21.define.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Feb 2021 06:08:29 PM CST
 ************************************************************************/

#include <stdio.h>
#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
// #b是将数字转化为字符串
#define GREEN(a) COLOR(a, 32)

// 加上下面这句话可以是add函数先于main函数执行
// 作用在于在add函数添加属性
__attribute__((constructor))  // 这个只会作用于其下面的第一个函数
int add(int a, int b) {
    printf("add : %d\n", __LINE__);
    return a + b;
}

int test() {
    printf("test : %d\n\n", __LINE__);
    return 0;
}



int main() {
    // 工具类知识,为字符串去添加颜色绿色32， 蓝色34
    // 如果特别喜欢添加颜色就写一个颜色宏定义
    printf("\033[34m main : %d\n \033[0m", __LINE__);
    add(2, 3);
    printf(GREEN("main : %d\n"), __LINE__);

    
    return 0;
}


/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 04:37:55 PM CST
 ************************************************************************/
// 测试memset的一些结果
#include <stdio.h>
#include <string.h>

int main() {

    int arr[2];
    memset(arr, 1, sizeof(arr));
    for (int i = 0; i < 2; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    memset(arr, -1, sizeof(arr));
    for (int i = 0; i < 2; i++) {
        printf("arr[%d] = %d\n", i, arr[i]); 
    }
    return 0;
}
/*
输出结果：
arr[0] = 16843009
arr[1] = 16843009
arr[0] = -1
arr[1] = -1
*/


/*************************************************************************
	> File Name: 22.string.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Feb 2021 09:20:59 PM CST
 ************************************************************************/
// 随堂练习4
#include <stdio.h>
#include <string.h>

int main() {

    char str[11] = {0};
    char str1[11] = {0};
    int n;
    while (~scanf("%d", &n)) {
        sprintf(str, "%X", n);  // 将n以中间的格式输入到str中 %X是16进制
        // %X 与 %x 的区别在于X时ABC， x是abc
        printf("十六进制： %s has %lu digits!\n", str, strlen(str));
        // strlen() 返回是无符号长整型
        sprintf(str1, "%d", n);
        printf("十进制： %s has %lu digits!\n", str1, strlen(str1));
    }
    return 0;
}

