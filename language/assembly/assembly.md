# 汇编语言asm

## 寄存器

![img](http://www.ruanyifeng.com/blogimg/asset/2018/bg2018012206.png)

CPU 优先读写寄存器，再由寄存器跟内存交换数据。寄存器不依靠地址区分数据，而依靠名称。每一个寄存器都有自己的名称，我们告诉 CPU 去具体的哪一个寄存器拿数据，这样的速度是最快的。

早期的 x86 CPU 只有8个寄存器，而且每个都有不同的用途。现在的寄存器已经有100多个了，都变成通用寄存器，不特别指定用途.

![寄存器结构](http://www.cs.virginia.edu/~evans/cs216/guides/x86-registers.png)

### 通用寄存器

X86处理器中有8个32位的通用寄存器。由于历史的原因，

EAX:累加器,通常用于计算

EBX:基址寄存器

ECX:计数器,通常用于循环变量计数

EDX:数据寄存器

ESI:源地址指针寄存器

EDI:目的地址指针寄存器

ESP:指示栈指针(用于指示栈顶位置)

EBP:基址指针（用于指示子程序或函数调用的基址指针）

EAX、EBX、ECX和EDX的前两个高位字节和后两个低位字节可以独立使用，其中两位低字节又被独立分为H和L部分，这样做的原因主要是考虑兼容16位的程序

应用寄存器时，其名称大小写是不敏感的，如EAX和eax没有区别。

### 段寄存器

CS:代码段

DS:数据段

ES:附加数据段

SS:堆栈段

FS:附加段

GS:附加段

### 指令寄存器

EIP:存储下一条执行的指令

### 标志寄存器

EFLAGS

## 内存模型

程序运行的时候，操作系统会给它分配一段内存，用来储存程序和运行产生的数据。这段内存有起始地址和结束地址，比如从0x1000到0x8000，起始地址是较小的那个地址，结束地址是较大的那个地址。

### 堆Heap

程序运行过程中，对于动态的内存占用请求（比如新建对象，或者使用`malloc`命令），系统就会从预先分配好的那段内存之中，划出一部分给用户,具体规则是从起始地址开始划分（实际上，起始地址会有一段静态数据).

用户主动请求而划分出来的内存区域，叫做 Heap（堆）。它由起始地址开始，从低位（地址）向高位（地址）增长。Heap 的一个重要特点就是不会自动消失，必须手动释放，或者由垃圾回收机制来回收。

![img](http://www.ruanyifeng.com/blogimg/asset/2018/bg2018012209.png)

### 栈stack

除了 Heap 以外，其他的内存占用叫做 Stack（栈）。简单说，Stack 是由于函数运行而临时占用的内存区域。Stack 是由内存区域的结束地址开始，从高位（地址）向低位（地址）分配。

![img](http://www.ruanyifeng.com/blogimg/asset/2018/bg2018012210.png)

```
int main() {
   int a = 2;
   int b = 3;
   return add_a_and_b(a, b);
}
```

`main`函数内部调用了`add_a_and_b`函数。执行到这一行的时候，系统也会为`add_a_and_b`新建一个帧，用来储存它的内部变量。也就是说，此时同时存在两个帧：`main`和`add_a_and_b`。一般来说，调用栈有多少层，就有多少帧。

![img](http://www.ruanyifeng.com/blogimg/asset/2018/bg2018012212.png)

### 静态数据区

X86汇编语言中用汇编指令.DATA声明静态数据区（类似于全局变量），数据以单字节、双字节、或双字（4字节）的方式存放，分别用DB,DW, DD指令表示声明内存的长度,相邻定义的标签在内存中是连续存放的.

```
.DATA
	DB 64;声明一个字节，并将数值64放入此字节中
	DB ?;声明一个未初始化的字节.
	DW ?;声明一个双字节，未初始化.
	DD 30000;声明一个4字节，其值为30000.
```

声明数组时使用DUP关键字

```
.DATA
	DB 10 DUP(?);声明10未初始化个字节
```

### 寻址模式

```
mov eax, [ebx]	; 将ebx值指示的内存地址中的4个字节传送到eax中
mov [var], ebx	; 将ebx的内容传送到var的值指示的内存地址中.
mov eax, [esi-4]	; 将esi-4值指示的内存地址中的4个字节传送到eax中
mov [esi+eax], cl	; 将cl的值传送到esi+eax的值指示的内存地址中
mov edx, [esi+4*ebx]   ; 将esi+4*ebx值指示的内存中的4个字节传送到edx
```

声明内存大小时，在汇编语言中，一般用DB，DW，DD均可声明的内存空间大小，这种现实声明能够很好地指导汇编器分配内存空间.

## 指令

约定:

```
<reg32> 32位寄存器 (EAX, EBX, ECX, EDX, ESI, EDI, ESP, or EBP)
<reg16>	16位寄存器 (AX, BX, CX, or DX)
<reg8>	8位寄存器(AH, BH, CH, DH, AL, BL, CL, or DL)
<reg>	任何寄存器
 	 
<mem>	内存地址 (e.g., [eax], [var + 4], or dword ptr [eax+ebx])

<con32>	32为常数
<con16>	16位常数
<con8>	8位常数
<con>	任何8位、16位或32位常数
```

#### 例子

```
example.c

#include <stdio.h>
int add_a_and_b(int a, int b) {
   return a + b;
}

int main() {
   return add_a_and_b(2, 3);
}
```

通过gcc编译成汇编代码

```
gcc -S example.c
```

```
	.file	"example.c"
	.text
	.globl	add_a_and_b
	.type	add_a_and_b, @function
add_a_and_b:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add_a_and_b, .-add_a_and_b
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$3, %esi
	movl	$2, %edi
	call	add_a_and_b
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
```

#### push

push指令用于将运算子放入 Stack,ESP只是栈顶。在压栈前，首先将ESP值减4（X86栈增长方向与内存地址编号增长方向相反），然后将操作数内容压入ESP指示的位置。

```
push <reg32>
push <mem>
push <con32>
```

#### pop

`pop`指令用于取出 Stack 最近一个写入的值（即最低位地址的值），并将这个值写入运算子指定的位置。它首先将ESP指示的地址中的内容出栈，然后将ESP值加4.

```
pop <reg32>
pop <mem>
```

#### lea

是一个载入有效地址指令，将第二个操作数表示的地址载入到第一个操作数（寄存器）中。

```
lea <reg32>,<mem>
```

#### call

call指令用来调用函数。

#### mov

`mov`指令用于将一个值写入某个寄存器.mov不能用于直接从内存复制到内存

```
mov    %eax, [%esp+8]
```

先将 ESP 寄存器里面的地址加上8个字节，得到一个新的地址，然后按照这个地址在 Stack 取出数据,再写入 EAX 寄存器。

```
mov <reg>,<reg>
mov <reg>,<mem>
mov <mem>,<reg>
mov <reg>,<const>
mov <mem>,<const>
```

#### add

add指令用于将两个运算子相加，并将结果写入第一个运算子.

```
add <reg>,<reg>
add <reg>,<mem>
add <mem>,<reg>
add <reg>,<con>
add <mem>,<con>
```

#### sub

sub指令指示第一个操作数减去第二个操作数，并将相减后的值保存在第一个操作数

```
sub <reg>,<reg>
sub <reg>,<mem>
sub <mem>,<reg>
sub <reg>,<con>
sub <mem>,<con>
```

#### inc/dec

inc,dec分别表示将操作数自加1，自减1

```
inc <reg>
inc <mem>
dec <reg>
dec <mem>
```

#### imul

整数相乘指令，它有两种指令格式，一种为两个操作数，将两个操作数的值相乘，并将结果保存在第一个操作数中，第一个操作数必须为寄存器；第二种格式为三个操作数，其语义为：将第二个和第三个操作数相乘，并将结果保存在第一个操作数中，第一个操作数必须为寄存器。

```
imul <reg32>,<reg32>
imul <reg32>,<mem>
imul <reg32>,<reg32>,<con>
imul <reg32>,<mem>,<con>
```

#### idiv

idiv指令完成整数除法操作，idiv只有一个操作数，此操作数为除数，而被除数则为EDX:EAX中的内容（一个64位的整数），操作的结果有两部分：商和余数，其中商放在eax寄存器中，而余数则放在edx寄存器中。

```
idiv <reg32>
idiv <mem>
```

#### and/or/xor

逻辑与、逻辑或、逻辑异或操作指令，用于操作数的位操作，操作结果放在第一个操作数中。

```
and <reg>,<reg>
and <reg>,<mem>
and <mem>,<reg>
and <reg>,<con>
and <mem>,<con>

or <reg>,<reg>
or <reg>,<mem>
or <mem>,<reg>
or <reg>,<con>
or <mem>,<con>

xor <reg>,<reg>
xor <reg>,<mem>
xor <mem>,<reg>
xor <reg>,<con>
xor <mem>,<con>
```

#### not

位翻转指令，将操作数中的每一位翻转

```
not <reg>
not <mem>
```

#### neg

取负指令。

```
neg <reg>
neg <mem>
```

#### shl/shr

位移指令，有两个操作数，第一个操作数表示被操作数，第二个操作数指示位移的数量。

```
shl <reg>,<con8>
shl <mem>,<con8>
shl <reg>,<cl>
shl <mem>,<cl>

shr <reg>,<con8>
shr <mem>,<con8>
shr <reg>,<cl>
shr <mem>,<cl>
```



X86处理器维持着一个指示当前执行指令的指令指针（IP），当一条指令执行后，此指针自动指向下一条指令。IP寄存器不能直接操作，但是可以用控制流指令更新。

#### jmp

控制转移到label所指示的地址，（从label中取出执行执行）

```
jmp <label>
```

#### jcondition

条件转移指令依据机器状态字中的一些列条件状态转移。机器状态字中包括指示最后一个算数运算结果是否为0，运算结果是否为负数等.

```
je <label> (jump when equal)
jne <label> (jump when not equal)
jz <label> (jump when last result was zero)
jg <label> (jump when greater than)
jge <label> (jump when greater than or equal to)
jl <label> (jump when less than)
jle <label>(jump when less than or equal to)
```

#### cmp

cmp指令比较两个操作数的值，并根据比较结果设置机器状态字中的条件码。此指令与sub指令类似，但是cmp不用将计算结果保存在操作数中。

```
cmp <reg>,<reg>
cmp <reg>,<mem>
cmp <mem>,<reg>
cmp <reg>,<con>
```

#### ret

ret指令用于终止当前函数的执行，将运行权交还给上层函数。也就是，当前函数的帧将被回收。

#### assume

```
assume cs:code //cs 代码段 ds数据段
```

code 表示用一个标志定义段,如下就是一个段

```
code segment

code ends
```

实现2的三次方

```
assume cs:abc

abc segment
	mov ax,2
	add ax,ax
	add ax,ax
	mov ax,4c00H
	int 21H
abc ends

end
```

#### ends

伪指令,段结束

#### end

伪指令,程序结束

#### idata

#### ( )

描述符号,表示内容

```
(ax)=0010H //ax寄存器的内容为0010H
```

#### [ ]

数据偏移

```
mov ax,[0]	//将ds:0处的数据移动到ax
```

## 格式

### AT&T与intel区别

```
*	寄存器命名原则
AT&T:	%eax																	Intel:	eax
*	源/目的操作数顺序	
AT&T:	movl	%eax,	%ebx											
Intel:	mov	ebx,	eax
*	常数/立即数的格式 
AT&T:	movl	$_value,	%ebx								
Intel:	mov	eax,	_value
把value的地址放入eax寄存器
AT&T:	movl	$0xd00d,	%ebx								
Intel:	mov	ebx,	0xd00d
*	操作数长度标识	
AT&T:	movw	%ax,	%bx													Intel:	mov	bx,	ax
*	寻址方式	
AT&T:	immed32(basepointer,	indexpointer,	indexscale)
Intel:	[basepointer	+	indexpointer	×	indexscale	+	imm32)

*	直接寻址	
AT&T:	foo																	Intel:	[foo]
boo是一个全局变量。注意加上$是表示地址引用,不加是表示值引用。对于局部变量,可以通过堆栈
指针引用。
*	寄存器间接寻址	
AT&T:	(%eax)																	Intel:	[eax]
*	变址寻址	
AT&T:	_variable(%eax)															Intel:	[eax	+	_variable]

AT&T:	_array(	,%eax,	4)													Intel:	[eax	×	4	+	_array]

AT&T:	_array(%ebx,	%eax,8)										
Intel:	[ebx	+	eax	×	8	+	_array]
```

### GCC内联汇编

#### 基本内联汇编

```
asm("statements");
```

"asm"	和	"__asm__"	的含义是完全一样的。如果有多行汇编,则每一行都要加上	"\n\t"。其中
的	“\n”	是换行符,"\t”	是	tab	符,在每条命令的	结束加这两个符号,是为了让	gcc	把内联汇编
代码翻译成一般的汇编代码时能够保证换行和留有一定的空格。对于基本asm语句,GCC编
译出来的汇编代码就是双引号里的内容。

```
asm(	
    "pushl	%eax\n\t"
    "movl	$0,%eax\n\t"
    "popl	%eax"
);
```

#### 扩展内联汇编

```
asm	[volatile]	(	Assembler	Template
			:	Output	Operands
			[	:	Input	Operands
			[	:	Clobbers	]	])
```

例子:

```
#define	read_cr0()	({	\
unsigned int __dummy;	\
__asm__(	\
				"movl	%%cr0,%0\n\t"	\
				:"=r"	(__dummy));	\
__dummy;	\
})
```

__asm__	表示汇编代码的开始,其后可以跟	__volatile__(这是可选项),其含义是
避免	“asm”	指令被删除、移动或组合,在执行代码时,如果不希望汇编语句被	gcc	优化而改
变位置,就需要在	asm	符号后添加	volatile	关键词:asm	volatile(...);或者更详细地说明为:
__asm__	__volatile__(...);

“=r”表示相应的目标操作数(指令部分的%0)可以使用任何一个通用寄存器,并且变量__dummy存放在这个寄存器中

“=m”就表示相应的目标操作数是存放在内存单元__dummy中。表示约束条件的字母很多,下
表给出几个主要的约束字母及其含义:

```
字母 含义
m,	v,	o 内存单元
R 任何通用寄存器
Q 寄存器eax,	ebx,	ecx,edx之一
I,	h 直接操作数
E,	F 浮点数
G 任意
a,	b,	c,	d 寄存器eax/ax/al,	ebx/bx/bl,	ecx/cx/cl或edx/dx/dl
S,	D 寄存器esi或edi
I 常数(0~31)
```

