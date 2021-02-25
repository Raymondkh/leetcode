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
