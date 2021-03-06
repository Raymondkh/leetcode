# 图

## 回顾数据结构
1. 集合：数据元素间除“同属于一个集合外，无其他关系
2. 线性结构：1:1，如线性表、栈、队列
3. 树形结构：1：n
4. 图形结构：n:m（每个结点都可以有多个前驱多个后继，即多对多）

## 图概念
1. 图 G(V, E)--Graph(Vertex, Rdge) --V：顶点（数据元素）的 有穷非空集合；E：边的有穷集合（图不为空时至少包含一个顶点）
2. 有向图：每条边都是无方向的
3. 无向图：每条边都是有方向的
4. 完全图：任意两个点都有一条边相同
  1. 无向完全图：n个顶点共有n(n-1)/2条边
  2. 有向完全图：n个顶点共有n(n-1)条边 (为无向图的两倍)
5. 弧：有向图的边也可称为弧
6. 稀疏图：有很少的边或弧的图(e < nlogn)
7. 稠密图：有较多边或弧的图
8. 网：边或弧 带权（权重） 的图（权重表明从一个顶点到另一个顶点的距离或耗费）
    1. 图：无权重
    2. 网：有权重
9. 邻接： 有边或弧相连的两个顶点之间的关系
    1. (Vi, Vj)则称为Vi,Vj互为邻接点, （）是无向图
    2. <Vi, Vj>则称为Vi邻接到Vj, Vj邻接与Vi, <>有向图,前者指向后者
10. 关联（依附）：边或弧与顶点之间的关系
11. 顶点的度：与该顶点相关联的边的数目
    1. 有向图中，顶点的度TD(v) = 顶点的入度ID(v) + 顶点的出度OD(v)
    2. 当有向图中仅有1个顶点的入度为0，其余顶点的入度为1---->树（有向树）
12. 路径：接续的边构成的顶点序列
13. 路径长度：路径上边或弧的数目/权值之和
14. 回路(环)：第一个顶点和最后一个顶点相同的路径
15. 简单路径：除路径起点和终点可以相同之外，其余顶点均不相同的路径
    1. 简单回路(简单环)：除路径起点和终点相同之外，其余顶点均不相同的路径
16. (连通图->无向图；强连通图->有向图)：在图中，如任意两个顶点都在存在可互相达到的路径（注意有向图是要能互相达到的,路线有方向）
17. 子图：顶点和边都是包含在整图中
18. 连通分量(强连通分量)：无向图G的极大连通子图成为G的连通分量
    1. 极大连通子图：该子图是G连通子图，将G的任何不在该子图中顶点加入，子图会不再连通，说明现在是能连通的子图（顶点式不一定是能连通的最大，而是当前情况可以连通的情况）
19. 极小连通子图： 连通子图+删除一条边将不再连通
    1. 生成树： 包含无向图G所有顶点的极小连通子图
    2. 生成森林
    
### 图的数据类型
1. 抽象数据类型定义：数据对象+数据关系
2. 图的操作：
    1. GreateGraph()图的创建：生成一个没有顶点的空图G
    2. GetVex(G,v)获取顶点v的值：
    3. DFGTraverse(G):深度优先遍历
    4. BFSTraverse(G):广度优先遍历

## 图的存储结构
#### 邻接矩阵(数组表示法)--图
1.  建立一个顶点表(记录个顶点信息)和一个邻接矩阵（表示各顶点之间的关系）
2. 顶点表(一维矩阵)
3. 邻接矩阵(二维矩阵)：n*n,有边则取1，无边则取0
4. 无向图
    1. 邻接矩阵：对角线为0，对象线对称矩阵  
    2. 每一行中1的个数=该顶点的度
    3. 完全图的邻接矩阵除对角线之外全是1
5. 有向图
    1. 邻接矩阵的1为该行的顶点发出的弧（尾--->头）
    2. 第i行的含义：以结点Vi为尾的弧（即出度边）--顶点的出度=第i行元素之和
    3. 第i列的含义：以结点Vi为头的弧（即入度边）--顶点的入度=第i列元素之和
    4. 顶点的度=第i行的元素之和+第i列元素之和
