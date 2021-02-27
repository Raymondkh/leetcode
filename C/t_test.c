/*************************************************************************
	> File Name: 1.字符串后缀排序.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n;
string str[1005];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        reverse(str[i].begin(), str[i].end());
    }
    sort(str, str + n);
    for (int i = 0; i < n; i++) {
        reverse(str[i].begin(), str[i].end());
        cout << str[i] << endl;
    }
    return 0;
}

/*************************************************************************
	> File Name: 2.哥德巴赫最终猜想.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
#define MAX_N 200000
int prime[MAX_N + 5];
void init() {
    for(int i = 2; i <= MAX_N; i++) {
        if(prime[i]) continue;
        prime[++prime[0]] = i;
        for(int j = 2 * i; j <= MAX_N; j += i) {
            prime[j] = 1;
        }
    }
    return ;
}
int binary_search(int *arr, int x, int n) {
    int head = 0, tail = n - 1, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(arr[mid] == x) return 1;
        if(arr[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return 0;
}
int main() {
    int n;
    init();
    scanf("%d", &n);
    for(int i = 1; i <= prime[0]; i++) {
        int flag = 0;
        for(int j = i; j <= prime[0]; j++) {
            int m = n - prime[i] - prime[j];
            if(m > 0 && binary_search(prime, m, m)) {
                printf("%d %d %d\n", prime[i], prime[j], m);
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }
    return 0;
}

/*************************************************************************
	> File Name: 3.求第N个素数.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
#define MAX_N 10000

int prime[MAX_N + 5];
void init() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (prime[j] * i > MAX_N) break;
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    return ;
}

int main() {
    init();
    int n;
    scanf("%d", &n);
    printf("%d\n", prime[n]);
    return 0;
}

/*************************************************************************
	> File Name: 4.单词反转.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <iostream>
#include <string>
using namespace std;

int main() {
    string a;
    while (cin >> a) {
        int l = 0, r = a.size() - 1;
        if (a[r] == '.') {
            r--;
        }
        while (l < r) {
            swap(a[l], a[r]);
            l++, r--;
        }
        cout << a;
        if (a[a.size() - 1] == '.') {
            break;
        } else {
            cout << " ";
        }
    }
    return 0;
}

/*************************************************************************
	> File Name: 1.三角形数、五边形数和六边形数.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
typedef long long ll;

ll Triangle (ll n) {
    return n * (n + 1) / 2;
}

ll Pentagonal(ll n) {
    return n * (3 * n - 1) / 2;
}

ll Hexagonal(ll n) {
    return n * (2 * n - 1);
}

ll binary_search(ll (*arr)(ll), ll n, ll x) {
    ll head = 1, tail = n, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (arr(mid) == x) return mid;
        if (arr(mid) < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

int main() {
    ll n = 1;
    while (~scanf("%lld", &n)) {
        ll temp = Hexagonal(n);
        int flag = binary_search(Pentagonal, temp, temp);
        printf("%s\n", flag == -1 ? "NO" : "YES");
    }
    return 0;
}

/*************************************************************************
	> File Name: 2.哥德巴赫最终猜想.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
#define MAX_N 200000
int prime[MAX_N + 5];
void init() {
    for(int i = 2; i <= MAX_N; i++) {
        if(prime[i]) continue;
        prime[++prime[0]] = i;
        for(int j = 2 * i; j <= MAX_N; j += i) {
            prime[j] = 1;
        }
    }
    return ;
}
int binary_search(int *arr, int x, int n) {
    int head = 0, tail = n - 1, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(arr[mid] == x) return 1;
        if(arr[mid] > x) tail = mid - 1;
        else head = mid + 1;
    }
    return 0;
}
int main() {
    int n;
    init();
    scanf("%d", &n);
    for(int i = 1; i <= prime[0]; i++) {
        int flag = 0;
        for(int j = i; j <= prime[0]; j++) {
            int m = n - prime[i] - prime[j];
            if(m > 0 && binary_search(prime, m, m)) {
                printf("%d %d %d\n", prime[i], prime[j], m);
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }
    return 0;
}

/*************************************************************************
	> File Name: 3.变换数字.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>

int main() {
	int n;
    scanf("%d", &n);
    printf("%lld\n", (n << 16) | (n >> 16));
    return 0;
}

/*************************************************************************
	> File Name: 4.打印范围内的素数.cpp
	> Author: 
	> Mail: 
	> Created Time: 
 ************************************************************************/
#include <stdio.h>
#define max_n 1000000
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

int prime[max_n + 5];
void init() {
    for (int i = 2; i <= max_n; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] > max_n) break;
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    return ;
}

int main() {
    int m, n;
    init();
    scanf("%d%d", &m, &n);
    if (m > n) swap(m, n);
    int flag = 0;
    for (int i = 1; prime[i] <= n && i <= prime[0]; i++) {
        if (prime[i] < m) continue;
        flag++;
        printf("%d\n", prime[i]);
    }
    if (!flag) printf("0\n");
    return 0;;
}

