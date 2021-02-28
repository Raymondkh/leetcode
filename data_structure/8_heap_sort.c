/*************************************************************************
	> File Name: 14.heap_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 28 Feb 2021 10:52:16 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

void test(int *arr) {
    printf("arr = %p\n", arr);
    printf("&arr[0] = %p\n", &arr[0]);
    printf("$arr[1] = %p\n", &arr[1]);
    return ;
}

void downUpdate(int *arr, int n, int ind) {
    while ((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[ind], arr[temp]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    // 让堆顶元素存储的下标为1
    //test(arr);
    arr -= 1; 
    //test(arr);
    // arr -= 1; 整体向前移动一位，则arr[0]是无意义的一位，arr[1]变成开头
    // 这样的目的在于，将有开头数值变成arr[1]便于下面从1开始堆排序
    // 因为输入的数组一般都是从0开始的，所以需要这样处理
    //
    // i = n >> 1从倒数第二层一直序号递减的调整
    // 仔细看这里i >= 1为终止条件，与上面arr -= 1相匹配的
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(arr, n, i); // n是数组的元素个数，i是第i层
    }
    // 此时堆已经建好了,开始堆排序
    for (int i = n; i > 1; i--) {
        // 头部弹出元素，堆尾元素与堆顶元素交换
        swap(arr[i], arr[1]);
        // 然后针对于新的堆顶进行向下调整
        downUpdate(arr, i - 1, 1);
    }
    return ;


}

void output(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
    return ;
}


int main() {
    
    srand(time(0));
    #define MAX_N 20
    int *arr = (int *)malloc(sizeof(int) * (MAX_N + 1));
    for (int i = 0; i < MAX_N; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, MAX_N);
    heap_sort(arr, MAX_N);
    output(arr, MAX_N);
    free(arr);
    #undef MAX_N
    return 0;
}
