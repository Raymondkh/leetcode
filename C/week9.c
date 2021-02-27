/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 04:37:55 PM CST
 ************************************************************************/
// 测试宏#pragma pack(1)的作用
#include <stdio.h>
#pragma pack(1)

struct person {
    char name;
    int age;
    float height;
};


int main() {
    struct person stu;
    printf("person -> %lu\n", sizeof(stu));
}
// 未添加宏时输出：person -> 12  此时是4个字节一个单位
// 添加宏后输出：person -> 9   此时就是一个字节一个单位


/*************************************************************************
	> File Name: 23.ip.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Feb 2021 08:59:18 AM CST
 ************************************************************************/
// 将ip转化为唯一对应的整数
#include <stdio.h>

union IP {
    struct {
        unsigned char a1;
        unsigned char a2;
        unsigned char a3;
        unsigned char a4;
    } ip;
    unsigned int num;
};


int is_little() {
    static int num = 1;
    return  ((char *)(&num))[0];
}

int main() {
    // 小端机测试
    printf("%d\n", is_little());
    union IP p;
    char str[100] = {0};
    int arr[4];
    while (~scanf("%s", str)) {
        sscanf(str, "%d.%d.%d.%d", arr, arr + 1, arr + 2, arr + 3);
        p.ip.a1 = arr[0];
        p.ip.a2 = arr[1];
        p.ip.a3 = arr[2];
        p.ip.a4 = arr[3];
        printf("ip = %u\n", p.num);
    }

    return 0;
}
