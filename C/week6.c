/*************************************************************************
	> File Name: 18.array.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Feb 2021 08:34:52 AM CST
 ************************************************************************/

#include <stdio.h>
#define max_n 100 
// 定义数组里的大小这样设置比较好，全局修改方便
// 同时可以多定义五个大小 max_n + 5可避免访问max_n这一位的bug

// int arr1[max_n + 5]; // 在全局定义时，数组会自动被清空

void func(int *num) {
    // int *num指针变量来存储传入的数组指针
    // 在64位系统中，指针变量占用8个字节，所以上面num的大小是8字节
    // 而不是数组的字节大小，即使传入的是数组地址
    printf("sizeof(num) = %lu\n", sizeof(num));
    printf("num = %p, num + 1 = %p\n", num, num + 1);
    //num和数组的使用的表现形式一样，所以就可以传入数组这样使用

    // 如果传入的是一个变量int n;
    *num = 12; // *取值符号
    num[0]  =123; // 将n看成一维一个元素的数组
    
    return ;
}

void func1(int (*num)[4]) {
    // 这样num 与num + 1之间就相差16个字节了
    printf("num = %p, num + 1 = %p\n", num, num + 1);
    return ;
}



int main() {
    // 在主函数，函数内定义的变量都是在栈区的，有空间大小限制
    // 且该变量并未清空，存放的内容可能为上一次使用该区域的内容
    // 需要自己手动清空 arr[] = {0}; 这个不止是将a[0]=0,而是
    // 将全部元素都赋值为0来清空
    int arr[max_n + 5] = {0};
    // arr的大小 (max_n + 5) * sizeof(int) = 105 * 4 = 420字节
    printf("sizeof(arr) = %lu\n", sizeof(arr));
    // %lu 无符号的长整形
    printf("arr = %p, &arr[0] = %p\n", arr, &arr[0]); // 两者是一样的

    // 动态数组：malloc, calloc, realloc
    // 即使在函数中分配的都是在堆区分配的，空间上限是内存

    int *a;
    a = arr;
    printf("arr = %p, a = %p\n", arr, a);
    printf("arr[20] = %d, a[20] = %d\n", arr[20], a[20]);
    func(arr);  // 函数调用处， 传入数组的首地址

    int arr1[2][4] = {0};
    // func(arr1); // 这样会报错，因为arr1是二维数组和num的表现形式不一样
    // arr1 与  arr1 + 1  之间相差了 4 * 4 =16个字节
    func1(arr1); // int (*num)[4];这样才不会报错
    // 只能省略最高维
    // arr[2][4][5] --> int (*num)[4][5] 


    // int **num; 去接受二维数组的情况
    // p[4] = {int *a, int *b, int *c, int *d};
    // a[4] = {int ,int ,int ,int};
    // 这样就相当于一个[4][4]的二维数组了
    // 那这样如何索引呢？



    /*
    int n;
    scanf("%d", &n); // 传入变量的地址是为了修改n变量的值，即传出参数
    for (int i = 0; i < n; i++) {
        //scanf("%d", &arr[i]);
         scanf("%d", arr + i); // 等价于上式 
        // arr == arr[0]的首地址
        // 注意这里的i不是字节，而是在物理地址中跳跃了i * sizeof(int)的字节
        // i是跳跃数组的类型的字节数，跳跃了i个元素的空间大小
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    */
    return 0;
}
//#include <inttypes.h>
//中可以使用int32_t.int64_t, 只要能支持这样定义
//那变量一定就是32位整形，64位整形
//因为int在不同机器不一定是固定的位数，比如电脑和单片机
//所以如果需要程序有较强的可移植性，那就是int32_t这样的类型?
