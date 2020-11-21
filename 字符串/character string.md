# 字符串

我觉得字符串这部分学完内置函数和正则化之后，刷leetcode更多的使用一定的算法去完成题目，如动态规划等算法。


1. str类型的通用函数及操作，如find、index、replace、切片，需要整理出来 [菜鸟教程-字符串](https://www.runoob.com/python3/python3-string.html)
2. 字符串匹配：朴素匹配算法、KMP算法（原理、代码掌握）、对比一下KMP与find函数的效率
3. python [正则表达式](https://www.runoob.com/regexp/regexp-tutorial.html)

### 字符串操作与内置函数
- 字符串索引是从0开始的,[]索引是左闭右开(即取到右索引值的前一位, i-1)
- 字符串切片是截取出字符串成为新的内容，不影响源字符串，同时需要注意的是字符串是不可变类型，不能只修改其中的部分字符
- 字符拼接  str+str
- 重复输出字符 str*n = str+str+..+str 共n个str拼接
- in 如果字符串中包含给定的字符则返回True
- not 如果字符串中不包含给定的字符则返回True
- r/R 原始字符串,用法：r"123123\123\123"里面的字符不会被转义，常常用在路径的书写

### 常用转义字符
- 续行符 在行尾加\
- 单引号\' 双引号\"
- 响铃 \a
- 换行 \n  回车\r
- 横向制表符\t 纵向制表符\v


### 字符串格式化：
- "%d%d"%(1, 2)    
- 常用格式化符号：%c 格式化字符及其ASCLL码??; %s 格式化字符串; %d 格式化整数; %f 浮点数，可指定小数点后的精度
- "{},{}".format(a, b)
- f"hello, {name}"  # name为变量，直接嵌入在字符串中(python3.6之后)
- """ """三引号可以多行字符串输入

### 知识点
- 在python3中所有字符串都是Unicode字符串
- 在python2中普通字符是以8位ASCLL码来存储，而Unicode字符串则存储为16位unicode字符串，这样能表示更多的字符集，使用的语法是在字符串前面加上前缀u

### 常用的字符串内置函数：(每个都需要添加一个例子)
- str.find(str, beg=0, end=len(string))  和  rfind()从右边开始查找 
```python
str1 = "Runoob example....wow!!!"
str2 = "exam";
 
print (str1.find(str2))      # 输出: 7  成功找到则返回开头的索引
print (str1.find(str2, 5))   # 输出: 7  
print (str1.find(str2, 10))  # 输出: -1  从10开始寻找已经找不到了，所以返回-1
```
- str.index(str, beg=0, end=len(string))  # 也是子字符串，与find的区别就是找不到会报错  和 rindex()
```python
str1 = "Runoob example....wow!!!"
str2 = "exam";

print (str1.index(str2))      # 输出: 7  找到则返回索引
print (str1.index(str2, 5))   # 输出: 7
print (str1.index(str2, 10))  # ValueError:substring not found 找不到就会报错
```
- str.count(sub, start=0, end=len(string)) # 在str中统计sub子字符串的数量,start和end为统计区间
```python
str="www.runoob.com"
sub='o'
print ("str.count('o') : ", str.count(sub))  # 输出: str.count('o') :  3
sub='run'    # 子字符串可以是单个字符也可以是多个字符
print ("str.count('run', 0, 10) : ", str.count(sub,0,10)) # 输出: str.count('run', 0, 10) :  1
# 总结：count必须有输入一个子字符串作为目标来统计数量

import collections 
c = collections.Counter(str)
print(c)  # 输出: Counter({'w': 3, 'o': 3, '.': 2, 'r': 1, 'u': 1, 'n': 1, 'b': 1, 'c': 1, 'm': 1})
print(c['w']) # 输出: 3 能一次统计所有单个字符的数量
```
- str.split(str, num=string.count(str)) # 通过指定分隔符str来分割字符串存放在list中
```python
str = "this is string example....wow!!!"
print (str.split( ))       # 以空格为分隔符
print (str.split('i',1))   # 以 i 为分隔符
print (str.split('w'))     # 以 w 为分隔符
#输出：
#['this', 'is', 'string', 'example....wow!!!']
#['th', 's is string example....wow!!!']
#['this is string example....', 'o', '!!!']
```
- replace(old, new, [, max]) # max是最大替换次数
- "".join(seq)  # 将前面的字符串插入到seq元素之间形成新的字符串
- max(str)  # 字符串里最大的字母
- min(str) # 字符串里最小的字母
- len(str) # 获取字符长度
- lstrip() 和 rstrip() 和 strip() 截取左右两边的空格或指定字符
- islower()判断是不是小写 和 lower() 转换为小写
- isupper()判断是不是大写 和 upper() 转换为大写
- isalpla()  # 只有有一个字符且所有字符都是字母或中文字则True,如果有.#等其他字符则False
- isdigit()  # 如果只包含数字则True，负责False
- startswith(substr, beg=0, end=len(string)) 
- endswith(shffix, beg=0, end=len(string))  # 注意end与with之间还有一个字母s # 检测是否包含指定后缀


### [正则表达式](https://www.runoob.com/regexp/regexp-tutorial.html)
import re

#### 正则表达式修饰符（常用）：
re.I??
re.M
re.S

^   # 开头
$   # 末尾
.   # 任意字符，除换行符外
[...] # 一组字符，如[abc]为'a','b','c'
[^...] # 除[]里的字母外
re* # 0或多个
re+ # 1或多个
re? # 
a|b # a或b
[0-9] # 所有数字
[a-zA-Z] # 所有字母

#### 内置函数
- re.match(pattern, string, flags=0) # 从字符串起始位置匹配pttern，成功则返回匹配对象，不成功则返回None
- 返回的匹配对象使用group(num) 或 grous()
```python

```
- re.search(pattern, string, flags=0)
- re.sub(pattern, repl, string, count=0, flags=0)
- re.compile()
- re.findall() # 返回list
- re.finditer()
- re.split() # ?

## leetcode
#### easy
```python
# leetcode-13
dict = {}  # 里面要补题目写的罗马数字
sum = dict[s[0]]
n = 1
while n < l:
  if dict[s[n]] > dict[s[n-1]]:
    sum -= dict[s[n-1]]
    sum += (dict[s[n]] - dict[s[n-1]])
  else:
    sum += dict[s[n]]
 
# leetcode-14
s1 = string[0]
out = [s for s in s1]
for s in string[1:]:
  n = 0
  while n < len(out):
    if s[n] == out[n]:
      n += 1
    else:
      out = out[:n]
return "".join(out)

# leetcode-38

# leetcode-28
return haystack.find(needle)

# leetcode-3,再看看题解其实思路是一样的，但是题解的写法比较高级一点吧
maxlist = []
tmp = []
for c in s:
  if c in tmp:
    if len(tmp) > len(maxlist):
      maxlist = tmp[:]
    id = tmp.index(c)
    tmp  =tmp[id+1:]
  else:
    tmp.append(c)
if len(tmp) > len(mxalist):
  maxlist = tmp[:]
return len(mxalist)

leetcode-125-已通过使用了内置函数去处理字符串，还是挺简洁的
class Solution(object):
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        # 将s中所有非数字和字符的符号去掉，链接起来再全部去小写
        # 去中值一直对比是否相等，一直相同则是回文串，否则不是
        import re
        s = "".join(re.split('[^0-9a-zA-Z]', s)).lower()
        n = len(s)
        # print(s)
        if n % 2 == 0:
            # 偶数
            n1 = n / 2
        else:
            n1 = n // 2 + 1
        for i in range(n1):
            # print(s[i], s[-i-1])
            if s[i] != s[-i-1]:
                return False
        return True
```

### mid
```python

# leetcode-5 看题解
```
