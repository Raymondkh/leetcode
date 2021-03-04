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

/*************************************************************************
	> File Name: mul.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 09:15:41 AM CST
 ************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

// 加个flag去标记是不是负数再处理就可以实现负数相乘！
// 定义输入大整数的字符数组
char num1[1005], num2[1005];
// 定义处理之后大整数和答案的整形数组
int n1[1005], n2[1005], ans[1005];

void output(int *arr) {
    cout << "arr_length:" << arr[0] <<endl;
    cout <<"arr :[";
    for (int i = arr[0]; i > 0; i--) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
    return ;
}

int main() {
    // 输入
    cin >> num1 >> num2;
    n1[0] = strlen(num1);
    n2[0] = strlen(num2);
    ans[0] = n1[0] + n2[0] - 1; // 两个数乘法的最少位数
    // 字符串->整形
    // str1[0]是数字的最高位 应存在 n1的n1[n1[0]] 最后一位
    // str是从0开始就是数字字符了
    //for (int i = 1, j = n1[0]; i <= n1[0]; i++, j--) {
        //n1[i] = num1[j] - '0';
    //}
    //for (int i = 1, j = n2[0]; i <= n2[0]; i++, j--) {
    //    n2[i] = num2[j] - '0';
    //}
    //上面的转换是错误的
    for (int i = 0, j = n1[0]; i < n1[0]; i++, j--) {
        n1[j] = num1[i] - '0';
    }
    for (int i = 0, j = n2[0]; i < n2[0]; i++, j--) {
        n2[j] = num2[i] - '0';
    }
    // 乘法
    for (int i = 1; i <= n1[0]; i++) {
        for (int j = 1; j <= n2[0]; j++) {
            // 注意是 += 是乘法会存在重复经过ans
            ans[i + j - 1] += n1[i] * n2[j];
        }
    }
    // 处理进位
    for (int i = 1; i <= ans[0]; i++) {
        if (ans[i] > 9) {
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
            if (i == ans[0]) {
                ans[0]++;
            }
        }
    }
    // 输出 高位->低位
    for (int i = ans[0]; i > 0; i--) {
        cout << ans[i];
    }
    cout << endl;


    return 0;
}

/*************************************************************************
	> File Name: euler15.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 10:35:54 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

int dp[25][25]; // 可以适当开多几个
long long dp_long[25][25];

int main() {
    
    for (int i = 1;i <= 21; i++) {
        for (int j = 1; j <= 21; j++) {
            // 判断是不是起点
            if (i == 1 && j == 1) {
                dp[1][1] = 1;
                dp_long[i][j] = 1; 
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                dp_long[i][j] = dp_long[i -1][j] + dp_long[i][j - 1];
            }
        }
    }
    cout << "dp_int[21][21] = " << dp[21][21] << endl;
    cout << "dp_long[21][21] = "<< dp_long[21][21] << endl;
    // 输出
    // lhh1@Aliyun day2 % ./a.out  
    // dp_int[21][21] = 407575348
    // dp_long[21][21] = 137846528820
    // 两者答案本该一样，但是由于int存不下答案所以发生了错误

    cout << "dp_int[10][10] = " << dp[10][10] << endl;
    cout << "dp_long[10][10] = "<< dp_long[10][10] << endl;
    //输出：
    //dp_int[10][10] = 48620
    //dp_long[10][10] = 48620
	
    long long ans = 1;
    for (int i = 40, j = 1; j <= 20; i--, j++) {
        ans *= i;
        ans /= j;
    }
    cout << "ans = " << ans << endl;
    // 就是公式的化简成程序，这个程序并不通用
    
	
    return 0;
}

