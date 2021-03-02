/*************************************************************************
	> File Name: euler1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Mar 2021 09:14:42 PM CST
 ************************************************************************/
// 欧拉计划第一题
#include <iostream>
using namespace std;

int main() {
    int ans = 0;
    for (int i = 3; i < 1000; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            ans += i;
        }
    }
    cout << ans << endl;
    return 0;
}
// 答案：233168


