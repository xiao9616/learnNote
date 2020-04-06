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

//去重
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

```

```

