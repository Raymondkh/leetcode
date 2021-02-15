/*************************************************************************
	> File Name: 9.stable_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Feb 2021 08:54:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}
// args...变参列表
//  \ 用于连接成为一行宏
#define TEST(arr, n, func, args...) {\
    int *num = (int *)malloc(sizeof(int) * n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n);\
    printf("%s = ", #func);\
    func(args);\
    output(num, n);\
    free(num);\
}



// 插入排序
void insert_sort(int *num, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && (num[j] < num[j - 1]); j--) {
            swap(num[j], num[j - 1]);
        }
    }
    return ;
}

// 冒泡排序
void bubble_sort(int *num, int n) {
    int times = 1; // 优化的小技巧，如在一轮中再也没有发生交换即为已顺序
    for (int i = 1; i < n && times; i++) {  // 对比次数
        times = 0;
        for (int j = 0; j < n - i; j++) { // 交换次数
            if (num[j] <= num[j + 1]) continue;
            swap(num[j], num[j + 1]);
            times++; 
        }

    }
}


// 归并排序  分支思想一般都是递归实现
void merge_sort(int *num, int l, int r) {
    if (r - l <= 1) {
        if (r - l == 1 && num[r] < num[l]) {
            swap(num[r], num[l]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));// 开辟空间来合并排序数列
    int p1 = l, p2 = mid + 1, k = 0;
    // (p1 <= mid || p2 <= r) 说明还存在需要合并的元素
    while (p1 <= mid || p2 <= r) {
        if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
            // 分析能进入这里的条件
            // p2 > r 说明p2已经没有元素了
            // 后一个条件是比较小的就插入数列中
            temp[k++] = num[p1++];
        } else {
            // p2 < r && p1 > mid
            // num[p1] > num[p2]
            temp[k++] = num[p2++];
        }
    }
    // num + l整段的起点？
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
}


void randint(int *arr, int n) {
    while (n--) arr[n] = rand() % 100;
    // 注意这里n--， 首先是20来判断，然后赋值的时候变为了arr[19]了！！
    return ;
}

void output(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", arr[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    
    srand(time(0));
    #define MAX_N 20
    int arr[MAX_N];
    randint(arr, MAX_N);
    // 为啥要用宏定义呢？函数不香吗？
    // 这里的num是宏定义里面的num，直接替换的
    TEST(arr, MAX_N, insert_sort, num, MAX_N);
    TEST(arr, MAX_N, bubble_sort, num, MAX_N);
    TEST(arr, MAX_N, merge_sort, num, 0, MAX_N - 1);
    #undef MAX_N
    return 0;
}
