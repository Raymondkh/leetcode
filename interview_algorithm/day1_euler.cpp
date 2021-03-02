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

/*************************************************************************
	> File Name: euler2.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Mar 2021 09:51:28 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

#define N 1000000
#define MAX 4000000
int num[N + 5];


int main() {
    int end = 0;
    num[1] = 1, num[2] = 2;
    // 由于不知道什么时候该停止循环，就写死循环，
    // 然后根据判断break跳出
    for (int i = 3; 1; i++) {
        num[i] = num[i - 1] + num[i - 2];
        if (num[i] >= MAX) {
            end = i;
            break;
        }
    }
    long long ans = 0;
    for (int i = 1; i < end; i++) {
        if (num[i] % 2 == 0) {
            ans += num[i];
        }
    }
    
    cout << ans << endl;
    return 0;
}
// 答案：4613732

/*************************************************************************
	> File Name: euler2_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 02 Mar 2021 10:03:30 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;
#define MAX 4000000

int main() {

    int a = 1, b = 2, ans = 0;
    while (b < MAX) {
        if (b % 2 == 0) {
            ans += b;
        }
        b = a + b;
        a = b - a;
    }
    cout << ans << endl;

    return 0;
}
