/*************************************************************************
	> File Name: euler.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Mar 2021 09:14:42 PM CST
 ************************************************************************/


#include <iostream>
using namespace std;

int main() {
    int ans = 0;
    for (int i = 3; i < 1000; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            ans += i;
        }
    }
    cout << "first try:" << ans << endl;

    // 优化过后的思想： 3的等差数列 + 5的等差数列 - 15的等差数列 
    int a3 = (3 + 999) * 333 / 2;
    int a5 = (5 + 995) * 199 / 2;
    int a15 = (15 + 990) * 66 / 2;
    cout << "second try:" <<  a3 + a5 - a15 << endl;
    return 0;
}

// 答案：233168


