# shell

# 执行shell的三种方法：

1	./xxx.sh	#chmod +x ./xxx.sh

2	sh xxx.sh

3	source xxx.sh

# 接收用户参数

$0	shell脚本程序名

$1-9 $10 $11等	对应位置的参数

$#	总共的参数

$*	所有参数列表

$?	判断上一条命令是否成功，0成功，非0失败

# 测试语句

1文件测试[   操作符  路径  ]

-d	是否为目录

-e	是否存在

-f	是否是文件

-r	读权限

-w	写权限

-x	执行权限

2逻辑测试[   表达式   ]   操作符   [  表达式  ]

&&

||

!

3数值比较[   数值1  操作符  数值2  ]

-eq		等于

-ne		不等于

-gt		大于

-lt		小于

-ge		大于等于

-le		小于等于

4字符串比较[  字符串1  操作符  字符串2  ]

=	等于

!=	不等于

-z	是否为空

# if语句

if 	条件1；then

​	执行1

elif	条件2；then

​	执行2

else 执行3

fi

```shell
if [ grade -ge 85 ] && [ grade -le 100 ];then
 echo " "
elif [ grade -ge 70 ] && [ grade -le 84 ];then
 echo " "
else echo " "
fi
```

# for语句

for 变量 in 列表

do

​	执行1

done

```
for skill in ada coffe action java
do
	echo "${skill}"
done
```

# while语句

while 条件1

do

​	执行1

done

# case语句

case 变量 in

模式1）

​	执行1

模式2）

​	执行2

seac

# 数组

```
array=（value1  value2  value3）

array[0]  array[1]
${array[0]}
${array[*]}	${array[@]}//所有元素
${#array[*]}	//数组长度
```