#### 邻接矩阵(数组表示法)--网：即有权图
1. 邻接矩阵的值为权重值(有边) 或 无穷（表示无边，需要一个特定值来表示）--（疑问：为什么要使用无穷值来表示无边呢？是权重也可以取到负值和0吗？在书中来看，权重、对角线0值、无边无穷值 三者之间相互区分）
```
# 图的抽象数据类型的操作
ADT Graph:
  Graph(self)    # 创建一个新图
  is_empty(self) # 判断是否为一个空图
  vertex_num(self) # 获得图中的顶点个数
  edge_num(self) # 获得图中边的条数
  vertices(self) # 获得图中顶点的集合
  edges(self) # 获得边的集合
  add_vertex(self, vertex) # 将顶点vertex加入这个图中,是新增加一个顶点则为增加一个新行且每一行都需要增加一个新的元素
  add_edge(self, v1, v2) # 将从v1到v2这条边的信息加入图中
  get_edge(self, v) # 获得v1到v2边有关信息，没有的时候返回特殊值
  out_edges(self, v) # 取得从v出发的所有边
  degree(self, v) # 检查v的度
"""
以上均应该按照应用的需求来实现操作
需要考虑是无向图或有向图，对于有向图需要考虑，顶点需要分为出度或入度，邻接边需区分出边还是入边
实际使用中一般只使用出度或出边
"""
"""
遍历重要的两点关键
- 图中可能有回路，到统一顶点可能有多条路径（树中没有这种情况）。因此在遍历中需要避免再次进入已经遍历过的部分
- 图中有可能不连通，或者这个图不是有根图，即使是有根图，算法也可能没有从图中根开始遍历。
  因此，要完成对一个图里所有顶点（或边）的遍历，遍历完图中可达的那个部分（在无向图里是一个连通分量，在有向图里是一个或几个强连通分量），
  并不一定是整个图的遍历的结束，还需要考虑从初始顶点不可达的部分
"""
"""
python实现
1. 两层list or 两层 tuple
2. dict 以顶点的下标序(i, j)作为关键码，1表示有边，None表示无边，检索效率为O(1)，适合表示稀疏矩阵
3. 使用python内置的bytearray字节向量类型或标准库中array类型
   bytearray是内置类型，与str类似，但为可变类型，bytearray对象的元素是二进制字节，可以用于表示边存在与否。存储效率较高
   array是标准库中定义的数值汇集类型，起对象的元素可以是整数或浮点数等基本类型的值，可用于表示带权图
4.无穷大的值：
  inf = float("inf")  # inf值大于任何float类型的值
"""
```
```
伪代码C语言：
# define MVNUM 100 // 最大顶点数
typedef char VerTexType; // 设顶点的数据类型为字符类型
typedef int ArcType;  // 假设边的权重类型为整形

typedef struct{
  VerTexType verx[MVNUM]; // 顶点表
  ArcType arcs[MVNUM][MVNUM]; // 邻接矩阵
  int vexnum, arcnum; // 图当前的总点数和总边数
}AMGraph; 

算法思想：
1. 输入总顶点数和总边数
2. 依次输出点的信息存入顶点表中
3. 初始化邻接矩阵，是每个权重初始化为极大值
4. 构造邻接矩阵

// 无向网
Status CreateUDN(AMGrapg &G){
    cin >> G.vexnum >> G.arcnum; // 输入总顶点数，总边数
    for (i=0; i<G.vexnum; ++i)
        cin >> G.vex[i]
    for (i=0; i<G.vexnum; ++i)
        for (j=0; j<G.vexnum; ++j)
            G.arcs[i][j] = MaxInt; // 边权值均设置为极大值
    for (k=0; k<G.arcnum; ++k){
        cin >> v1 >> v2 >> w;  // 输入一条边所依附的顶点及边的权值
        i = LocateVex(G, v1); 
        j = LocateVex(G, v2); // 确定v1和v2的位置
        G.arcs[i][j] = w; // 设置<v1, v2>的权值为w
        G.arcs[j][i] = G.arcs[i][j] // 置<v1,v2>的对称边<v2, v1>的权值为w
    }
    return OK;

int LocateVex(AMGraph G, VextexType u) {
    int i;
    for (i=0; i<G.Vexnum; ++i) {
        if (u==G.vexs[i]) return i; // 找到下标则返回
    return -1; //找不到就返回-1
    }
}
   
上面代码是无向网，可以同理得出
无向图（图中的边没有权重）
  1. 初始化邻接矩阵时，w为0
  2. 构造邻接矩阵时，w为1

有向网（不需要对称赋值）
  1. 邻接矩阵时非对称矩阵
  2. 仅为G.arcsp[i][j]赋值，无需为G.arcs[j][i]赋值

}
```
```python
class AdjacencyMatrix(object):
	def __init__(self, number):
		self.number = number
		self.list = [[None] * number for i in range(number)]
		
	# insert node
	def insert(self, origin, index, weight=1):
		self.list[origin - 1][index - 1] = weight
# 测试代码
graph = AdjacencyMatrix(5)
graph.insert(1, 2)
graph.insert(1, 3)
graph.insert(1, 4)
graph.insert(2, 3)
graph.insert(3, 1)
graph.insert(3, 5)
graph.insert(4, 3)
print(graph.list)
```
#### 邻接矩阵的优缺点
1. 优点
    1. 直观简单好理解
    2. 方便检查任意一对顶点间是否存在边
    3. 方便找任一顶点的所有邻接点（有边直接相连的顶点）
    4. 方便计算任意顶点的度（无向图：对应行或列非0元素的个数；有向图：对应行非0元素的个数是出度，对应列非0元素的个数是入度）
