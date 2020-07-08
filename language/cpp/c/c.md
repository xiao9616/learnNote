# C

## 动态内存

### malloc free

stdlib.h

void *malloc(unsigned int size)

在堆中分配一块size字节的连续区域，返回的通用指针（起始地址）必须强制转换，返回NULL表示不成功，分配的内容不确定，一般需要memset初始化。

```c
int *array,n;
array=(int *)malloc(n*sizeof(int));
memset(array,0,n*sizeof(int));
for(int i;i<n;++i){
    array[i] = i;
}
free(array);
```

### calloc

stdlib.h

void *calloc(size_t nmemb , size_t size)

申请nmemb个块，每块大小为size个字节，分配内容默认为0 。

### relloc

stdlib.h

void *relloc(void *s , unsigned int newsize)

针对malloc，calloc分配的内存，想在原基础上重新申请内存，大小为newsize，就可以使用relloc。如果原内存后面有足够大的空间，就追加。如果不够则找一个新的newsize大小的内存，将原先内存的内容拷贝过来，返回新地址。如果newsize比原先内存小，则会释放原先内存后面的空间，只保留前面的newsize大小。

### free

内存泄漏

如果动态分配的内存首地址丢了，无法使用该内存也无法释放该内存区域，就称为内存泄漏。

```c
char *p;
p=(char*)malloc(100);
p="hello";	//内存泄漏
```

### memset

string.h

void *memset(void *s,int c,size_t n)

将参数s所指的内存区域的前n个字节，以参数c填充，返回指向s的指针。

## 结构体

### 内存分配-对齐机制

```c
struct stu{
	char sex;
	int age;
}student;

sizeof(student);	// 8字节
```

结构体分配内存的时候，会去结构体中找基本数据类型的成员，哪个基本数据类型占字节数多，就以它的大小为单位开辟。存储的顺序是按照结构体定义顺序来的。

### 指定对齐规则

#pragma pack（value）value可以是1 2 4 8

指定对齐值与数据类型对齐值相比取较小的值

### 位段

```
struct stu{
	char sex：4;
	int age;
}student;
```

## 共用体

几个不同的变量占用同一段内存地址，共用体的大小是占内存长度最大的成员的大小

```c
union stu{
	char sex;
	int age;
}student; 

sizeof(student);	// 4字节
```





