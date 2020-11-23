# 树与二叉树

### 二叉树的基本概念
- 树：
  1. 要么为空，要么有且仅有一个根节点root,每个分支又可以看成是一个树，所以树是递归的,在运算的时可使用递归的方法处理
  2. 双亲结点,孩子结点,兄弟结点,堂兄弟结点
  3. 结点的祖先:从根节点到该节点的所有结点; 结点的子孙
  4. 树的深度:最大层次
  5. 树的高度
  6. 有序树,无序树
  7. 森林:m棵互不相交的树的集合

### 为什么要专门研究二叉树？
- 所有树都能转化为唯一对应的二叉树来运算,具有一般性, 既能转化也能还原(具体方法还未知)？
- 二叉树不是树的一特殊情况,二者分别是两个概念
  1. 因为二叉树会严格区分左子树和右子树,即使只有一个孩子结点也会严格区分,而树的话只有一个孩子结点则都一样
  2. 例如如果只有是三个结点,二叉树会有五种形态,而树只会有两种

### 二叉树
- 五种基本形态
  1. 空树
  2. 只有一个根节点
  3. 根节点+左子树
  4. 根节点+右子树
  5. 根节点+左子树+右子树

### 性质
1. 第i层至多有2^(i-1)个结点, 至少有1个结点
2. 深度为k的二叉树至多有2^k-1个结点
3. 对于任何一棵二叉树如果其叶子节点数量为n1,度为2的节点数为n2,则n1=n2+1

### 二叉树的特殊情况: 满二叉树和完全二叉树
- 两种二叉树在顺序存储的情况是可以复原的
1. 满二叉树
  - 所有层都是满的,叶子结点都是最底层
  - 所以在顺序储存时可以看到每个位置都是有元素的
2. 完全二叉树
  - 按顺序标号之后每个号码在满二叉树中都是一一对应的
  - 特点
  1. 叶子结点只能分布在倒数第一第二层
  2. 对任一结点,如果其右子树的最大层次为i,则其左子树的最大层次必为i或i+1
  
### 二叉树的存储方式
1. 顺序储存（数组）
- 优点：便于查找，可以通过计算直接获得元素
- 缺点：除了满二叉树和完全二叉树之外，空间利用率不高，且数组的大小是固定的
- 用途：堆

2. 二叉链表（lchild+data+rchild）

3. 三叉链表（lchild+data+parent+rchild）：适用于查找双亲节点比较多的情况


### 二叉树的遍历
1. 遍历：顺着一条路径去访问二叉树的所有节点，每个节点只访问一次
2. 访问：定义很广，可以是对节点的各种处理，比如输出、修改等，但是访问不能破坏原来的数据结构
3. 目的：目的得到所有节点的线性排列
4. 用途：对树结构的插入删除修改查找等操作
5. 注意：每一个子树都是一个二叉树（根节点，左子树，右子树），使用递归遍历时需要明白这一点
- [代码资料](https://blog.csdn.net/coxhuang/article/details/90547520)

#### 先序遍历（根-->左子树-->右子树）
```python
class TreeNode:
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None

class Solution:
    def preorder_recursion(self, root):
        """递归方法"""
        if not root:  # 如果根节点为空则不操作
            return 
        print(root.data)
        self.preorder_recursion(root.left)
        self.preorder_recursion(root.right)

    def preorder(self, root):
        """非递归的方法实现,还不太熟悉"""
        stack_node = [root]  # 栈
        list_node = [] # 先序遍历结果存放列表

        while stack_node:
            node = stack.pop() # 栈顶节点出栈
            if not node:
                continue
            list_node.append(node.data)
            # 先压入右节点，栈的特点先入后出
            stack_node.append(node.right)  
            # 再压入左节点
            stack_node.append(node.left)
        print(list_node)
        return list_node
```
#### 中序遍历（左子树-->根-->右子树）
```python
class TreeNode:
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None

class Solution:
    def inorder_recursion(self, root):
        """递归方法"""
        if root == None:
            return 
        self.inorder_recursion(root.left)
        print(root.data)
        self.inorder_recursion(root.right)

    def inorder(self, root):
        """非递归的方法实现,还不太熟悉"""
        stack_node = [root]  # 栈
        list_node = [] # 中序遍历结果存放列表
        node_p = root # 当前节点

        while stack_node or node_p: # 当前节点不为空或栈不为空
            while node_p: # 一直移动到最左端
                stack_node.append(node_p) # 节点压栈
                node_p = node_p.left # 指针左移
            node = stack_node.pop() # 出栈
            list_node.append(node.data) # 获取节点数据
            node_p = node.right # 获取右节点
        print(list_node)
        return list_node
```
#### 后序遍历（左子树-->右子树-->根）
```python
class TreeNode:
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None

class Solution:
    def postorder_recursion(self, root):
        """递归方法"""
        if root == None:
            return 
        self.postorder_recursion(root.left)
        self.postorder_recursion(root.right)
        print(root.data)

    def postorder(self, root):
        """非递归的方法实现,还不太熟悉"""
        stack_node = [root]  # 栈
        list_node = [] # 遍历结果存放列表

        while stack_node: 
            node = stack.pop()

            if node.left: # 左孩子不为空
                stack_node.append(node.left) # 左孩子压栈
            if node.right: # 右孩子不为空
                stack_node.append(node.right) # 右孩子压栈
            list_node.append(node.data)
        list_node.reverse() # 取反
        return list_node
```



  