2. 缺点
    1. 不便于增加和删除
    2. 如果边比较少的话，稀疏图，会浪费很多空间，因为空间固定为n*n
    3. 统计稀疏图中一共有多少条边会浪费时间
   

#### 邻接表(链表)--重要
1. 顶点：按编号顺序将顶点数据存储在一维数组中 (数据结构：该顶点的数据+邻接的第一个结点)
2. 第一个结点---第二个结点---空（即顶点后面跟着是与其相连的所有顶点组成的链表，这也表示边）
```
无向图
  1. 邻接表不唯一
  2. 若无向图中有n个顶点，e条边，则其邻接表需要n个头结点和2e个表结点（表示有重复）。适宜存储稀疏图
  所以在无向图中顶点vi的度为第i个单链表中的结点数
  3. 空间 n+2e
  
有向图
  两种
  1. 顶点只存储出度的边（只要就不会有重复）--查找出度方便，查找入度就需要遍历n-1个链表
  2. 顶点只存储入度的边   --查找入度方便，查找出度就需要遍历整个表
  3. 空间 n+e
  
代码实现：
class 顶点：
  data
  第一条边的指向

class 边：
  与本顶点相连的顶点的下标（边）
  权重
  指向与顶点想连得下一个顶点

class 图：
  顶点总数
  顶点总边数或总弧数
  顶点列表 = [1， 2， 3， 4 ] # 要操作某个顶点就进list[i]来进入，如果在操作顶点类的数据，比如头插顶点表示边
  
算法思想：以无向网为例
1 输入总顶点数和总边数
2. 建立顶点表
    依次输入点的信息存入顶点表中
    使每个表头结点的指针域初始化为None
3. 创建邻接表
    依次输入每条边依附的两个顶点
    确定两个顶点的序号i和j，建立边结点
    将此边结点分别出入vi和vj对应的两个边链表的头部(因为是无向表所以两个顶点要分别插入，如果是有向图则只需插入一次）

```
```python
# 实现1：https://www.cnblogs.com/gtscool/p/12584117.html
class Vertext():  # 包含顶点信息以及顶点连接边
	def __init__(self, key):
		# key是添加的顶点
		self.id =  key
		self.connectedto = {} # 初始化邻接表
		
	def addneighbor(self, nbr, weight=0):
		# 添加权重之邻接点
		self.connectedto[nbr] =   weight
		
	def getconnections(self):
		# 得到这个顶点所连接的其他所有顶点
		return self.connectedto.keys()
	
	def getid(self):
		# 返回当前顶点
		return self.id
	
	def getweight(self, nbr):
		#  返回所邻接顶点nbr的权重
		return self.connectedto[nbr]
	
class Graph():
	"""
	图-->由顶点构成，包含一个邻接表
	{
		key:Vertext(){
				self.id = key
				self.connectedto{
						邻接顶点实例:权重
						...(多个邻接顶点   )
					}
			}
		...(所有顶点s)
	}
	"""
	def __init__(self):
		self.verlist = {}    # 邻接表
		self.num = 0 # 顶点的个数
	
	def addvertext(self, key):
		# 添加顶点
		self.num += 1  #  顶点个数累加 
		newvertext = Vertext(key)  # 创建顶点
		self.verlist[key] = newvertext 
		return newvertext
	
	def getvertext(self, n):
		# 通过key来查找顶点
		if n in self.verlist:
			return self.verlist[n]
		else:
			return None
		
	def __contains__(self,  n):
		#  transition包含-->返回查询顶点是否存在于图中
		return n in self.verlist
	
	def addedge(self, f, t, cost=0):
		# 添加一条边
		if f not in self.verlist:
			# 如果没有边就创造一条边
			nv = self.addvertext(f)
		if t not in self.verlist:
			nv = self.addvertext(t)
			
		if cost == 0:
			# cost == 0 代表是没有传入参数，而使用默认参数0，即是无向图
			self.verlist[f].addneighbor(self.vetlist[t], cost) # cost是权重
			self.verlist[t].addneighbor(self.verlist[f], cost)
		else:
			self.verlist[f].addneighbor(self.verlist[t],cost) # 有向图权重
			
	def getvertices(self):
		# 返回图中所有顶点
		return self.verlist.keys()
	
g = Graph()
g.addedge(0,5,2)
g.addedge(1,2,4)
g.addedge(2,3,9)
g.addedge(3,4,7)
g.addedge(3,5,3)
g.addedge(4,0,1)
g.addedge(5,4,8)
g.addedge(5,2,1)

print(g.getvertices())
print(g.verlist)
print(type(g.verlist))
for k, v in g.verlist.items():
	for w in v.getconnections(): # 获得类实例的connectedTO
        # print(w)
		print("({},{}:{})".format(v.getid(), w.getid(), v.getweight(w)))

# 实现2:https://www.jianshu.com/p/ce4109962031
class Node(object):
	def __init__(self, index, weight, next=None):
		self.index = index
		self.weight = weight
		self.next = next
		
class AdjacencyList(object):
	def __init__(self, number):
		self.number = number
		self.list = [None] * number
		
	def insert(self, origin, index, weight=1):
		node = Node(index, weight, self.list[origin-1])
		self.list[origin-1] = node
		
graph = AdjacencyList(5)
graph.insert(1, 2)
graph.insert(1, 3)
graph.insert(1, 4)
graph.insert(2, 3)
graph.insert(3, 1)
graph.insert(3, 5)
graph.insert(4, 3)
for i in range(graph.number):
	print('node', (i + 1), 'links:', end = ' ')
	node = graph.list[i]
	while node:
		print(node.index, end = ' ')
		node = node.next
		print()
```
#### 邻接表的优缺点
1. 优点：
    1. 方便找任意顶点的所有邻接点
    2. 节约稀疏图的空间
    3. 对于无向图来说方便计算任一顶点的度；对有向图只有“出度”，所以可以构造一个“逆邻接表”来存储入度边
