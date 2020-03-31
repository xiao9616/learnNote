# opencv

## 安装

**1.依赖库**

```
sudo apt-get install build-essential 
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev 
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```

**2.编译opencv**

```
make build
cd build
cmake -D -DBUILD_SHARED_LIBS=OFF -D CMAKE_INSTALL_PREFIX=/usr/local/opencv/release -DBUILD_TESTS=OFF ..
make -j8
make install
```

### 编译java版本

```
apt-get install ant
```

```
cmake -D -DBUILD_SHARED_LIBS=OFF -D CMAKE_INSTALL_PREFIX=/usr/local/opencv/release -DBUILD_TESTS=OFF ..
```

/opt/intel/openvino_2020.1.023/bin/setupvars.sh

## 使用

cmake添加

```
find_package(OpenCV 4.0 REQUIRED)
add
target_link_libraries(test  ${OpenCV_LIBS})

```

包含头文件

```
#include <opencv2/opencv.hpp>
using namespace cv;
```

## 基本数据结构

b：unsigned character
s：short integer
i：32-bit integer
f：32-bit floating-point number
d：64-bit floating-point number

### Point_

```
typedef Point_<int> Point2i;
typedef Point_<int64> Point2l;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;

typedef Point3_<int> Point3i;
typedef Point3_<float> Point3f;
typedef Point3_<double> Point3d;
```

```
Point2i p1(1, 2);
Point3f p2(1.0, 2.0, 3.0);
Vec3f p3 = (Vec3f) p2;
p1.x;
p2.z;
```

### Size_

```
typedef Size_<int> Size2i;
typedef Size_<int64> Size2l;
typedef Size_<float> Size2f;
typedef Size_<double> Size2d;
typedef Size2i Size;
```

```
Size2i s1(1, 2);
s1.height;
s1.width;
s1.area();
```

### Rect_

```
typedef Rect_<int> Rect2i;
typedef Rect_<float> Rect2f;
typedef Rect_<double> Rect2d;
typedef Rect2i Rect;
```

```
Rect2i r;
r.x;
r.y;
r.width;
r.height;
r.br();
r.tl();
r(p, s);
r(p1, p2);
```

```
两个矩形的交集	cv::Rect r3 = r1 & r2;r1 &= r2;
包含两个矩形的最小矩形	cv::Rect r3 = r1 | r2;r1 |= r2;
平移矩形	cv::Rect rx = r + p;r += p;
放缩矩形	cv::Rect rs = r + s;r += s;
判断矩形是否相等	bool eq = (r1 == r2);
判断矩形是否不相等	bool ne = (r1 != r2);
```

### Matx_

```
typedef Matx<float, 1, 2> Matx12f;
typedef Matx<double, 1, 2> Matx12d;
typedef Matx<float, 1, 3> Matx13f;
typedef Matx<double, 1, 3> Matx13d;
typedef Matx<float, 1, 4> Matx14f;
typedef Matx<double, 1, 4> Matx14d;
typedef Matx<float, 1, 6> Matx16f;
typedef Matx<double, 1, 6> Matx16d;
```

```
Matx33f m(1, 2, 3,
          4, 5, 6,
          7, 8, 9);
```

### Vec_

```
template<typename _Tp, int cn> class Vec : public Matx<_Tp, cn, 1>

typedef Vec<uchar, 2> Vec2b;
typedef Vec<short, 4> Vec4s;
typedef Vec<ushort, 4> Vec4w;
typedef Vec<int, 8> Vec8i;
typedef Vec<float, 6> Vec6f;
typedef Vec<double, 6> Vec6d;
```

```
Vec2i v(1,2);
v[1];
v(2);
```

### Scalar_

```
template<typename _Tp> class Scalar_ : public Vec<_Tp, 4>

```

```
Scalr s(1,2,3,4);
```

## Mat

| 构造函数                                                     | 说明                 |
| :----------------------------------------------------------- | -------------------- |
| Mat( int  rows,int  cols,int  type)                          | 两维矩阵             |
| Mat( int  rows,int  cols,int  type,const  Scalar& s)         | 两维矩阵(带有初始值) |
| Mat( cv::Size  sz , int  type)                               | 两维矩阵             |
| Mat( cv::Size  sz,int  type,const  Scalar& s)                | 两维矩阵(带有初始值) |
| cv::Mat(int rows, int cols, int type,
               void* data, size_t step=AUTO_STEP); | 已现有值初始化       |
| cv::Mat(cv::Size sz , int type,  void* data, size_t step=AUTO_STEP); | 已现有值初始化       |
| 拷贝构造函数                                                 | 说明                 |
| Mat(const Mat& mat)                                          |                      |
| Mat(const Mat& mat, const cv::Range& rows,const cv::Range& cols); |                      |
| Mat(const Mat& mat,const cv::Rect& roi);                     |                      |
| Mat(const Mat& mat,const cv::Range* ranges);                 |                      |
| Mat(const CvMat* old,bool copyData=false);                   |                      |
| Mat(const IplImage* old,bool copyData=false);                |                      |
| cv::Mat::zeros(rows,cols,type);                              |                      |
| cv::Mat::ones(rows,cols,type);                               |                      |
| cv::Mat::eye(rows,cols,type);                                |                      |

