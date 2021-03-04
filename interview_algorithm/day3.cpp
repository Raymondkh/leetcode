/*************************************************************************
	> File Name: sort.cpp // 简单的使用C++的sort算法
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 06:19:05 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm> // sort算法
using namespace std;

// 这代表前者a需要大于后者b
bool cmp(int a, int b) {
    return a > b;
}

void output(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout <<  arr[i] << " ";
    }
    cout << endl;
    return ;
}

int main() {
    int n, num[1005] = {0};
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }
    // sort默认情况下是从小到大
    sort(num, num + n);
    // 如果需要自定义情况，就需要写函数
    output(num, n);
    
    // 自定义降序
    sort(num, num + n, cmp);
    output(num, n);

    return 0;
}
