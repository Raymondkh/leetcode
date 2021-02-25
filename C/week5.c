/*************************************************************************
	> File Name: 15.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 08:41:21 PM CST
 ************************************************************************/
 // 二分查找，数组版，函数版
#include <stdio.h>

// 数组情况（可以看成由空间换时间）
int binary_search(int *arr, int n, int x) {
    int head = 0, tail = n - 1, mid;

    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

// 函数情况,函数就是压缩了的数组（由时间换空间）
int binary_search_func(int (*func)(int), int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (func(mid) == x) return mid;
        if (func(mid) < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;

}


/*************************************************************************
	> File Name: 16.my_sqrt.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 10:07:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <math.h>

double func(double x) {
    return x * x;
}

double binary_search(double (*arr)(double), double n) {
    // 带查找的区间:[0, n]
    //
    double head = 0, tail = n, mid;
    // 特判
    if (n < 1) tail = 1.0;
    // 只要误差足够小，就为答案了
    #define EPLS 1e-7
    while (tail - head > EPLS) {
        mid = (head + tail) / 2.0;
        if (arr(mid) < n) head = mid;
        else tail = mid;
    }
    #undef EPLS
    return head; // 返回head和tail都可以，两者已经足够接近了 

}


int main() {

    double n;
    while (~scanf("%lf", &n)) {
        // %g 以科学计数法来表示当前的数
        printf("my_sqrt(%g) = %g\n", n, binary_search(func, n));
        printf("sqrt(%g) = %g\n", n, sqrt(n));
    }

    // 第一个问题 根号0.1 = 0.3 的但是程序出错了，问题在于不在[0, n]之内
    // 二分查找的条件，范围内一定要包含查找的答案
    
    return 0;
}


int func(int x) {
    return x * x;
}

int main() {

    int arr[100] = {0};
    // 序号： 0 1 2 3 4  5  6....
    // 值：   0 1 4 9 16 25 36...
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    while (~scanf("%d", &x)) {
        printf("%d\n", binary_search(arr, n, x));
    }

    // 函数开始
    int n1, x1;
    scanf("%d", &n1);
    while (~scanf("%d", &x1)) {
        printf("函数查找-->%d\n", binary_search_func(func, n1, x1));
    }

    return 0;
}
