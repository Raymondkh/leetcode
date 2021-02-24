
//实现n的阶层，递归实现
#include <stdio.h>

int fac(int n) {
    if (n == 1) return 1;
    return n * fac(n - 1);
}

int main() {
    int n;
    while (~scanf("%d", &n)) {                 // 循环读入要记住(!scanf(""))
        printf("%d! = %d\n", n, fac(n));
    }
    return 0;
}

// 欧拉45题
#include <stdio.h>

typedef long long int1;  // 考虑数据溢出，所以要变成longlong的类型

int1 Triangle(int1 n) {
    return n * (n + 1) / 2;
}

int1 Pentagonal(int1 n) {
    return n * (3 * n - 1) / 2;
}

int1 Hexagonal(int1 n) {
    return n * (2 * n - 1);
}

// 还需要考虑数据存在溢出
//int binary_search(int *num, int n, int x) {
int1 binary_search(int1 (*num)(int1), int1 n, int1 x) {
    int1 head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1; // 除以1为右移一位，乘以1为左移一位 
        // if (num[mid]) < 0) printf("ERR\n"); // 超出int范围会变成负数，就会一直输出err，这是debug
        //if (num[mid] == x) return mid;
        if (num(mid) == x) return mid; // 函数指针, [] -> ()
        //if (num[mid] < x) head = mid + 1;
        if (num(mid) < x) head = mid + 1;
        else tail = mid - 1; 
    }
    return -1;
}


int main() {

    int1 n = 285;  // 从285向后开始找第二个值
    while (1) {
        n++; 
        int1 val = Triangle(n);
        
        //if (binary_search(Pentagonal, val, val) != -1) {
        //    if (binary_search(Hexagonal, val, val) != -1) {
        //        printf("%d\n", val);
        //        break;
        //    }
        //}
        // 上面这个缩进太多,简化逻辑
        if (binary_search(Pentagonal, val, val) == -1) continue;
        if (binary_search(Hexagonal, val, val) == -1) continue;
        printf("%lld\n", val);
        break;
        
        // 还可以继续优化：六边形的跨度更大！！可以以这个为第一个
        // 减少判断，更快找到所需要的的值
    }
    return 0;
}
