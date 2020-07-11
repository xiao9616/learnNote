# cuda/cudnn

## 一.安装

### 1.下载安装[cuda](https://developer.nvidia.com/cuda-downloads)

1.1查看显卡是否支持CUDA

```
 lspci | grep -i nvidia
```

官网查看是否支持[CUDA](https://developer.nvidia.com/cuda-gpus)

1.2安装cuda

```
chmod +x filename.run
sudo ./filename.run
```

### 2.配置路径

```
sudo vi /etc/profile
export 	PATH=/usr/local/cuda-10.1/bin:$PATH
export 	LIBRARY_PATH=/usr/local/cuda-10.1/lib64:$LIBRARY_PATH
export 	LD_LIBRARY_PATH=/usr/local/cuda-10.1/lib64:$LD_LIBRARY_PATH
```

```
source /etc/profile
```

### 3.下载配置[cudnn](https://developer.nvidia.com/rdp/cudnn-download)

```
tar -xzvf cudnn-10.1-linux-x64-v7.tgz
sudo cp cuda/include/cudnn.h /usr/local/cuda/include
sudo cp cuda/lib64/libcudnn* /usr/local/cuda/lib64
sudo chmod a+r /usr/local/cuda/include/cudnn.h
```

### 4.安装gcc

查看gcc版本

```
gcc --version
```



## 二.cuda编程

#### 1.声明

在CUDA中，host和device是两个重要的概念，我们用host指代CPU及其内存，而用device指代GPU及其内存。CUDA程序中既包含host程序，又包含device程序，它们分别在CPU和GPU上运行。同时，host与device之间可以进行通信，这样它们之间可以进行数据拷贝。

GPU实际上是异构模型，所以需要区分host和device上的代码

```
__global__：在device上执行，从host中调用（一些特定的GPU也可以从device上调用），返回类型必须是void，不支持可变参数参数，不能成为类成员函数。注意用__global__定义的kernel是异步的，这意味着host不会等待kernel执行完就执行下一步。
__device__：在device上执行，单仅可以从device中调用，不可以和__global__同时用。
__host__：在host上执行，仅可以从host上调用，一般省略不写，不可以和__global__同时用，但可和device，此时函数会在device和host都编译。
__device__and__host__:可以同时使用
```

#### 2.kernel

kernel是在device上线程中并行执行的函数，kernel在device上执行时实际上是启动很多线程，一个kernel所启动的所有线程称为一个网格（grid），同一个网格上的线程共享相同的全局内存空间，grid是线程结构的第一层次，而网格又可以分为很多线程块（block），一个线程块里面包含很多线程。

grid:一个grid里每个block的线程数是一样的（1，2维）

block:block每个线程可以同步，访问共享存储（1，2，3维）

例如：N=32

每个块有16*16个线程，threadIdx([0,15],[0,15])

Grid里面有2*2个block，blockIdx([0,1],[0,1]),blockDim=16

```
__global__ void MatrixAdd(float A[][],float B[][],float C[][]){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    int j=blockIdx.y*blockDim.y+threadIdx.y;
    c[i][j]=A[i][j]+B[i][j];
}

int main(){
	dim3 threadPerBlocks(16,16);
	dim3 numBlocks(N/threadPerBlocks.x,N/threadPerBlock.y);
    MatrixAdd<<<numBlocks,threadPerBlocks>>>(A,B,C);
}
```

例如：M*M与N\*N矩阵相乘

```
__global__ void MatrixMulKernel(float* M,float* N,float* P，int Width){
    int x=threadIdx.x;
    int y=threadIdx.y;
    float Pvalue=0;
    for(int k=0;k<Width;++k){
        float Melement=M[y*M.width+k];
        float Nelement=N[k*N.width+x];
        Pvalue+=Melement*Nelement;
    }
    P[y*Width+x]=Pvalue;
}

dim3 dimBlock(WIDTH,WIDTH);
dim3 dimGrid(1,1);
MatrixMulKernel<<<dimGrid,dimBlock>>>(M,N,P);
```

问题：一个block会限制矩阵大小，会有存取的开销

改进1：

```
__global__ void MatrixMulKernel(float* M,float* N,float* P，int Width){
    int Row=blockIdx.y*blockDim.y+threadIdx.y;
    int Col=blockIdx.x*blockDim.x+threadIdx.x;
    float Pvalue=0;
    for(int k=0;k<Width;++k){
        Pvalue+=M[Row*Width+k]*N[k*Width+Col]
    }
    P[Row*Width+Col]=Pvalue;
}

dim3 dimBlock(N,N);
dim3 dimGrid(Width/N,Width/N);
MatrixMulKernel<<<dimGrid,dimBlock>>>(M,N,P);
```

改进2：

```
__global__ void MatrixMulKernel(float* M,float* N,float* P，int Width){
    __shared__ float Ms[N][N];
    __shared__ float Ns[N][N];
    int bx=blockIdx.x;
    int by=blockIdx.y;
    int tx=threadIdx.x;
    int ty=threadIdx.y;
    int Row=by*N+ty;
    int Col=bx*N+tx;
    
    float Pvalue=0;
    for(int m=0;m<width/N;++m){
        Ms[ty][tx]=M[Row*width+(m*N+tx)];
        Ns[ty][tx]=N[Col+(m*N+ty)*width];
        __syncthreads();
        for(int k=0;k<N;++k){
            Pvalue+=Ms[ty][k]*Ns[k][tx];
        }
        __syncthreads();
    }
    P[Row*width+Col]=Pvalue;
}
```

#### 3.内存

cudaMalloc分配内存

cudaFree释放内存

cudaMemcpy内存传输

```
float *Md;
int size=width*width*sizeof(float);
cudaMalloc((void)** &Md,size);
cudaFree(Md);

cudaMemCpy(Md,M,size,cudaMemcpyHostToDevice);
cudaMemCpy(Md,M,size,cudaMemcpyDeviceToHost);
```

#### 4.同步

__syncthreads()

一个线程块内的同步，只有所有线程执行到这个地方就会等待，然后所有线程一起执行__syncthreads后面的指令

## 三.在linux下开发

1.nsight

图形化开发环境.，单卡会有冲突需要两张N卡

2.nvcc



## 四.命令行

```
nsight
nvcc
cuda-gdb
lspci|grep -i nvidia
nvidia-smi
```