## 访问像素值

```
Mat m;
m.at<floar>(3,3);
m.at<Vec2f>(3,3)[0];
MatConstIterator<cv::Vec3f> it=m.begin();
(*it)[0]
```

按块访问

```
m.row(i);
m.col(j);
m.rowRange(i0,i1);
m.rowRange(cv::Range(i0,i1));
m.diag(d);
m(cv::Range(i0,i1),cv:Range(j0,j1));
m(cv::Rect(i0,i1,w,h));
m(ranges);
```

## 基本的矩阵操作

## 绘制图形文字

### cv::circle

```
void circle(
	cv::Mat& img,
	cv::Point center,
	int radius;
	const cv::Scalar& color,
	int thickness=1,
	int lineType=8,
	int shift =0
)
```

### cv::clipLine

```
bool clipLine(
	cv::Rect imagRect,	//判断线是否和矩形有交集
	cv::Point& pt1,
	cv::Point& pt2
);

bool clipLine(
	cv::Size imagSize,	//以（0，0）为初始点，判断线是否和矩形有交集
	cv::Point& pt1,
	cv::Point& pt2
);
```

### cv::ellipse

```
bool ellipse(
	cv::Mat&	img,
	cv::Point	center,
	cv::Size	axes,
	double	angle,
	double startAngle,
	double endAngle,
	const cv::Scalar& color,
	int thickness,
	int lineType,
	int shift
)

bool ellipse(
	cv::Mat& 	img,
	const cv::RotatedRect&	rect,
	const cv::Scalar&	color,
	int thickness,
	int	lineType,
	int	shift
)

void ellipse2Ploy(	//绘制椭圆多边形的采样点
	cv::Point	center，
	cv::Size	axes,
	double	angle,
	double	startAngle,
	double	endAngle,
	int	delta,
	vector<cv::Point>& pts
)
```

### cv::fillConvexPloy

```
void fillConvexPloy(
	cv::Mat& img,
	const cv::Point* pts,
	int npts,
	const cv::Scalar& color,
	int lineType,
	int shift
)

void fillPloy(
	cv::Mat& img,
	const cv::Point* pts,
	int npts,
	int ncontours,
	const cv::Scalar& color,
	int lineType,
	int shift,
	cv::Point	offset
)
```

### cv::line

```
void line(
	cv::Mat& img,
	cv::Point pt1,
	cv::Point pt2,
	const cv::Scalar& color,
	int lintType,
	int	shift
)
```

### cv::rectangle

```
void rectangle(
	cv::Mat& img,
	cv::Point pt1,
	cv::Point pt2,
	const cv::Scalar& color,
	int lineType,
	int shift
)

void rectrangle(
	cv::Mat& img,
	cv::Rect	r,
	const cv::Scalar& color,
	int	lineType,
	int	shift
)
```

### cv::polyLines

```
void polyLines(
	cv::Mat&	img,
	const cv::Point*	pts,
	int	npts,
	int ncontours,
	bool	isClosed,
	const cv::Scalr& color,
	int	lineType,
	int shift
)
```

### cv::LineIterator

```
LineIterator::LineIterator(
	cv::Mat&	img,
	cv::Point 	pt1,
	cv::Point	pt2,
	int	lineType,
	bool	leftToRight
)
```

### cv::putText

```
void cv::putText(
	cv::Mat&	img,
	const string& text,
	cv::Point	origin,
	int	fontFace,
	double	fontScale,
	cv::Scalar	color,
	int thickness,
	int lineType,
	bool	bottomLeftOrigin
)
```

### cv::getTextSize

```
cv::Size cv::getTextSize(
	const string& text,
	cv::Point	origin,
	int fontFace,
	double fontScale,
	int	thickness,
	int*	baseLine
)
```

## IO

### cv::imread

```
cv::mat cv::imread(
	const string& filename,
	int flags=cv::IMREAD_COLOR
)

flag:
IMREAD_COLOR
IMREAD_GRAYSCALE
IMREAD_ANYCOLOR
IMREAD_ANYDEPTH
IMREAD_UNCHANGE
```

### cv::imwrite

```
bool cv::imwrite(
	cosnt string& filename,
	cv::InputArray,
	const vector<int>& params
)

params:
IMWRITE-JPG-QUALITY 	0-100
IMWRITE-PNG-COMPRESSION	0-9
IMWRITE-PXM-BINARY	0 OR 1
```

### cv::VideoCapture

```
cv::VideoCapture::VideoCapture(const string& filename);
cv::VideoCapture::VideoCapture(int device);
cv::VideoCapture::VideoCapture();

cv::VideoCapture cap;
cap.isopen()
cap.open("video.avi");
Mat img;
cap.read(img);
cap>>img;
```

### cv::VideoWriter

```
cv::VideoWriter::VideoWriter(
	const string& filename,
	int fourcc,
	double fps,
	cv:Size frame_size,
	bool is_color = true
)
```

## Image Processing

