// 数据结构与算法C语言实现版本代码

/*************************************************************************
	> File Name: 1,vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 30 Jan 2021 10:20:53 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h> // 用于动态创建内存空间
#include <time.h> // 用于调用time(0)作为种子来生成随机数

typedef struct Vector {
    int *data;
    int size, length;
} Vec;

/* 知识点
结构体：
struch person {
  string name;
  int age;
  char gender;
  float height; 
};
struct person tom; // 定义结构体变量


类型别名：
例 typedef int Size; // 将Size来代替int的类型名，约定俗成类型别名的首字母一般大写
typedef struct box {
  Size width;
  Size height;
  Size length;
} Box; // 由此可见这个才是类型别名
*/



// 顺序表初始化函数
Vec *init(int n) {
    Vec *v = (Vec *)malloc(sizeof(Vec)); //为顺序表结构分配内存
    v->data = (int *)malloc(sizeof(int) * n); // 为数据分配内存
    v->size = n;   // 顺序表数据总数量或总长度
    v->length = 0; // 当前数据数量
    return v;
}

int insert(Vec *v, int val, int ind) {
    if (v == NULL) return 0;
    if (ind < 0 || ind > v->length) return 0; // 插入的序号不规范
    if (v->length == v->size) return 0; // 顺序表已满
    for (int i = v->length; i > ind; i--) {
        v->data[i] = v->data[i - 1]; // 从后面开始移动，空出需要插入的序号
    }
    v->data[ind] = val;
    v->length += 1;
    return 1;
}

int erase(Vec *v, int ind) {
    if (v == NULL) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}
 

void clear(Vec *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v); // 为什么要先free掉data的内存再顺序表
    // 因为直接free掉v则data部分的内存不会被free而发生内存泄露
    return ;
}

void output(Vec *v) {
    if (v == NULL) return ;
    printf("Vector : [");
    for (int i = 0; i < v->length; i++) {
        i && printf(", "); // 除了第一次外都输出逗号
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return ;

}


int main() {
    srand(time(0));
    #define max_op 20
    Vec *v = init(max_op);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100; // 100以内的值
        int ind = rand() % (v->length + 3) - 1; // 范围[-1, v->lenght + 1]
        // 若 rand() % v->lenght ==> 范围:[0, v->lenght-1], 修改之后则会有
        // 负值，和大于v>lenght的值这类不正确的值来测试程序的鲁棒性
        int op = rand() % 2; // 0, 1表示插入or删除
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to Vector = %d\n", val, ind, insert(v, val, ind));
            } break;
            case 3: {
                printf("erase a iterm at %d from Vector = %d\n", ind, erase(v, ind));
            } break;
        }
        output(v);
        printf("\n");
    }

    return 0;
}
