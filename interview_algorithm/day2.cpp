/*************************************************************************
	> File Name: add.cpp // 欧拉13题
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 06:31:33 PM CST
 ************************************************************************/

#include <iostream>
#include <cstring> // 在c++使用c的头文件，即删除.h改为前面加c
using namespace std;

// 存入输入字符串
char num1[1005], num2[1005];
// n1, n2 测长并倒序的整理字符串变成十进制数组，ans 是答案
int n1[1005], n2[1005], ans[1005]; 


int main() {

    cin >> num1 >> num2;
    n1[0] = strlen(num1); // 第一位存字符串的长度
    n2[0] = strlen(num2);
    // ans的长度至少为比较长一个字符串的长度
    ans[0] = max(n1[0], n2[0]);
    for (int i  = 1, j = n1[0] - 1; i <= n1[0]; i++, j--) {
        n1[i] = num1[j] - '0';
    }
    for (int i = 1, j = n2[0] - 1; i <= n2[0]; i++, j--) {
        n2[i] = num2[j] - '0';
    }
    // 开始逐位相加
    for (int i = 1; i <= ans[0]; i++) {
        ans[i] = n1[i] + n2[i];
    }
    // 开始进位
    for (int i = 1; i <= ans[0]; i++) {
        if (ans[i] > 9) {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
            if (i == ans[0]) {
                ans[0]++;
            }
        }
    }
    // 加法和进位可以写在一起
    // 输出答案
    for (int i = ans[0]; i > 0; i--) {
        cout << ans[i];
    }
    cout << endl;



    return 0;
}