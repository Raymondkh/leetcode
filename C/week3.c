#include <stdio.h>
#include <inttypes.h>  // INT32_MIN 需要包含的头文件
#include <stdarg.h>  // va家族
// 除了va_list是变量类型之外，va_start, va_arg, va_end都是一个宏
// 必须要有第一个明确的参数才能定位到变参变量
// 即 max_int(...); 这样是不行的
//
int max_int(int n, ...) {
    int ans = INT32_MIN;
    va_list arg; // 定义变参变量
    va_start(arg, n); // arg是需要赋予变参列表变量的变量， n是定位的坐标
    while (n--) {
        // 注意这里传的是int，是变量类型int
        // 所以va_arg不是一个函数，它是一个宏！！！
        int temp = va_arg(arg, int); // 取得下一个变参列表的变量
        if (temp > ans) ans = temp;
    }
    va_end(arg);
    return ans;

}

int main() {
    printf("%d\n", max_int(3, 1, 2, 3));
    printf("%d\n", max_int(5, 11, 18, 99, 22, 65));
    printf("%d\n", max_int(5, 11, 18, 99, 22, 65, 11));
    return 0;
}
////////////////////////////////////////////////////////////////////
/*************************************************************************
	> File Name: 12.my_printf.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Feb 2021 10:15:51 AM CST
 ************************************************************************/

// putchar() 每次向屏幕输出一个字符

#include <stdio.h> // 与系统的printf()输出的效果对比
#include <stdarg.h>
#include <inttypes.h>

int reverse_num(int x, int *temp) {
    int digit = 0;
    do {
        digit++;
        *temp = *temp * 10 + x % 10;
        x /= 10;
    } while (x);
    return digit;
}

int output_num(int num, int digit) {
    int cnt = 0;
    while (digit--) {
        putchar(num % 10 + '0'), ++cnt;
        num /= 10;
    }
    return cnt;

}

// 返回值int是成功输出多少个字符
// const char* 中const表示frm变量的值是不可以修改的
// char * const 内容可以修改，但是frm的地址是不可以修改的
// 例如操作: frm++; // frm是一个地址
int my_printf(const char *frm, ...) {
    int cnt = 0;
    va_list arg;
    va_start(arg, frm);
    #define PUTC(a) putchar(a),++cnt

    // frm[i]来作为结束，是因为frm字符串最后是由'\0'结束符的，代表0值
    for (int i = 0; frm[i]; i++) { 
        switch (frm[i]) {
            case '%': {
                switch (frm[++i]) {
                    case '%': PUTC(frm[i]); break;
                    // 考虑到%%d的情况要输出一个%
                    case 'd': {
                        int x = va_arg(arg, int);
                        uint32_t xx = 0;
                        if (x < 0) PUTC('-'), xx = -x;
                        else xx = x;
                        int x1 = xx / 100000, x2 = xx % 100000;
                        int temp1 = 0, temp2 = 0;
                        // temp1是高五位翻转，temp2是低
                        int digit1 = reverse_num(x1, &temp1);
                        int digit2 = reverse_num(x2, &temp2);
                        int digit3 = 0;
                        // printf("digit1 = %d, digit2 = %d\n", digit1, digit2);
                        if (x1) digit3 = 5 - digit2;
                       // x1高位有数值，则低位一定满
                        else digit1 = 0; 
                        // 疑惑：上面函数返回值不能表示这些吗？还需要重新赋值？
                        cnt += output_num(temp1, digit1);
                        cnt += output_num(0, digit3);
                        cnt += output_num(temp2, digit2);
                       } break;
                    case 's': {
                        const char *str = va_arg(arg, const char *);
                        // 这里后面使用const char *这个类型不太理解
                        // 字符串的类型是char *?
                        for (int i = 0; str[i]; i++) {
                            PUTC(str[i]);
                        }
                    } break;
                } break;
            } 
            // putchar(frm[i]), ++cnt; // 用下面宏定义代替
            default: PUTC(frm[i]); break; // 没有%就直接输出
        }
    }
    #undef PUTC
    va_end(arg);
    return cnt;
}

int main() {
    int a = 123;
    int n;
    // 测试函数返回值是否正确
    //while (~scanf("%d", &n)) {
    //    printf("has %d digits\n", printf("%d", n));
    //    my_printf("has %d digits\n", my_printf("%d", n));
    //}
    //return 0;
    printf("hello world!\n");
    my_printf("hello world!\n");
    // \n是能识别为一个换行符吗？
    printf("int(a) = %d\n", a);
    my_printf("int(a) = %d\n", a);
    printf("int(a) = %d\n", 0);
    my_printf("int(a) = %d\n", 0); 
    printf("int(a) = %d\n", 1000);
    my_printf("int(a) = %d\n", 1000);
    printf("int(a) = %d\n", -123);
    my_printf("int(a) = %d\n", -123);
    // 在实现逻辑中数字需要先翻转过来在输出
    // 但是int表示范围是-2147483648~2147483647
    // 最大值倒过来的时候是7.....2 这样就超过int能表示的范围了
    // 解决方法：分高低五位去表示
    printf("int(a) = %d\n", INT32_MAX);
    my_printf("int(a) = %d\n", INT32_MAX);
    // 注意最小值是...8这样会超出正数的范围
    // 解决：uint32_t xx 来存储
    printf("int(a) = %d\n", INT32_MIN); 
    my_printf("int(a) = %d\n", INT32_MIN);
    char str[] = "I love china!"; 
    // char *str1[] = {str}; 、// 数组，每个元素存放指向字符的地址
    // char *str2 = str; // 存放指向字符的地址
    printf("str = %s\n", str); 
    my_printf("str = %s\n", str);
    
    printf("int(100500)) = %d\n", 100500); 
    my_printf("int(100500)) = %d\n", 100500); 
    // my_printf()--> 150000  错误了！！
    // 原因在于output_num这里输出是五位，但前面并不会输出0！
    return 0;
}
