// 1.red_black_tree_insert.cpp  1.red_black_tree_insert_rep.cpp  2.red_black_tree_complete.cpp

/*************************************************************************
	> File Name: 1.red_black_tree_insert.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Mar 2021 12:35:18 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int color; // 0 red； 1 black； 2 double black
    struct Node *lchild, *rchild; 
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->data = 0;
    NIL->color = 1; // 叶节点一定是黑色的
    NIL->lchild = NIL->rchild = NIL;
    return ;
}


Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->color = 0; // 初始化红色节点
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    // 首先判断是否有红色子节点，如无则一定不需要调整
    if (!has_red_child(root)) return root;
    int flag = 0; 
    // 情况1，这里的代码船长是偷懒了，并没有判断情况1，但是这样调整是通用的，
    // 即使没有冲突调整之后也不会错
    // 之后补正式的判断看会不会出错！！
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        // 红色上浮
        goto insert_end;
    }
    // 情况2判断
    // 判断root中左孩子或右孩子有红色其其孙子有红色才修改flag
    if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1; // L
    if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2; // R
    if (flag == 0) return root; // 没有发生冲突
    if (flag == 1) {
        if (root->lchild->rchild->color == 0) {
            // LR需要小左旋
            root->lchild = left_rotate(root->lchild);
        }
        // 之后都是LL了，则直接大右旋
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->color == 0) {
            // RL需要小右旋
            root->rchild = right_rotate(root->lchild);
        }
        // 现在都是RR了直接大左旋
        root = left_rotate(root);
    }
    // 颜色调整都需要这样调整写在一起
insert_end:
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}


Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->data == key) return root;
    if (key < root->data) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

// 如果实现某些功能比较麻烦那就封装一层，不然就封装两层
Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = 1; // 根节点一定是黑色的
    return root;
}



void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("(%d| %d, %d, %d)\n", 
          root->color, 
          root->data,
          root->lchild->data,
          root->rchild->data);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}


int main() {

    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: root = insert(root, val);
        }
        if (op == 1) {
            output(root);
            printf("----------------\n");
        }
    }

    return 0;
}



/*************************************************************************
	> File Name: 1.red_black_tree_insert_rep.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Mar 2021 11:34:02 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int color; // 0红色 1黑色
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor)) 
void init_NIL() {
    NIL->data = 0;
    NIL->color = 1; // 叶节点是黑色的
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->color = 0; // 创建的新节点是红色的
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}


Node *insert_maintain(Node *root) {
    // 首先判断是否有红色孩子，如果没有则一定不需要调整
    if (!has_red_child(root)) return root;
    int flag = 0;
    // 情况1, 从祖父看父亲和叔叔还有儿子都是红色的
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        goto insert_end;
    }
    // 情况1不符合则判断情况2
    // 从祖父节点来看，父亲节点和儿子节点都为红色
    // LL/LR/RR/RL
    if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1; // L
    if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2; // R
    if (flag == 0) return root; // 没有冲突
    if (flag == 1) {
        if (root->lchild->rchild->color == 0) {
            // LR 需要小左旋变成LL
            root->lchild = left_rotate(root->lchild);
        }
        // LL 大右旋
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->color == 0) {
            // RL 需要小右旋变成RR
            root->rchild = right_rotate(root->rchild);
        }
        // RR
        root = left_rotate(root);
    }
    // 调整颜色
insert_end:
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}

Node *__insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (root->data == val) return root;
    if (val < root->data) {
        root->lchild = __insert(root->lchild, val);
    } else {
        root->rchild = __insert(root->rchild, val);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int val) {
    root = __insert(root, val);
    root->color = 1; // 根节点一定是黑色的
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("%d| %d, l = %d, r = %d\n", 
          root->color,
          root->data,
          root->lchild->data,
          root->rchild->data);
    return ;
}


void output(Node *root) {
    if (root == NIL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}



int main() {

    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: root = insert(root, val); break;
            
        }
        if (op == 1) {
            output(root);
            printf("---------------\n");
        }
    }


    return 0;
}




/*************************************************************************
	> File Name: 2.red_black_tree_insert_complete.cpp // 完整版
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Mar 2021 12:35:18 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int color; // 0 red； 1 black； 2 double black
    struct Node *lchild, *rchild; 
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->data = 0;
    NIL->color = 1; // 叶节点一定是黑色的
    NIL->lchild = NIL->rchild = NIL;
    return ;
}


Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->color = 0; // 初始化红色节点
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    // 首先判断是否有红色子节点，如无则一定不需要调整
    if (!has_red_child(root)) return root;
    int flag = 0; 
    // 情况1，这里的代码船长是偷懒了，并没有判断情况1，但是这样调整是通用的，
    // 即使没有冲突调整之后也不会错
    // 之后补正式的判断看会不会出错！！
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        // 红色上浮
        goto insert_end;
    }
    // 情况2判断
    // 判断root中左孩子或右孩子有红色其其孙子有红色才修改flag
    if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1; // L
    if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2; // R
    if (flag == 0) return root; // 没有发生冲突
    if (flag == 1) {
        if (root->lchild->rchild->color == 0) {
            // LR需要小左旋
            root->lchild = left_rotate(root->lchild);
        }
        // 之后都是LL了，则直接大右旋
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->color == 0) {
            // RL需要小右旋
            root->rchild = right_rotate(root->rchild); // ?
        }
        // 现在都是RR了直接大左旋
        root = left_rotate(root);
    }
    // 颜色调整都需要这样调整写在一起
insert_end:
    root->color = 0;
    root->lchild->color = root->rchild->color = 1;
    return root;
}


Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->data == key) return root;
    if (key < root->data) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

// 如果实现某些功能比较麻烦那就封装一层，不然就封装两层
Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = 1; // 根节点一定是黑色的
    return root;
}

int predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp->data;
}


Node *erase_maintain(Node *root) {
    // 两个子节点都没有双黑节点则不需要调整
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;
    // 首先判断兄弟节点是红色的情况
    // 此时逻辑上已经有一个节点是双黑节点了,则只需要判断是否有红色节点
    if (has_red_child(root)) {
        int flag = 0; // 判断左右旋
        root->color = 0; // 原根节点标红
        if (root->lchild->color == 0) {
            root = right_rotate(root);
            flag = 1;
        } else {
            root = left_rotate(root);
            flag = 2;
        }
        root->color = 1; // 新根节点变黑
        if (flag == 1) {
            // 右旋在右子树递归
            root->rchild = erase_maintain(root->rchild);
        } else {
            // 左旋在左子树递归
            root->lchild = erase_maintain(root->lchild);
        }
        return root;
    }

    // 此时兄弟节点是黑色的情况,且兄弟节点的两个子节点黑色的不是LL,LR,RR,RL
    if ((root->lchild->color == 2 && !has_red_child(root->rchild)) || 
        (root->rchild->color == 2 && !has_red_child(root->lchild))) {
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            root->color += 1; // 可能直接调整好，也可能将双黑节点上传
            return root;
        }
    
    // 此时就是判断LL,LR,RR,RL情况
    if (root->lchild->color == 2) {
        // 此时去除双重的的一层黑,直播那里没有自己加的！！！
        root->lchild->color -= 1;
        // 双黑节点在左边，兄弟在右边 R*
        if (root->rchild->rchild->color != 0) {
            // 严格的RL类型，需要小右旋, 必须这样判断，因为LR情况是严格的
            root->rchild->color = 0;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = 1;
        }
        root = left_rotate(root);
        root->color = root->lchild->color; // 新根节点为原根节点的颜色
    } else {
        // 去掉一层黑,自己加的
        root->rchild->color -= 1;
        if (root->lchild->lchild->color != 0) {
            // LR类型
            root->lchild->color = 0;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = 1;
        }

        root = right_rotate(root);
        root->color = root->rchild->color; // 
    }
    root->lchild->color = root->rchild->color = 1;
    return root;
}

Node *__erase(Node *root, int val) {
    if (root == NIL) return NIL;
    if (val < root->data) {
        root->lchild = __erase(root->lchild, val);
    } else if (val > root->data) {
        root->rchild = __erase(root->rchild, val);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            // 度为0 or 1
            Node *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            temp->color += root->color;
            free(root);
            return temp;
            //为什么不在此时开始调整呢？
            //虽然产生双重黑节点是度为0的时候生成，但是这样调整是删除调整是在父亲
            //节点调整的，所以还需要返回到上一层
        } else {
            // 度为2
            int t = predecessor(root);
            root->data = t;
            root->lchild = __erase(root->lchild, t);
        }
    }
    // 删除调整
    return erase_maintain(root);

}


// 删除，也进行封装
Node *erase(Node *root, int val) {
    root = __erase(root, val);
    root->color = 1;
    return root;
}


void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("(%d| %d, %d, %d)\n", 
          root->color, 
          root->data,
          root->lchild->data,
          root->rchild->data);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}


int main() {

    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        if (op == 1 || op == 2)  {
            output(root);
            printf("----------------\n");
        }
    }

    return 0;
}

