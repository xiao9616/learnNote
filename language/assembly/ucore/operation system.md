# 操作系统

## 配置环境

### qemu

apt-get安装

```
sudo	apt-get	install	qemu-system
```

源码安装

```
sudo	apt-get	install	libsdl1.2-dev				#	安装库文件	libsdl1.2-dev
tar	zxvf	qemu.tar.gz
configure	--target-list="i386-softmmu"		#	配置qemu,可模拟X86-32硬件环境
make
sudo make install
```

建立符号链接文件qemu

```
sudo	ln	–s	/usr/local/bin/qemu-system-i386		/usr/local/bin/qemu
```

命令格式

```
qemu	[options]	[disk_image] 		//disk_image	即硬盘镜像文件
```

options:

```
`-hda	file' `-hdb	file'	`-hdc	file'	`-hdd	file'
使用file作为硬盘0、1、2、3镜像。

`-fda	file' `-fdb	file'
使用file作为软盘镜像,可以使用	/dev/fd0	作为file来使用主机软盘。

`-cdrom	file'
使用file作为光盘镜像,可以使用	/dev/cdrom	作为file来使用主机cd-rom。

`-boot	[a|c|d]'
从软盘(a)、光盘(c)、硬盘启动(d),默认硬盘启动。

`-snapshot'
写入临时文件而不写回磁盘镜像,可以使用	C-a	s来强制写回。

`-m	megs'
设置虚拟内存为	msg	M字节,默认为	128M字节。

`-smp	n'
设置为有n个CPU的SMP系统。以PC为目标机,最多支持255	个CPU。

`-nographic'
禁止使用图形输出。

使用	dev	设备的命令如:
    `-serial	dev'
    重定向虚拟串口到主机设备dev	中。
    `-parallel	dev'
    重定向虚拟并口到主机设备dev	中。
    `-monitor	dev'
    重定向	monitor	到主机设备dev中。
    
`-s'
等待	gdb	连接到端口1234。

`-p	port'
改变	gdb	连接端口到port。

`-S'
在启动时不启动	CPU,需要在	monitor	中输入	'c',才能让qemu继续模拟工作。

`-d'
输出日志到qemu.log文件。
```

## BIOS

