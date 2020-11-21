# 字符串

1. str类型的通用函数及操作，如find、index、replace、切片，需要整理出来
- https://www.runoob.com/python/python-strings.html  python
- https://www.runoob.com/python3/python3-string.html  python3
2. 字符串匹配：朴素匹配算法、KMP算法（原理、代码掌握）、对比一下KMP与find函数的效率
3. python 正则化（都要尝试一遍）
- https://www.runoob.com/python/python-reg-expressions.html python
- https://www.runoob.com/python3/python3-reg-expressions.html  python3
- https://www.runoob.com/regexp/regexp-tutorial.html 正则化教程


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
count(str, beg=0, end=len(string))
endwith(shffix, beg=0, end=len(string))



