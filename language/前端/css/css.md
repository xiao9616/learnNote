# CSS

## 样式继承

文字相关可以被继承,布局相关不可被继承

```html
<head>
      <style>
        div {
            width: 100px;
            height: 100px;
            background-color: #ffffff;
            font-size: 30px;
        }
    </style>
</head>
<div>
    <p>p继承了div</p>	//font-size被继承了
</div>
```

如果想要继承布局相关,可以使用inherit继承

```html
<head>
  <style>
    div{
      ...
    }
    p{
      border:inherit
    }
  </style>
</head>
```

## 优先级

1.设置相同样式的时候,后出现的优先级较高,可以理解为覆盖(不建议出现这种情况)

2.内部样式和外部样式的优先级相同,后引入的优先级较高

3.单一样式:style>id>class>标签>通配>继承

```html
<p style=" " id = " " class = " " >
  
</p>
```

单独提升优先级 !import(但是不能提升继承方式的优先级)

```css
#elem{color: red !important;} 
```

4.标签+类优先级要高于类

```css
.elem{color: red}
div.elem{color: blue}  //优先级高
```

5.群组优先级

再相同选择器的条件下,优先级相同,后出现的会覆盖前面的

```css
div{color: blue}
div,p{color: red}	//red覆盖blue
```

6.层次优先级

权重

```
style:1000 id:100 class:10 标签:1
```

## 盒子模型

conent -> padding -> border -> margin