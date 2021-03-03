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

/*************************************************************************
	> File Name: euler4.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 07:39:17 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;
#define MAX 1000

int func(int x) {
    int rev = 0, raw = x;
    while (x) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return rev == raw;
}


int main() {
    
    int ans = 0, a, b;
    for (int i = 100; i < MAX; i++) {
        for (int j = i; j < MAX; j++) {
            int t = i * j;
            if (func(t) && ans < t) {
                ans = t;
                a = i;
                b = j;
            }
        }
    }
    cout << a << " "<< b<< endl;
    cout << ans;

    return 0;
}
// 答案：
// 913 993
// 906609%  

/*************************************************************************
	> File Name: euler4_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 07:46:48 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

int func(int x) {
    int rev = 0, raw = x;
    while (x) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return rev == raw;
}


int main() {

    int ans = 0, a, b;
    int max = 999 * 999;
    int flag = 0;
    for (int i = max; i > 10000; i--) {
        if (!func(i)) continue;

        for (int j = 999; j > 100; j--) {
            if (i / j < 100) break;
            if (i % j) continue;
            ans = i;
            a = j;
            b = ans / a;
            flag = 1;
            break;
        }
        if (flag) break;

    }
    cout << a << " " << b << endl;
    cout << ans;
    return 0;
}

/*************************************************************************
	> File Name: euler6.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 08:26:00 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;

int main() {
    int psum = 0, sump = 0;
    for (int i = 1; i <= 100; i++){
        sump += i;
        psum += i * i;
    }

    cout << sump * sump - psum<< endl;
    sump *= sump;
    cout << sump - psum << endl;

    psum = 0;
    sump = 0;
    for (int i = 1; i <= 100; i++) {
        psum += i * i;
        sump += i;
    }
    sump *= sump;
    cout << sump - psum << endl;
    return 0;
}

/*************************************************************************
	> File Name: euler8.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 03 Mar 2021 09:44:14 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;
#define MAX 1000


int main() {
    char num[MAX + 5] = {0};
    cin >> num;
    long long ans = 0, now = 1;
    int cnt = 0;
    for (int i = 0; i < 1000; i++) {
        if (i < 13) {
            // 初始化
            now *= num[i] - '0'; // 转化为十进制的数字
        } else {
            if (num[i] == '0') {
                cnt++;
            } else {
                now *= num[i] - '0';
            }
            if (num[i - 13] == '0') {
                cnt--;
            } else {
                now /= num[i - 13] - '0';
            }
        }
        if (cnt == 0) ans = max(ans, now);
    }
    cout << ans << endl;


    return 0;
}

// input处理          :%s/ //g
// %s字符串  / /杆空格杆空 表示将空格代替为空  /g全局替换



