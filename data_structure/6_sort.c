/*************************************************************************
	> File Name: 9.stable_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 15 Feb 2021 08:54:32 PM CST
	// 动图链接：https://www.cnblogs.com/onepixel/p/7674659.html
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}
// args...变参列表，然后就在{}内只用名字args来使用
//  \ 用于连接成为一行宏
// 注意memcpy(目标， 源， 字节操作)
// 所以是memvpy(num, arr, sizeof(int) * n );
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
// num数组num[0]...num[n-1]
void insert_sort(int *num, int n) {
    // i从1一直到n-1
    for (int i = 1; i < n; i++) {
	// j表示从i一直向前交换移动，直到num[1]
	// 因为是可以作用到num[j - 1]的，所以是可以覆盖到num[0]的
        for (int j = i; j > 0 && (num[j] < num[j - 1]); j--) {
            swap(num[j], num[j - 1]);
        }
    }
    return ;
}

// 冒泡排序
void bubble_sort(int *num, int n) {
    int times = 1; // 优化的小技巧，如在一轮中再也没有发生交换即为已顺序
    for (int i = 1; i < n && times; i++) {  // 对比次数,共n-2轮？
        times = 0;
        for (int j = 0; j < n - i; j++) { // 交换次数，递减if
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
	// r - l <= 1 表示 rl是同一个序号或者rl相邻为最小的情况了
	// 如果是相邻的情况直接按大小交换
    }
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    // 此时拆分的部分已经排好序了,接下来就是合并
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));// 开辟空间来合并排序数列
    int p1 = l, p2 = mid + 1, k = 0;
    // (p1 <= mid || p2 <= r) 说明还存在需要合并的元素
    while (p1 <= mid || p2 <= r) {
        if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
            // 分析能进入这里的条件
            // p2 > r 说明p2已经没有元素了
            // 后一个条件是左半段比较小的就插入数列中
            temp[k++] = num[p1++];
        } else {
            // 情况1：p2 < r && p1 > mid
            // 情况2：num[p1] > num[p2]
            temp[k++] = num[p2++];
        }
    }
    // num + l整段的起点
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
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
    randint(arr, MAX_N);  // 给数组元素赋随机值
    // 为啥要用宏定义呢？函数不香吗？
    // 这里的num是宏定义里面的num，直接替换的
    TEST(arr, MAX_N, insert_sort, num, MAX_N);
    TEST(arr, MAX_N, bubble_sort, num, MAX_N);
    TEST(arr, MAX_N, merge_sort, num, 0, MAX_N - 1);
    #undef MAX_N
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************
	> File Name: 10.unstable_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Feb 2021 09:03:21 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define swap(a, b) {\
    __typeof(a) __temp = a; \
    a = b; b = __temp; \
}

#define TEST(arr, n, func, args...) {\
    int *num = (int *)malloc(sizeof(int) * n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n); \
    printf("%s = ", #func);\
    func(args);\
    output(num, n);\
    free(num);\
}


// 选择排序
void select_sort(int *num, int n) {
    for (int i = 0; i < n - 1; i++) { // 一共进行n-1轮对比，因为最后剩一个即完成了
        int ind = i; // 最小值的坐标存储
        for (int j = i + 1; j < n; j++) {  // 遍历比较待排序区
            if (num[j] < num[ind]) ind = j; // 若有更小的值则交换坐标
        }
        swap(num[i], num[ind]);
    }
    return ;
}

// 快速排序, 递归实现，有监督，监督体现在移动y, x需要while(x < y)
void quick_sort(int *num, int l, int r) {
    if (l > r) return ;
    int x = l, y = r, z = num[x]; // 基准值一般是第一个值
    while (x < y) {
        while (x < y && num[y] > z) y--;
        if (x < y) num[x++] = num[y];
        while (x < y && num[x] < z) x++;
        if (x < y) num[y--] = num[x];
    }
    num[x] = z; // 最后x = y是即完成一次
    quick_sort(num, l, x - 1);
    quick_sort(num, x + 1, r);
    return ;
}

// 优化版快速排序, 无监督的算法，无监督比有监督的要快
void quick_sort_s(int *num, int l, int r) {
    
    while (l < r) {
        int x = l, y = r, z = num[(l + r) >>1];
        do {
            while (num[x] < z) x++;
            while (num[y] > z) y--;
            if (x <= y) {
                swap(num[x], num[y]);
                x++, y--;
            }
        } while (x <= y);
	// 此时 x > y 即 l ... y x .... r
        quick_sort_s(num, l, y); // 左侧是递归
        l = x; // 右侧是循环
    }
    return ;
}

void randint(int *arr, int n) {
    while (n--) arr[n] = rand() % 100;
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
    TEST(arr, MAX_N, select_sort, num, MAX_N);
    TEST(arr, MAX_N, quick_sort, num, 0, MAX_N - 1);
    TEST(arr, MAX_N, quick_sort_s, num, 0, MAX_N - 1);
    #undef MAX_N
    return 0;
}




