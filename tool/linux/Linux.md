# Linux

## 1.基础结构及目录

### 1.1基础结构

- bin (binaries) 存放二进制可执行文件
- sbin (super user binaries) 存放二进制可执行文件，只有root才能访问
- etc (etcetera) 存放系统配置文件
- usr (unix shared resources) 用于存放共享的系统资源
- home 存放用户文件的根目录
- root 超级用户目录
- dev (devices)用于存放设备文件
- lib (library)存放跟文件系统中的程序运行所需要的共享库及内核模块
- mnt (mount)系统管理员安装临时文件系统的安装点
- boot 存放用于系统引导时使用的各种文件
- tmp (temporary)用于存放各种临时文件
- var (variable)用于存放运行时需要改变数据的文件

### 1.2基础命令

#### 1.2.1文件操作

##### 系统相关

**cd** 

```
cd /path 到指定目录
```

**pwd**

```
pwd 显示当前工作目录
```

**touch**

```
touch filename.txt 创建文件
```

**mkdir**

```
mkdir dirname	创建目录
mkdir -p dirname/dirname 创建多级目录
```

**cp**

```
cp sourcefile targetdir 复制文件到目标位置
cp -r sourcefile targetdir 第归调用
```

**mv**

```
mv sourcefile targetdir 移动文件到目标位置或者重命名
```

**rm**

```
rm filename 删除文件
rm -rf 删除所有文件及文件夹
```

**rmdir**

```
rmdir dirname 删除目录
```

##### 显示相关

**echo**

```
echo 显示环境变量，字符串
```

**cat**

```
cat filename 显示文件内容
```

**more**

```
more filename 分页显示内容（空格先后，b向后）
```

**less**

```
less filename 分页显示内容（空格先后，b向后）
```

**head** **tail**

```
head filename 查看文件头10行
head -[n] filename 查看n行
```

**wc**

```
wc filename 统计行数，字数，字符数
wc -m filename 字符
wc -w filename 字数
wc -i filename 行数
```

**find**

```
find -name filename 查找指定文件
```

**grep**

```
grep aaa filename 查找指定文件指定内容
```

**ln**

```
ln file1name file2name 建立硬链接
ln -s file1name file2name 建立软链接
```

##### 解压缩

**gzip** **gunzip** 

```
gzip filename 压缩文件
gunzip filename 解压缩文件
```

**zip** **unzip**

```
zip -r filename 第归压缩
unzip filename 解压缩
window的zip包在linux下解压乱码问题：unzip -O cp936 filename.zip
```

**tar**

```
tar -zcvf filename.tar filename 压缩
tar -zxvf filename.tar filename 解压缩
```

#### 1.2.2系统

##### 基础

**top**

```
top 显示当前系统耗资源最多的进程
```

**ps**

```
ps -e 显示所有进程环境变量
ps -ef 全格式显示
ps -a 显示所有用户所有进程
ps -aux 显示无控制终端的进程
```

**kill**

```
kill -9 pid 强制杀死pid进程
```

**shutdown**

```
shutdown -h now 立即关机
shutdown -h 1 1分钟后关机
shutdown -r now 立即重启
```

**reboot**

```
reboot 重启
```

**halt**

```
halt 关机不重启
```

**su**

```
su 用户名 切换用户
```

**logout**

```
logout 注销
```

**init**

```
init 【012356】：切换运行级别
0：关机
1：单用户
2：多用户无网络
3：多用户有网络
5：图形界面
6：重启
```

##### 权限

**chmod**

```
chmod u+x filename 修改权限 u：当前用户 g：同组用户 o：其他用户
						   r：可读 w：可写 x：可执行	
chmod -R u+x filename 附带子目录
```

**chown**

```
chown user：group filename 将文件指定为组下面的user
chown -R user：group filename 附带子目录
```

##### 磁盘相关

**df**

```
df 显示磁盘空间
df -h 以可读的方式显示
```

**du**

```
du 显示指定目录的磁盘占用
```

**free**

```
free 显示内存使用
```

**mkfs**

```
mkfs -t ext4 /dev/sdb1 格式化
```

**mount**

```
mount /dev1/sdb1 挂载硬盘
```

##### 网络

**ping**

```
ping ip 测试网络联通性
```

**ifconfig**

```
ifconfig 网络配置
```

##### 时间

**data**

**cal**

##### 帮助

**man**

**help**

#### 1.2.3快捷键

```
ctrl+c 停止进程
ctrl+l 清屏
ctrl+r 搜索历史命令
ctrl+q 退出
tab 补全
```

### 其他

```
1.修改root密码
开机->引导时输入回车键->切换到单用户模式->passwd修改密码
2.查看端口占用
netstat -ntlpu
3.开启ssh服务
sudo apt-get update
sudo apt-get install openssh-server
vi /etc/ssh/sshd_config
PermitRootLogin yes
/etc/init.d/ssh start
ps aux|grep ssh
4.查看系统版本
cat /etc/issue
```

