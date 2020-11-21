# 字符串

我觉得字符串这部分学完内置函数和正则化之后，刷leetcode更多的使用一定的算法去完成题目，如动态规划等算法。


1. str类型的通用函数及操作，如find、index、replace、切片，需要整理出来
- https://www.runoob.com/python/python-strings.html  python
- https://www.runoob.com/python3/python3-string.html  python3
2. 字符串匹配：朴素匹配算法、KMP算法（原理、代码掌握）、对比一下KMP与find函数的效率
3. python 正则化（都要尝试一遍）
- https://www.runoob.com/python/python-reg-expressions.html python
- https://www.runoob.com/python3/python3-reg-expressions.html  python3
- https://www.runoob.com/regexp/regexp-tutorial.html 正则化教程

## 字符串操作与内置函数
字符串索引是从0开始的,[]索引是左闭右开(即不会取到有索引值)
字符串切片是截取出字符串成为新的内容，不影响源字符串，同时需要注意的是字符串是不可变类型，不能只修改其中的部分字符
常用操作符：
+ 字符拼接
* 重复输出字符
[] 通过索引取得字符,左闭右开
in 如果字符串中包含给定的字符则返回True
not 如果字符串中不包含给定的字符则返回True
r/R 原始字符串,用法：r"123123\123\123"里面的字符不会被转义，常常用在路径的书写

字符串格式化：
"%d%d"%(1, 2)
"{},{}".format(a, b)
f"hello, {name}"  # name为变量，直接嵌入在字符串中

常用的字符串内置函数：(每个都需要添加一个例子)
find(str, beg=0, end=len(string))
rfind()
index(str, beg=0, end=len(string))
count(str, beg=0, end=len(string))
replace(old, new, [, max]) # max是最大替换次数
max(str)  # 字符串里最大的字母
min(str) # 字符串里最小的字母
len(str) # 获取字符长度
lstrip()
rstrip()
strip()  # 等价于lstrip().rstrip()
lower()
upper()
isalpla()
startswith() 
endswith(shffix, beg=0, end=len(string))  # 注意end与with之间还有一个字母s


## 正则表达式
import re

正则表达式修饰符（常用）：
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

内置函数
re.match(pattern, string, flags=0)
- 通过.group(0)获得整个字符 或 .group(1..)具体索引来获取第几个字符串，从1开始
re.search(pattern, string, flags=0)
re.sub(pattern, repl, string, count=0, flags=0)
re.compile()
re.findall() # 返回list
re.finditer()
re.split() # ?

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


