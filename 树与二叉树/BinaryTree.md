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
                node_p = node_p.left # 继续向左子树访问
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
#### 层次遍历（一层一层从上到下，从左到右来访问）
```python
class TreeNode:
    def __init__(self, x):
        self.data = x
        self.left = None
        self.right = None

class Solution:
    def levelorder(self, root):
        """层次遍历"""
        queue_node = [root] # 队列实现,循环链表实现？
        list_node = [] # 保存结果

        while queue_node: # 队列不为空，一直训练
            node = queue_node.pop() # 出队
            if not node: # 节点为空，从头开始，不把空节点放入结果list
                continue
            list_node.append(node.data)
            queue_node.insert(0, node.left)   # 如果使用colletions.deque模块会不会好一点？
            queue_node.insert(0, node.right)
        print(list_node)
        return list_node
```

#### 确定唯一的二叉树
1. 先序遍历结果+中序遍历结果
2. 后序遍历结果+中序遍历结果

### 二叉树遍历算法的应用
1. 二叉树的建立
- 使用先序遍历来创建二叉树，但是仅靠先序遍历来创建的二叉树不是唯一的，所以输入的序列表补充表示空节点的符号(如:#)的，将其补成一个完全二叉树的序列之后在使用先序遍历来创建二叉树

2. 复制二叉树

3. 计算二叉树的深度

4. 计算二叉树结点总数

5. 计算二叉树叶子节点数

#### 线索二叉树
- 提出问题：如何寻找特定遍历序列中二叉树结点的前驱和后继？
- 解决方法：
  1. 通过遍历寻找--费时间
  2. 再增设前驱后继指针域--增加存储负担
  3. 利用二叉链表中的空指针域（可以利用这些空指针域来增加特定遍历序列的前驱和后继），n个结点固定右n+1个空？
- 第三点的操作：
 1. 如果某个结点的左孩子为空，则将空的左孩子指针域改为其前驱；如果某个结点的右孩子为空，则将空的右孩子指针域改为其后继
 （改变指针的指针称为“线索”，即“线索二叉树”）
 2. 对二叉树按某种遍历次序使其变为线索二叉树称为“线索化”
 3. ltag和rtag来实现 左孩子还是前驱 or 右孩子还是后继 的区分
 
### 树和森林
#### 树的存储结构
1. 双亲表示法：（数据和指向双亲结点）
2. 孩子链表：（数据和指向第一个孩子的链表）
3. 孩子兄弟表示法(常用)(也称：二叉树表示法，二叉链表表示法): 指向第一个孩子结点和下一个兄弟结点

#### 树与二叉树的转换
方法：即用上面第三点来表示树与二叉树之间的对应关系
1. 树--->二叉树
  1. 操作：加线-->抹线-->旋转
  2. 口诀：兄弟相连留长子
2. 二叉树--->树
  1. 口诀：左孩右右连双亲、去掉原来右孩子线
  
#### 森林<--->二叉树
1. 树变二叉根相连
2. 去掉全部根右孩线，孤立二叉再还原


#### 树的遍历
1. 先根遍历
2. 后根遍历
3. 层次遍历

#### 森林的遍历

### 哈夫曼树（最优二叉树）

#### 基本概念
1. 路径：从树中一个节点到另一个节点之间的分支构成两节点之间的路径
2. 结点的路径长度：两节点路径上的分支树（线段数）
3. 树的路径长度：从树根到每一个结点的路径长度之和，记作：TL
  - 结点数目相同的二叉树中，完全二叉树是路径长度最短的二叉树
4. 权(weight):将树中结点赋给一个有着某种含义(视具体情况而定)的数值
5. 结点的带权路径长度：从根结点到该结点之间的路径长度与该结点的权的乘积
6. 树的带权路径长度：树中所有叶子结点的带权路径长度之和（注意是到叶子结点，而不是全部结点）
---> 哈夫曼树：最优树：带权路径长度WPL最短的树
      - 注意“带权路径长度最短”是在“度相同”的树中比较而得的结果，因此有最优二叉树、最优三叉树之称
      - 满二叉树不一定是哈夫曼树
      - 哈夫曼树中权越大的叶子离根越近
      - 具有相同带权结点的哈夫曼树不唯一（不止一个最优解）
      - 疑惑：这样能计算比较出最优树，那如何去获得最优树的形态呢？
       - 方法--->贪心算法：构造哈夫曼树时首先选择权值小的叶子结点
 
 #### 哈夫曼树的构造算法
 1 根据n个给定的权值w1,w2,w3...,wn构成n棵二叉树的森林，F={T1,T2,...Tn}，Ti
 只有一个带权为wi的根结点-->构造森林全是根
 2. 在F中选取两棵根结点的权值最小的树作为左右字数，构造一棵新的二叉树，且设置新的二叉树的根结点的权值为其左右子树上根结点的权值之和--->选用两小造新树
 3. 在F中删除这两棵树，同时将得到的二叉树加入森林中--->删除两小添新人
 4. 重复2和3，直到森林中只有一棵树为止，这棵树就是哈夫曼树
 - 哈夫曼树的结点的度数只有0或2，没有度为1的结点  
 - 包含n个叶子结点的哈夫曼树中共有2n-1个结点
 - 包含n棵树的森林要经过n-1次合并才能形成哈夫曼树，共产生n-1个新结点(是度为2的结点)
 
 #### 算法实现
 1. 顺序储存结构---一维结构数组
 2. 链表
 ```python
 class Node(object):
    def __init__(self, name=None, value=None):
        self._name = name
        self._value = value  # weight
        self._left = None
        self._right = None

class HuffmanTree(object):
    def __init__(self, char_weight):
        # 根据输入的字符及其权重生成叶子结点
        self.a = [Node(part[0], part[1] for part in char_weight)]
        while len(self.a) != 1:
            # True为降序
            self.a.sort[key=lambd node:node._value, reverse=True]
            # 选用两小造新树，删除两小添新人
            c = Node(value=(self.a[-1]._value + self.a[-2]._value))
            c._left = self.a.pop(-1) # 
            c._right = self.a.pop(-1)
            self.a.append(c)
        self.root = self.a[0]
 ```
 
#### 哈夫曼编码
1. 若将编码设计为长度不等的二进制编码，即让待传字符串中出现次数较多的字符采用尽可能短的编码，则转换的二进制字符串遍可能减少
2. 重码问题，解决关键：要设计长度不等的编码，则必须使任意字符的编码都不是另一个字符编码的前缀--前缀编码
3. 问题：什么样的前缀码能使得电文总长最短？--哈夫曼编码
   - 方法：
     1. 统计字符集中每个字符在电文中出现的平均概率（或是频率？）（概率越大，要求编码越短）
     2. 利用哈夫曼树的特点：权越大的叶子离跟越近，将每个字符的概率值作为权值，构造哈夫曼树，则概率越大的结点，路径越短
     3. 在哈夫曼树的每个分支上标0或1：结点的左分支标0，右分支标1，把从根到每个叶子的路径上的标号连接起来，作为该叶子代表的字符的编码
4. 问题
  1. 为什么哈夫曼编码能够保证是前缀编码？因为从哈夫曼树来看，路径都是唯一的，不会有哪个路径会经过两个字符
  2. 为什么哈夫曼编码能够保证字符编码总长最短？因为哈夫曼编码的带权路径长度最短，故字符编码的总长最短

5. 性质：
  1. 哈夫曼编码是前缀码
  2. 哈夫曼编码是最优前缀码
```python
class Node(object):
    def __init__(self, name=None, value=None):
        self._name = name
        self._value = value  # weight
        self._left = None
        self._right = None

class HuffmanTree(object):
    def __init__(self, char_weight):
        # 根据输入的字符及其权重生成叶子结点
        self.a = [Node(part[0], part[1]) for part in char_weight]
        while len(self.a) != 1:
            # True为降序
            self.a.sort(key=lambda node:node._value, reverse=True)
            # 选用两小造新树，删除两小添新人
            c = Node(value=(self.a[-1]._value + self.a[-2]._value))
            c._left = self.a.pop(-1) # 
            c._right = self.a.pop(-1)
            self.a.append(c)
        self.root = self.a[0]
        self.b = [i for i in range(10)] # self.b用来保存每个叶子结点的haffman编码结果
        
    # 用递归的思想生成编码
    def pre(self, tree, length):
        node = tree
        if not node:
            return # 如果树为空则直接返回
        elif node._name:  # 到达叶子结点的时候_name就不为空则为真
            out = "".join([str(self.b[i]) for i in range(length)])
            print(node._name + "的编码是：" + out)
            return 
        self.b[length] = 0  # 左子树为0
        self.pre(node._left, length+1)
        self.b[length] = 1  # 右子树为1
        self.pre(node._right, length+1)    
    
    def get_code(self):
        self.pre(self.root, 0)
        
if __name__ == "__main__":
    #输入的是字符及其频数
    char_weights=[('a',5),('b',4),('c',10),('d',8),('f',15),('g',2)]
    tree=HuffmanTree(char_weights)
    tree.get_code()
```


     
 
 
 
        
      




    
  
  





















  




