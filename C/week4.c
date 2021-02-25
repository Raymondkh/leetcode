/*************************************************************************
	> File Name: 13.prime.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 05:43:00 PM CST
 ************************************************************************/
// 素数筛！！
#include <stdio.h>
#define max_n 100  // 便于灵活调整

int prime[max_n + 5] = {0};  // 一开始初始化为0，默认每个数都是素数 
// 多开五个是变成技巧，能避免一些重大的错误

// 初级版本
void init_0() {
    for (int i = 2; i <= max_n; i++) {
        if (prime[i] == 0) {
            for (int j = 2 * i; j < max_n; j+=i) { 
                prime[j] = 1;
            }
        }

    }
}

// 优化版本--->减少缩减
// 再次优化-->将素数连续存储
void init() {
    for (int i = 2; i <= max_n; i++) {
        if (prime[i]) continue;
        prime[++prime[0]] = i;
        // prime[0]用来记录素数的个数， 将素数按着个数顺序存放
        // 在是素数的时候就移动到前面去
        for (int j = i * 2; j <= max_n; j+=i) {
            prime[j] = 1;
        }
    }
    return ;
}


int main() {
    init();
    for (int i = 1; i <= prime[0]; i++) {
        printf("%d\n", prime[i]);
    }


    return 0;
}
