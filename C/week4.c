/*************************************************************************
	> File Name: 13.prime.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 05:43:00 PM CST
 ************************************************************************/
// 素数筛
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
        //for (int j = i * 2; j <= max_n; j+=i) {
        //    prime[j] = 1;
        //}
        //for (int j = i * i; j <= max_n; j += i) {
        //    prime[j] = 1;
            // 但是max_n = 100000时，j需要表示i*i的值会超过int能表示的值
            // 此时j会变成负数，所以访问数组会出现段错误
            // 所以i * i这部分问题还需要自己解决？？
        //}
        // 解决上面i*i爆栈的问题-->一种改法，不唯一，重点在于理解
        for (int j = i; j <= max_n / i; j++) {
            prime[j * i] = 1;
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

/*************************************************************************
	> File Name: 14.prime.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 06:40:27 PM CST
 ************************************************************************/
// 线性筛！
#include <stdio.h>
#define max_n 10000

int prime[max_n + 5]; // 全局数组的时候不需要清空，系统自动清

void init() {
    // N = M * P
    // 第一步枚举M
    for (int i = 2; i <= max_n; i++) {
        // 素数往前存
        if (!prime[i]) prime[++prime[0]] = i;
        // 枚举P
        for (int j = 1; j <= prime[0]; j++) {
            // 超出所需范围break
            if (prime[j] * i > max_n) break;
            // 枚举素因子
            prime[prime[j] * i] = 1; 
            // i即为M，能被整除时，之后的都不是最小因子了
            if (i % prime[j] == 0) break;
            // 因为这样不是每次都是最大因子吧？
            // 不是的，这里枚举P是对于之后的那些合数是最小的素因子
            // 可以自己推一遍前30，不会有重复的。
        }
    }
    return ;

}

int main() {

    init();
    for (int i =1; i <= prime[0]; i++) {
        printf("%d\n", prime[i]);
    }

    return 0;
}

