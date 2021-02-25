// 实现欧几里德算法
#include<stdio.h>

// 递归实现，gcd就是将大问题转化为小问题解决
int gcd(int a, int b) {
    // if (a % b == 0) return b; 
    // 这个也是实现，每次都要%多一步计算，不如下面
    // if (b == 0) return a;
    //if (!b) reutrn a;
    //return gcd(b, a % b); 
    // 再次优化 --> 三目运算符
    return (b ? gcd(b, a % b) : a);
}

int main() {

    int a, b;
    while (~scanf("%d%d", &a, &b)) {
        printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    }

    return 0;
}


//////////////////////////////////////////////////////////////////////////
// 拓展欧几里德算法
#include<stdio.h>

int ex_gcd(int a, int b, int *x, int *y) {
    if (!b) {
        *x = 1, *y = 0;
        return a;
    }
    //int xx, yy, ret = ex_gcd(b, a % b, &xx, &yy);
    //*x = yy;
    //*y = xx - a / b * yy;
    //printf("ret = %d\n", ret);
    // 可以简化不用xx, yy 变量
    int ret = ex_gcd(b, a % b, y, x);    
    *y -= a / b * (*x);    // 这里还不是很理解，没绕过来！！！
    return ret;
}

int main() {
    
    int a, b, x, y;
    while (~scanf("%d%d", &a, &b)) {
        printf("ex_gcd(%d, %d) = %d\n", a, b, ex_gcd(a, b, &x, &y));
        printf("%d * %d + %d * %d = %d\n", a, x, b, y, a * x + b * y);
    }

    return 0;
}
