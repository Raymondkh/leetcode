/*************************************************************************
	> File Name: 11.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 16 Feb 2021 11:26:02 AM CST
 ************************************************************************/

#include <stdio.h>
#define P(func) {\
    printf("%s = %d\n", #func, func);\
}



int binary_search(int *arr, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid  =(head + tail) >> 1;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) head = mid + 1;
        else tail = mid - 1; 
    }
    return -1; // 表示没找到目标值
}

// 11111111000000000 找最后一个1
int binary_search_l1(int *arr, int n, int x) {
    int head = -1, tail = n - 1,  mid; // head = -1 在虚拟位表示可能存在全零情况
    while (head < tail) {
        // mid = (head + tail + 1) >> 1;
        // +1 原因是
        // printf("head = %d, tail = %d, mid = %d\n", head, tail, mid);// 输出看看为什么会死循环
        // head = 2, tail = 3, mid = 2; 就一直卡在这里了
        // (2 + 3）/ 2 = 5 / 2 = 2.5 向下取整为2
        // 所以需要+1，改为向上取整了
        mid = (head + tail + 1) >> 1;
        if (arr[mid] == x) head = mid;
        else tail = mid - 1;
    }
    // 出来时 head == tail 
    //return head == -1 ? -1 : head; // head = -1 时即为全零情况 
    return head;
}
// 问题来了：那上面这个程序能找到最后一个0吗？还是能找到第一个0？

// 000000011111111  找到第一个1
int binary_search_f1(int *arr, int n, int x) {
    int head = 0, tail = n, mid;  // tail = n 虚拟位来避免全零
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] == x) tail = mid;
        else head = mid + 1;
    }

    return tail == n ? -1 : head;
}


int main() {
    
    int arr1[10] = {1, 3, 5, 7, 9, 11, 13, 17, 19, 21};
    int arr2[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    int arr3[10] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1};

    P(binary_search(arr1, 10, 7));
    P(binary_search_l1(arr2, 10, 1));
    P(binary_search_f1(arr3, 10, 1));
    printf("\n");
    P(binary_search_l1(arr2, 10, 0)); // 9 答案是对的
    P(binary_search_f1(arr3, 10, 0)); // -1答案是错的，为什么呢？
    return 0;
}
