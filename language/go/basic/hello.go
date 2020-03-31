package main

import (
	"fmt"
)

func main() {
	fmt.Println("hello world")
	var b bool = true
	var a, d, c int16 = 1, 2, 3
	println(a, c, d)
	println(b)
	var e = 32
	println(e)
	f := "string"
	println(f)
	var condition int = 20
	if  condition==20 {
		println(condition)
	}else{
		println("false")
	}
	testSelect()
	x :=1
	y:=2
	println(max(x,y))
	swap(&x,&y)
	println(x)

	var c1 Circle
	c1.radius=10
	println(c1.getArea())

	km:=map[string]string{"xiao":"xiao","xuan":"xuan"}
	for k:=range km{
		println(k)
	}
	delete(km,"xiao")
	for k:=range km{
		println(k)
	}

	var phone Phone
	phone=new(Iphone)
	phone.call()

	ch :=make(chan int)
	

}

type Phone interface{
	call()
}

type Iphone struct{

}

func (iphone Iphone) call(){
	println("I am iphone")
}

func testSelect(){
	var c1 chan int
	var i1 int
	select {
	case i1=<-c1:
		println("received",i1,"from c1")
	default:
		println("no communication")
	}
}

func max(num1,num2 int) int{
	var result int
	if num1>num2{
		result=num1
	}else{
		result=num2
	}
	return result
}

func swap(a *int,b *int){
	var temp int
	temp=*a
	*a=*b
	*b=temp
}

type Circle struct{
	radius float64
}

func (c Circle) getArea() float64{
	return 3.14*c.radius*c.radius
}