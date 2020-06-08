# makefile

规则

```
target ： dependfile1 dependfile2 dependfile3 
		gcc ....
dependfile1:
		gcc .....
dependfile2:
		gcc .....
dependfile3:
		gcc .....
		
clean:
	rm *.o
```

