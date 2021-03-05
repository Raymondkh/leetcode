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

/*************************************************************************
	> File Name: hzoj389.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 05 Mar 2021 10:37:16 AM CST
 ************************************************************************/
#include <iostream>
#include <algorithm>
using namespace std;

int m, n, num[100005];
int l, r;
void output(int *, int);

// mid是最小距离，在mid的要求下能安排多少个人
int func(int mid) {
    int ans = 1;
    int l = num[0];
    for (int i = 1; i < m; i++) {
        if (num[i] - l < mid) continue;
        ans++;
        l = num[i];
    }
    return ans;
}



int binary_search() {
    while (l != r) {
        int mid = (l + r + 1) / 2;
        int s = func(mid); // 得出能容纳的人数
        if (s >= n) l = mid;
        else r = mid - 1;
    }
    return l;
}



int main() {

    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        cin >> num[i];
    }
    sort(num, num + m);
    output(num, m);
    r = num[m - 1] - num[0];
    cout << "l = " << l << "  r = " << r << endl;
    cout << binary_search() << endl;

    return 0;
}

// 调试输出看看数据有没有排序好
void output(int *num, int m) {
    
    for (int i = 0; i < m; i++) {
        cout << num[i] << " ";
    }

    cout << endl;
    return ;

}

/*************************************************************************
	> File Name: hzoj390.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 05 Mar 2021 09:46:50 AM CST
 ************************************************************************/
// 二分答案题目！！！答案满足单调性

#include <iostream>
using namespace std;

// 原木的根数，切的长度，每根原木的长度
int n, m, num[100005];
int l, r;

int func(int x) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
       ans += num[i] / x;
    }
    return ans;
}


int bs() {
    while (l != r) {
        int mid = (l + r + 1) / 2; // 为什么这里就要+1呢？
        // 如果不+1就发生了死循环了
        // 那什么情况应该加呢？
        int s = func(mid);   // func函数求出在所有原木中能切出多少根
        if (s >= m) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        r = max(r, num[i]);   
        // r是最长原木的长度？
        // 是指二分最长情况是最长原木的长度，即只能切出1根
        // 而l初始化为0则是0根
    }
    // 答案封装的bs()函数里面求得
    cout << bs() << endl;

    return 0;
}
/*
分析：
原木切得长度范围： [0, 1, 最长原木长度]
0是为针对答案不存在设置的虚拟位
==>输出原木长度， 0段， [所有原木长度和， 1]段
设定的是m段，所以 m可能不存在于当前情况，或者 [所有原木长度和, m, 1]之间
这样是单调的，且满足 111100000找到最后一个1,即为满足条件最长原木段的需求

步骤：
1、确定是二分答案的问题？ 答案满足单调性
2、分的答案是谁能切多少段？ --原木切断长度
3、分清l， r上界下界
4、二分的特殊情况：111110000， 000001111
    最大最小这些字眼！
*/


