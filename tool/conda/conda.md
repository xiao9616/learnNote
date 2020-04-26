# conda

### 1.conda环境/包管理创建

```shell
conda create --name envname python=pyversion	//创建环境
conda install --name envname packagename
conda install packagename

conda activate py37	//激活环境
conda deactivate py37		//停止环境
```

### 2.更新

2.1conda更新

```
conda update conda
```

2.2包更新

```
conda update packagename
conda update -n envname packagename
conda update --all
```

### 3.卸载

3.1卸载包

```
conda remove packagename
conda remove -n envname packagename
```

3.2卸载环境

```
conda remove -n envname --all
```

### 4.pip安装

```
pip install
pip install --upgrade 
pip freeze > requirements.txt
```

### 5.conda自身信息

5.1 版本信息

```
conda --version
```

```
conda 4.7.5
```

5.2 更多信息

```
conda info
```

```
     active environment : base
    active env location : /home/560204/anaconda3
            shell level : 1
       user config file : /home/560204/.condarc
 populated config files : /home/560204/.condarc
          conda version : 4.7.5
    conda-build version : 3.17.6
         python version : 3.7.3.final.0
       virtual packages : __cuda=10.1
       base environment : /home/560204/anaconda3  (writable)
           channel URLs : https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/linux-64
                          https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/noarch
                          https://repo.anaconda.com/pkgs/main/linux-64
                          https://repo.anaconda.com/pkgs/main/noarch
                          https://repo.anaconda.com/pkgs/r/linux-64
                          https://repo.anaconda.com/pkgs/r/noarch
          package cache : /home/560204/anaconda3/pkgs
                          /home/560204/.conda/pkgs
       envs directories : /home/560204/anaconda3/envs
                          /home/560204/.conda/envs
               platform : linux-64
             user-agent : conda/4.7.5 requests/2.21.0 CPython/3.7.3 Linux/3.10.0-862.14.4.el7.x86_64 centos/7.5.1804 glibc/2.17
                UID:GID : 1000:1000
             netrc file : None
           offline mode : False
```

5.3查看环境

```
conda info -e
```

```
base                  *  /home/560204/anaconda3
tf                       /home/560204/anaconda3/envs/tf
tfgpu                    /home/560204/anaconda3/envs/tfgpu
```

5.4查看包

```
conda list
conda list -n envname
```

5.5帮助

```
conda -h
```

### 6.导出/载入环境包

6.1导出/载入环境

```
conda env export > environment.yml
conda env create -f environment.yml

//克隆环境
conda create --name envname --clone clonename
conda create --name envname --file filename.txt
```

6.2导出/载入包

```
conda list --explicit > filename.txt
conda install --name envname --file filename.txt
```

### 7.更换源

conda源更换

```
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes
conda config --remove-key channels	//删除源
https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud
```

pip源更换

linux下：

```
修改 ～/.pip/pip.conf
添加以下内容：
[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple/ 
timeout = 10000
```

win下：

```
C:\Users\xx\pip，新建文件pip.ini
添加以下内容：
[global]
index-url=https://pypi.tuna.tsinghua.edu.cn/simple/ 
```

