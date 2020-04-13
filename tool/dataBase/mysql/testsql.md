包含以下sql语句的视图不允许更新：

分组 ，distinct， group by ，having， union ，union all

truncate 不支持回滚

## 高级

### 变量

```sql
//查看所有系统变量,会话变量global改为session
show global variables;
show global variables like "%a";

//查看指定全局变量
select @@global.var1;

//设置指定变量，只对所有链接有效，重启的会话无效
set @@global.var1 = 0;

//自定义变量
set @var1=值;
set @var1：=值;
select @var1：=值;
select ...... into @var1 from ......;

//查看自定义变量
select @var1;

//局部变量 只在begin end中有效
//声明 
declare 变量名 类型;
declare 变量名 类型 default 值;
```

### 存储过程

就是可以传参数的自定义函数，适合曾删改

```mysql
//创建存储过程
create procedure 过程名（参数）
begin
	......sql语句;
end

参数包含：参数模式，参数名，参数类型
参数模式有：in，out，inout

//调用存储过程
call 过程名（实参）

//删除存储过程
drop procedure 过程名;

//查看存储过程
show create procedure 过程名;
```

### 函数

有且只有一个返回值，适合处理数据

```mysql
//创建函数
create function 函数名（参数列表）returns 返回类型
begin
	......
	return 返回值;
end

//调用
select 函数名（参数列表）

//删除
drop function 函数名;

//查看
show create function 函数名;
```

### 流程控制结构

分支结构

```
//if

//case
```

