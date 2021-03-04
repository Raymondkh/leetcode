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


/*************************************************************************
	> File Name: hzoj380.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 06:19:05 PM CST
 ************************************************************************/
// 注意这个文件用了很多C++的东西！！！
#include <iostream>
#include <algorithm> // sort算法
#include <string> // 不用加c就是C++的头文件了吗？
using namespace std;

struct node {
    int cnt;
    string num;  
    // 这类用了C++的类，类内重载了很多操作
    // 包括 < > 等等，所以下面能直接return a.num > b.num字典序
};


// 对自定义类型进行排序，如结构体
// const 是为了避免在函数里对原对象进行操作改变值
// & 引用是为了避免拷贝？？
// 这个是规定的
bool cmp(const node &a, const node &b) {
    if (a.num.size() == b.num.size()) {
        return a.num > b.num; // 字典序，C++类方法重载了符号
    }

    return a.num.size() > b.num.size();
}



void output(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout <<  arr[i] << " ";
    }
    cout << endl;
    return ;
}


int main() {
    
    int n; 
    node bio[105];  // 这里没加struct是C++的优化吧
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> bio[i].num;
        bio[i].cnt = i;
    }
    sort(bio + 1, bio + n + 1, cmp);
    cout << bio[1].cnt << endl << bio[1].num << endl;

    return 0;
}

/*************************************************************************
	> File Name: hzoj386.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 08:39:30 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct node {
    int cnt; // 西瓜的编号
    int num; // 西瓜的数量
};

bool cmp(const node &a, const node &b) {
    return a.num < b.num;
}
int n, m; // 
node wm[100005];

int main() {

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &wm[i].num);
        wm[i].cnt = i;
    }
    sort(wm + 1, wm + n + 1, cmp);
    
    for (int i = 1; i <= m; i++) {
        int l = 1, r = n, temp;
        scanf("%d", &temp);
        while (l <= r) {
            int mid = (r + l) >> 1;
            if (wm[mid].num == temp) {
                printf("%d\n", wm[mid].cnt);
                temp = -1; // 用作一个标志位去表示找到
                break;
            }
            if (wm[mid].num < temp) l = mid + 1;
            else r = mid - 1;
        }
        if (t != -1) printf("0\n"); 
        
    }


    return 0;
}

/*************************************************************************
	> File Name: hzoj387.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 09:16:12 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct node {
    int cnt;
    long long num;
};

bool cmp(const node &a, const node &b) {
    return a.num < b.num;
}

node wm[100005];
int main() {

    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &wm[i].num);
        wm[i].cnt = i;
    }
    sort(wm + 1, wm + 1 + n, cmp);
    
    for (int i = 1; i <= m; i++) {
        long long temp;
        int l = 1, r = n + 1;
        scanf("%lld", &temp);
        while (l != r) {
            int mid = (l + r) >> 1;
            if (wm[mid].num < temp) l = mid + 1;
            else r = mid;
        }
        if (r == n + 1) printf("0\n");
        else printf("%d\n", wm[l].cnt);
    }

    return 0;
}

/*************************************************************************
	> File Name: hzoj387_teacher.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 04 Mar 2021 09:42:10 PM CST
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct node {
    int cnt, num;
};

bool cmp(const node &a, const node &b) {
    return a.num < b.num;
}

node wm[100005];
int m, n;

int main() {
    
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%d", &wm[i].num);
        wm[i].cnt = i + 1;
    }
    sort(wm, wm + n, cmp);
    wm[n].cnt = 0, wm[n].num = 2000000000; // 虚拟瓜位
    // 这里好处在于如果是不存在答案直接输出虚拟瓜位的cnt即可
    // 不需要特判
    for (int i = 0; i < n; i++) {
        int t, l = 0, r = n;
        scanf("%d", &t);
        while (l != r) {
            int mid = (l + r) / 2;
            if (wm[mid].num >= t) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", wm[r].cnt);
    }


    return 0;
}
