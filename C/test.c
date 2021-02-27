/*************************************************************************
	> File Name: kaoshi1.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Feb 2021 08:26:36 PM CST
 ************************************************************************/
// 自己写的数字转换，能实现功能
#include <stdio.h>
#include <math.h>
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

void ten_to_two(int num, char *arr) {

    for (int i = 0; num; i++) {
        arr[i] = num % 2;
        num /= 2;
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return ;
}

void change(char *arr, int n) {
    int h = n / 2;
    n /= 2;
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[i], arr[i + h]);
    }
    return ;
}

long long  two_to_ten(char *arr, int n) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (!arr[i]) continue;
        ans += pow(2, i);
    }
    return ans;
}

void output(char *arr, int n) {
    printf("arr: ");
    for (int i = n -1; i >=  0; i--) 
        printf("%d", arr[i]);
    printf("\n");
    return ;
}

int main() {
    int num;
    long long ans = 0;
    char arr[32] = {0};
    scanf("%d", &num);
    ten_to_two(num, arr);
    output(arr, sizeof(arr));
    change(arr, sizeof(arr));
    output(arr, sizeof(arr));
    ans = two_to_ten(arr, sizeof(arr));
    printf("%lld\n", ans);
}
