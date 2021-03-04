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

/*************************************************************************
	> File Name: euler25.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 07:25:20 PM CST
 ************************************************************************/


#include <iostream>
using namespace std;

int func(int *n1, int *n2) {
    // f(n) = f(n - 1)大 + f(n - 2)小;
    // 循环就是 大加在小上，原来的大变成下一次的小
    // 所以n1=>f(n-2)大， n2=>f(n-1)小
    n2[0] = n1[0];
    for (int i = 1; i <= n2[0]; i++) {
        n2[i] += n1[i];
        if (n2[i] > 9) {
            n2[i + 1] += n2[i] / 10;
            n2[i] %= 10;
            if (i == n2[0]){
                n2[0]++;
            }
        }
    }
    return n2[0] >= 1000;
}


int main() {
    // 长度为1，值是1？
    int num[2][1100] = {{1, 1}, {1, 1}};
    int a = 0, b = 1; // 用于循环相加实现斐波那契数列形式
    for (int i = 3; 1; i++) {
        // 注意这一传入的是指针
        if (func(num[a], num[b])) {
            cout << i << endl;
            break;
        }
	cout <<"before" << endl;
        cout << "num[a] = " << num[a] << "  num[a][0] = " << num[a][0] << endl;
        cout << "num[b] = " << num[b] << "  num[b][0] = " << num[b][0] << endl;
        cout << endl;

        swap(num[a], num[b]); // 始终保持小项在前
	    
	cout << "after" << endl;
	cout << "num[a] = " << num[a] << "  num[a][0] = " << num[a][0] << endl;
        cout << "num[b] = " << num[b] << "  num[b][0] = " << num[b][0] << endl;
        cout << endl;

    }
    return 0;
}
// 答案：4782
/*
before
num[a] = 0x7ffc50bae8f0  num[a][0] = 972
num[b] = 0x7ffc50bafa20  num[b][0] = 973

after
num[a] = 0x7ffc50bae8f0  num[a][0] = 973
num[b] = 0x7ffc50bafa20  num[b][0] = 972

由输出可以可知swap是更换两个数组的内容，可能是因为是数组地址是固定要寻址的原因才是
更换内容，然后我觉得如果是两个指针，直接更换指针即可，内容索引方式是一样的

同时可见，a是原本大的，b是原本小的；计算之后将大的叠加在小的上面
所以计算之后b变成大的，a变成小的。swap之后继续保持a是大的，循环交换实现斐波那契数列
*/
