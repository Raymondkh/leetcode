// 1.binary_search_tree.cpp  2.binary_search_tree_pro.cpp  3.avl.cpp  binary_search_tree.cpp

/*************************************************************************
	> File Name: binary_search_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Mar 2021 08:09:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define L(n) (n ? n->lchild : NULL)
#define R(n) (n ? n->rchild : NULL)
#define VAL(n) (n ? n->data : 0)

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search(root->lchild, key);
    else return search(root->rchild, key);
} 



Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (val == root->data) return root;
    if (val < root->data) {
        root->lchild = insert(root->lchild, val);
    } else {
        root->rchild = insert(root->rchild, val);
    }
    return root;
}

int predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp->data;
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (val < root->data) {
        root->lchild = erase(root->lchild, val);
    } else if (val > root->data) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            int t = predecessor(root);
            root->data = t;
            root->lchild = erase(root->lchild, t);
        }
    }
    return root;
}


void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d(), l = %d, r = %d\n", VAL(root), VAL(L(root)), VAL(R(root)));
    output(root->rchild);
    return ;
}


int main() {

    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: {
                printf("search %d, the result = %d\n", val, search(root, val));
            } break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }

        if (op == 1 || op == 2) {
            output(root);
            printf("----------------------------\n");
        }
    }

    return 0;
}


/*************************************************************************
	> File Name: 2.binary_search_tree_pro.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Mar 2021 08:09:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define L(n) (n ? n->lchild : NULL)
#define R(n) (n ? n->rchild : NULL)
#define VAL(n) (n ? n->data : 0)
#define SIZE(n) (n ? n->size : 0)
#define LS(n) SIZE(L(n))

typedef struct Node {
    int data;
    int size; // 节点个数
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->size = 1;
    p->lchild = p->rchild = NULL;
    return p;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search(root->lchild, key);
    else return search(root->rchild, key);
} 

// 查找排名为k的值
int search_k(Node *root, int k) {
    if (root == NULL) return 0;
    if (LS(root) == k - 1) return root->data;
    if (k <= LS(root)) return search_k(root->lchild, k);
    else return search_k(root->rchild, k - LS(root) - 1);
}

void output(Node *root);
// 查找前k个值
void top_k(Node *root, int k) {
    if (root == NULL) return ;
    if (k - 1 == LS(root)) {
        output(root->lchild);
        printf("%d(%d), l = %d, r = %d\n", VAL(root), SIZE(root), VAL(L(root)), VAL(R(root)));
        return ;
    } else if (k <= LS(root)) {
        top_k(root->lchild, k);
    } else {
        output(root->lchild);
        printf("%d(%d), l = %d, r = %d\n", VAL(root), SIZE(root), VAL(L(root)), VAL(R(root)));
        top_k(root->rchild, k - LS(root) - 1);
    }
    return ;
}



void update_size(Node *root) {
    
    root->size = SIZE(L(root)) + SIZE(R(root)) + 1;

    return ;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (val == root->data) return root;
    if (val < root->data) {
        root->lchild = insert(root->lchild, val);
    } else {
        root->rchild = insert(root->rchild, val);
    }
    update_size(root);
    return root;
}

int predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp->data;
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (val < root->data) {
        root->lchild = erase(root->lchild, val);
    } else if (val > root->data) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            int t = predecessor(root);
            root->data = t;
            root->lchild = erase(root->lchild, t);
        }
    }
    update_size(root);
    return root;
}


void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d(%d), l = %d, r = %d\n", VAL(root), SIZE(root), VAL(L(root)), VAL(R(root)));
    output(root->rchild);
    return ;
}


int main() {

    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: {
                printf("search %d, the result = %d\n", val, search(root, val));
            } break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: {
                printf("NO.%d = %d\n", val, search_k(root, val));
            } break;
            case 4: {
                top_k(root, val);
            } break;
        }

        if (op == 1 || op == 2) {
            output(root);
            printf("----------------------------\n");
        }
    }

    return 0;
}


/*************************************************************************
	> File Name: 3.avl.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Mar 2021 08:53:07 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define L(n) (n->lchild) 
#define R(n) (n->rchild) 
#define H(n) (n->h)
#define VAL(n) (n->data)

typedef struct Node {
    int data;
    int h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->data = 0;
    NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}


Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void update_height(Node *root) {
    root->h = (H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root))) + 1;
    return ;
}


Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    update_height(root);
    update_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    update_height(root);
    update_height(temp);
    return temp;
}



Node *maintain(Node *root) {
    if (abs(H(root->lchild) - H(root->rchild)) <= 1) return root;
    if (H(root->lchild) > H(root->rchild)) {
        if (H(root->lchild->lchild) < H(root->lchild->rchild)) {
            // LR
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (H(root->rchild->lchild) > H(root->rchild->rchild)) {
            // RL
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}


Node *insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (val == root->data) return root;
    if (val < root->data) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    update_height(root);
    return maintain(root);
}

int predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp->data;
}

Node *erase(Node *root, int val) {
    if (root == NIL) return NIL;
    if (val < root->data) {
        root->lchild = erase(root->lchild, val);
    } else if (val > root->data) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = (root->lchild == NIL ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            int t = predecessor(root);
            root->data = t;
            root->lchild = erase(root->lchild, t);
        }
    }
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void inorder(Node *root) {
    if (root == NIL) return ;
    inorder(root->lchild);
    printf("%d(%d) l = %d, r = %d\n", VAL(root), H(root), VAL(L(root)), VAL(R(root)));
    inorder(root->rchild);
    return ;
}

void preorder(Node *root) {
    if (root == NIL) return ;
    printf("%d(%d) l = %d, r = %d\n", VAL(root), H(root), VAL(L(root)), VAL(R(root)));
    preorder(root->lchild);
    preorder(root->rchild);
    return ;
    
}


int main() {

    int op, val, x;
    Node *root = NIL;
    while (~scanf("%d%d%d", &op, &val, &x)) {
        switch(op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        // x = 1中序遍历， x = 0 先序遍历
        if (x) {
            inorder(root); 
        } else {
            preorder(root);
        }
        printf("------------------------------\n");
    }


    return 0;
}
/*************************************************************************
	> File Name: binary_search_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Mar 2021 08:09:38 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define L(n) (n ? n->lchild : NULL)
#define R(n) (n ? n->rchild : NULL)
#define VAL(n) (n ? n->data : 0)

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    if (key < root->data) return search(root->lchild, key);
    else return search(root->rchild, key);
} 



Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (val == root->data) return root;
    if (val < root->data) {
        root->lchild = insert(root->lchild, val);
    } else {
        root->rchild = insert(root->rchild, val);
    }
    return root;
}

int predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp->data;
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (val < root->data) {
        root->lchild = erase(root->lchild, val);
    } else if (val > root->data) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            int t = predecessor(root);
            root->data = t;
            root->lchild = erase(root->lchild, t);
        }
    }
    return root;
}


void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("%d(), l = %d, r = %d\n", VAL(root), VAL(L(root)), VAL(R(root)));
    output(root->rchild);
    return ;
}


int main() {

    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: {
                printf("search %d, the result = %d\n", val, search(root, val));
            } break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }

        if (op == 1 || op == 2) {
            output(root);
            printf("----------------------------\n");
        }
    }

    return 0;
}
