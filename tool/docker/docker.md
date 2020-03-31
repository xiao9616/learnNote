[TOC]

[github地址](https://github.com/yeasy/docker_practice)

# Docker

## 常用命令

```
docker container prune	//删除所有停止的容器
docker rmi -f $(docker images -a -q)	//删除所有镜像
```

## **1.安装**

```shell
yum install docker
apt install docker.io
```

### 添加到组

```shell
sudo usermod -aG docker $USER //把当前用户添加到docker组，这样启动docker就不需要root权限了

groupadd docker	//docker组如果不存在，添加

sudo service docker start //启动

newgrp docker
重启终端
```

### 启动服务

```shell
service docker start //启动
service docker stop //停止
chkconfig docker on //设置开机启动

或者

systemctl start docker.service
systemctl enable docker.service
```

### 配置文件

启动配置文件：/etc/default/docker

### 镜像加速

```shell
vi  /etc/docker/daemon.json
#添加后
{
    "registry-mirrors": ["https://gjedjzbz.mirror.aliyuncs.com"],
    "live-restore": true,
    "insecure-registries":["172.28.4.109:1313"]
}
```

或者

```
curl -sSL https://get.daocloud.io/daotools/set_mirror.sh | sh -s http://f1361db2.m.daocloud.io
```

### 登录

登录dockerhub

```
docker login -u id -p 密码
```

登录daocloud

```
docker login daocloud.io
```

### 报错解决

1.

```
Error response from daemon: Get https://registry-1.docker.io/v2/
```

解决办法:

```
dig @114.114.114.114 registry-1.docker.io
```

找到可用ip

```
vim /etc/hosts
```

添加

```
ip registry-1.docker.io
```

2.

```
Rpmdb checksum is invalid: dCDPT(pkg checksums):
```

解决办法:

```
RUN rpm --rebuilddb && yum install -y sudo
```

## 2.镜像操作

```
docker build -t IMAGENAME .
images
rmi
tag
history
save
import
info|version
info
version
system df
```

## 3.容器操作

```shell
run
    -itd -t 选项让Docker分配一个伪终端（pseudo-tty）并绑定到容器的标准输入上， -i 则让容器的标准输入保持打			 开。
    -d 后台工作以守护态（Daemonized）形式运行
    --name	//定义容器的名字
    -p  Publish a container's port(s) to the host
  	-P  Publish all exposed ports to random ports
  	-v  Bind mount a volume
  	--volumes-from container list     Mount volumes from the specified container(s)
	start/stop/restart
	logs
	rm
	prune	//删除全部终止态容器
kill
rm
pause/unpause
create
exec
	-it bash
export
import
container prune
```

```
ps
  -a, --all             Show all containers (default shows just running)
  -f, --filter filter   Filter output based on conditions provided
      --format string   Pretty-print containers using a Go template
  -n, --last int        Show n last created containers (includes all states) (default -1)
  -l, --latest          Show the latest created container (includes all states)
      --no-trunc        Don't truncate output
  -q, --quiet           Only display numeric IDs
  -s, --size            Display total file sizes
inspect
	-f, --format string   Format the output using the given Go template
	-s, --size            Display total file sizes if the type is container
	--type string     Return JSON for specified type

top
attach
events
logs
      --details        Show extra details provided to logs
  -f, --follow         Follow log output
      --since string   Show logs since timestamp 
      --tail string    Number of lines to show from the end of the logs (default "all")
  -t, --timestamps     Show timestamps
      --until string   Show logs before a timestamp 

wait
export
port
```

### **容器**rootfs命令

```shell
commit	//通过容器构建镜像
	-a, --author string    Author (e.g., "John Hannibal Smith <hannibal@a-team.com>")
	-c, --change list      Apply Dockerfile instruction to the created image
	-m, --message string   Commit message
	-p, --pause            Pause container during commit (default true)
build
	-t, --tag list         Name and optionally a tag in the 'name:tag' format
cp
diff
```

### **镜像仓库**

```shell
login/logout
pull	//拉取镜象
push	//推送镜像
search	//查找镜像
```

```
registry 搭建自己私有仓库
1.docker pull registry
2.docker tag IMAGENAME TAGNAMW(127.0.0.1:port/imagename:version) 
3.docker push TAGNAME
4.docker pull TAGNAME
```

## 4.Docker File

建立新文件Dockerfile

```dockerfile
#注释
FROM ubuntu:16.04
MAINTAINER xiao9616 "749935253@qq.com"
RUN apt-get update
RUN apt-get install -y nginx
EXPOSE 80
```

```dockerfile
ADD #可以添加链接,可以复制压缩包自动解压
COPY #简单复制
VOLUME ["/data","/programs"]
WORKDIR
ENV
USER
ENTRYPOINT	python ##容器运行时命令,不可以被取代,只有最后一条生效,run中 --entrypoint=可以覆盖掉
CMD python ##容器运行时命令,可以被取代
ONBUILD 当有其他镜像在此基础上构建时才执行
```

## 5.Docker Compose

使用 Docker Compose 可以轻松、高效的管理容器，它是一个用于定义和运行多容器 Docker 的应用程序工具

建立文件docker-compose.yml

```shell
sudo curl -L https://github.com/docker/compose/releases/download/1.21.2/docker-compose-$(uname -s)-$(uname -m) -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose

或者

pip install docker-compose
```

```yaml
version: '2'
services:
  tensorflow:
    image: tensorflow/tensorflow:latest-py3
    container_name: tensorflow
    ports:
     - "6000:6000"
    volumes:
     - .:/code
    tty: true
  tensorboard:
    image: tensorflow/tensorflow:latest-py3
    container_name: tensorboard
    ports:
      - "6006:6006"
    volumes:
      - .:/code
    command:
      - "tensorboard"
      - "--logdir"
      - "/code/tmp/tensorflow_logs"
      - "--host"
      - "0.0.0.0"
```

#### docker-compose 命令

```
build 
	构建(重新构建)项目中的服务容器
config
	验证	Compose	文件格式是否正确
up
	根据  Compose	文件启动服务容器
stop
	将会停止up命令所启动的容器,并移除网络
exec
	进入指定容器
ps
	列出项目中目前的所有容器
rm
	删除所有(停止状态的)服务容器
```

## 6.数据管理

### 数据卷

```
创建数据卷 docker volume create VOLNAME
查看数据卷 docker volume ls
		docker volume inspect VOLNAME
挂载数据卷 docker run --mount source=VOLNAME target=/app
删除数据卷 docker volume rm VOLNAME
清理数据卷 docker volume prune
```

### 挂载目录

```
--mount	 	标记可以指定挂载一个本地主机的目录到容器中去
可以挂载目录和文件
```

## 7.网络管理

查看端口配置

```
docker port  CONTAINERNAME PORT
```

配置端口

```
docker run -d -p 5000:5000 -p 8080:8080
```

```
创建网络 docker network create -d bridge NETNAME
查看网络 docker network ls
```

链接容器

```
创建两个容器,使用同一个network
docker run -itd --name test1 --network my-net ubuntu bash
docker run -itd --name test2 --network my-net ubuntu bash
两个容器是可以ping通的

多个容器互联,推荐使用docker-compose
```

## 8.docker machine

安装

```
sudo curl -L https://github.com/docker/machine/releases/download/v0.13.0/docker-machine-`uname -s`-`uname	-m`	>	/usr/local/bin/docker-machine

sudo chmod +x /usr/local/bin/docker-machine
```

```
docker-machine -V
```

创建虚拟主机

```
docker-machine -d virtualbox NAME
```

Error with pre-create check: "VBoxManage not found. Make sure VirtualBox is installed and VBoxManage is in the path"``

```
sudo apt-get install -y virtualbox-qt
```

```
kill 停止某个Docker主机
ls 列出所有管理的Docker主机
regenerate-certs 为某个主机重新成功TLS认证信息
restart 重启Docker主机
rm 删除Docker主机
scp 在Docker主机之间复制文件
ssh SSH到主机上执行命令
start 启动一个主机
status 查看一个主机状态
stop 停止一个主机
upgrade 更新主机Docker版本为最新
url 获取主机的URL
```

## 9.docker swarm

利用docker-machine创建主机manager,worker1,worker2

```
docker-machine create -d virtual manager
docker-machine create -d virtual worker1
docker-machine create -d virtual worker2
```

查看docker-machine

```
docker-machine ls
```

进入主机(管理节点)

```
docker-machine ssh manager
```

初始化swarm

```
docker swarm init --advertise-addr IP
```

查看节点

```
docker node ls
```

进入主机(工作节点)

```
docker-machine ssh worker1
```

往管理节点添加工作节点

```
docker swarm join --token TOKEN IP
```

#### docker service管理swarm

进入docker-machine,创建服务

```
docker service create --replicas 3 -p 80:80 --name nginx nginx:1.13.7-alpine
```

查看当前集群运行的所有服务ls,查看某个服务ps,查看日志logs

```
docker service ls
docker service ps nginx
docker service logs nginx
docker service update
docker service rollbsck
```

服务伸缩与删除

```
docker service scale nginx=5

docker service rm nginx
```

#### docker stack管理多服务集群

通过docker-compose构建多个容器的服务

```
docker stack deploy -c docker-compose.yml SERVICENAME
```

其他

```
docker stack ls
docker stack service 
docker stack ps
docker stack down	//移除服务,不移除数据卷
docker stack rm	//删除
```

#### docker secret管理密钥

创建secret

```
openssl rand -base64 20 | docker secret create MYPASSWORD -
```

查看secret

```
docker secret ls
```

#### docker config管理配置文件

```
docker config create redis.conf redis.conf
```

查看config

```
docker config ls
```

#### 滚动升级

```
docker service update --image nginx:1.13 nginx
```

```
docker service rollback nginx
```

## 10.常用服务的docker化

#### mysql

```
docker pull mysql:5.5

docker run --name mysql -e MYSQL_ROOT_PASSWORD=root -v /home/mysqldata:/var/lib/mysql -p 3306:3306 -d mysql:5.5
```

#### tensorflow-gpu

notebook启动命令

```
source /etc/bash.bashrc && jupyter notebook --notebook-dir=/tf --ip 0.0.0.0 --no-browser --allow-root
```

