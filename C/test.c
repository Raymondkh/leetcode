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

/*************************************************************************
	> File Name: kaoshi2.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Feb 2021 09:15:52 PM CST
 ************************************************************************/

#include <stdio.h>
#define MAX_N 20000

int arr[MAX_N + 5];

void init(int *arr) {

    for (int i = 2; i <= MAX_N; i++) {
        if (!arr[i]) arr[++arr[0]] = i;
        for (int j = 1; j <= arr[0]; j++) {
            if (arr[j] * i > MAX_N) break;
            arr[arr[j] * i] = 1;
            if (i % arr[j] == 0) break;
        }
    }
    return ;
}

int binary_search(int *arr, int head, int tail, int n){
    int mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] == n) return 1;
        if (arr[mid] < n) head = mid + 1;
        else tail = mid - 1;
    }
    return 0;
}

int main() {
    
    int n;
    int i = 0, j = 0, z = 0;
    scanf("%d", &n);
    init(arr);
    printf("arr[0] = %d\n", arr[0]);
    for (i = 1; i <= arr[0] + 2; i++) {
        for (j = i; j <= arr[0] + 2; j++) {
            z = n - arr[i] - arr[j];
            if(binary_search(arr, j, arr[0] + 2, z)) {
                printf("%d %d %d", arr[i], arr[j], z);
                return 0;
            } 
            
        }
    }
    printf("没找到吗？");
    
    
    return 0;
}
