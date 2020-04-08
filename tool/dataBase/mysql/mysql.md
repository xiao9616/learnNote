# MySql

## 客户端登陆

```mysql
mysql -h localhost -P 3306 -u root -p
```

## 基本命令

```mysql
desc tablename; //查看表结构
use databasename
show basename tablename
create table
create database
select database() version()
```

## DQL

data query language 数据查询语句

### 基础查询

```sql
select field1,field2 from tablename;
select * from tablename;

//重命名
select field1 as f1 ,field2 as f2 from tablename;
select field1 f1 ,field2 f2 from tablename;
select field1 as f1 from tablename as tn;
//去重 distinct
select distinct field from tablename;

//排除null
select ifnull(field1,0) from tablename;

//拼接( + 会转换字符型为整型,不成功则为0   如果为null则结果一定为null)
select concat(field1,field2) from tablename;

select version();
select database();
```

### 条件查询

```sql
//逻辑 and or not (连接条件)
select * from tablename where field1 > 12000 and field2 < 30;

//条件 < > <= >= != = <> <=>
select * from tablename where field1 > 12000;
select * from tablename where field1 <=> null;	// <=> 安全等于
select * from tablename where field1 <=> 12000;


//模糊 like , between and , in , is null
select * from tablename where field1 like '*a*';(用正则表达式)
select * from tablename where field1 between 100 and 200;
select * from tablename where field1 in ( 'var1','var2');	//判断所否为in内的某个值
select * from tablename where field1 is null;
select * from tablename where field1 is not null;

```

### 排序查询

```sql
select * from tablename where field ...  order by field  asc | desc ;(升序|降序)
select * from tablename where field ...  order by field1  asc , field2 desc;
```

### 常见函数

```sql
//单行函数 
//字符类
//length(字节数) , concat(拼接字符串) ， upper , lower(大小写) ， substr(截取字符) , 
//instr(返回子串第一次的索引) ， trim(去掉前后空格或指定字符) ， lpad ， rpad(往左/右填充指定字符)
//replace(替换)
select length(field1) from tablename;
select substr(field, start ,end) from tablename;
select trim('a' from field1) from tablename;
select lpad(field1 , 2 , '*') from tablenames;
select replace(field1 , 'a' , '*') from tablename;
//数学
//round(四舍五入) ， ceil(向上取整 >= ) , floor(向下取整 <= ) , truncate(截断) , mod(取余)
select round(1.567,2); //1.57
select truncate(1.6999 , 1); //1.6
select mod(-10,3); //-1  mod(a,b)=a-a/b*b 与被除数符号相同
//日期
//now(系统日期时间) ， curdata(现在日期) ， curtime(现在时间) ， year ， month , monthname ....
//str_to_date(字符转日期) , date_format(日期转字符)
select year(now());
select year('1992-08-06');
select str_to_date('1992-8-6','%Y-%m-%d');
select date_format(now() , '%年%月%日');
//其他 version ， database ， user
select database() version();
//流程控制图
//if case
select field1 if(field1 is null , 'true' , 'false') from tablename;

//分组
//sum , avg , max , min , count
select sum(field1) from tablename;
select count(*) from tablename; //统计行数
select count(1) from tablename;	//同上
```

### 分组查询

```sql
select sum(field1) , field2 from tablename group by field2;
//筛选后分组
select sum(field1) , field2 from tablename where field3 < 3 group by field2;

//having 分组后筛选
select count(*) , field1 from tablename group by field1 having count(*)>2;

//按函数分组
select count(*) , length(field1) from tablename group by length(field1);

//按多个字段分组
select avg(*) , field1 , field2 from tablename group by field1 , field2;

//分组排序
select avg(*) , field1 , field2 from tablename group by field1 , field2 order by avg(*) desc;
```

### 连接查询

```sql
//等值链接
//从多个表中取数据，需要加链接条件
select field1 , field2 from tablename1 , tablename2 where tablename1.field3 = tablename2.field4;

//非等值链接
select field1 , field2 from tablename1 t1 , tablename2 t2 where t1.field3 between t2.field4 and field5

//自连接
select t1.field1 , t2.field2 from tablename1 t1 , tablename1 t2 where t1.field3 = t2.field4;

//sql99 join on
//连接类型：inner(内连接) left(左外) right(右外) full(全外) cross(交叉)
//内链接包括等值，非等值，自连接
select field1 , field2 from tablename1 t1 inner join tablename2 t2 on t1.field3 = t2.field4;
//外联接：查询这个表，另一个表没有
select field1 , field2 from tablename1 t1 left join tablename2 t2 on t1.field3 = t2.field4;
```