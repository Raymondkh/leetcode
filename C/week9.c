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