2. 缺点：
  1. 不方便检查任一对顶点间是否存在边（是对于有向图吧？）

#### 邻接矩阵和邻接表的区别
1. 联系：邻接表中每一个链表对应的邻接矩阵中的一行，链表中结点的个数等于一行中非零元素的个数
2. 区别：邻接矩阵是唯一的，但邻接表不唯一（链接次序与顶点的编号无关，与具体如何插入有关）
3. 区别：邻接矩阵的空间复杂度为O(n^2), 而邻接表为O(n+e)
4. 用途：邻接矩阵多用于稠密图，邻接表多用于稀疏图，自行根据实际情况来选择

#### 十字链表(orthogonal list)：解决邻接表查找有向图的度的困难
1. 可看做是有向图的邻接表和逆邻接表结合
2. 表头结点:data + firstin(入度边) + firstout(出度边)
3. 弧节点：tailvex弧尾位置+headvex弧头位置+hlink弧头相同的下一条弧+tlink弧尾相同的下一条弧


#### 邻接多重表(链表)：解决邻接表的无向图每条边都要存储两遍
1. 如何代码实现，视频听得有点懵？代码如何实现能顺着去添加每个结点的链接的？
2. 顶点结点：data+firstedge; 边结点：mark+ivex+ilink+jvex+jlink+info(mark标志域标记此边是否被搜索过，ivex该边依附的两个节点在表头数组中的位置，ilink指向依附于ivex的下一条边，jvex该边依附的两个节点在表头数组中的位置，jvex指向依附于jvex的下一条边)
3. 

#### 邻接多重表、十字链表
1. 发现这两种结构最后都只需要与顶点和边的数量一致，也就是最少的情况，当然另外还需要额外的空间存储链接

#### 深度优先遍历
- [过程理解](https://blog.csdn.net/weixin_40953222/article/details/80544928?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control)
- 概念：
- 代码实现（多种情况）：
1. 邻接表
2. 邻接矩阵
3. 无向图和有向图（两者的代码有什么区别吗？）
4. 二叉树
6. 树
#### 广度优先遍历
- 概念：
- 代码实现（多种情况）：
1. 邻接表
2. 邻接矩阵
3. 无向图和有向图（两者的代码有什么区别吗？）
4. 二叉树
6. 树

### 图的应用
#### 最小生成树·

    
    
    
    
    
    

