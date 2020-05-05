# JavaScript

## 基础概念

ECMAScript：ES 	js核心语法

DOM:document object model	提供一系列API，使得js可以获取或者操作HTML元素

BOM：broswer object model	提供一系列API，使得js可以操作浏览器

## 语法

### 变量类型

var：变量

function：函数

let：块域的变量

const：常量

import：

class：

```javascript
var [变量名] = 值;	//let const
function 函数名（）{
    
}
```

### 数据类型

数字:NaN	null	isNaN

字符

布尔

null

undefined

object

function

Symbol

```javascript
typeof undefined              // undefined
typeof null                   // object
null === undefined            // false类型不相等
null == undefined             // true值相等

var a=Symbol("123");
var b=Symbol("456");
a==b;	//false

var name = 'xiao'：
isNaN（name）;	//true
```

### 常用函数

```
alert（）
console.log();
```

