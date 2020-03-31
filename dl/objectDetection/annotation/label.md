# 目标检测标注

## 一.标注工具

1.[labelimg](https://github.com/tzutalin/labelImg)

以PASCAL VOC格式生成的XML文件

```
<annotation verified="yes">
	<folder>images</folder>
	<filename>raccoon-1.jpg</filename>
	<path>/Users/datitran/Desktop/raccoon/images/raccoon-1.jpg</path>
	<source>
		<database>Unknown</database>
	</source>
	<size>
		<width>650</width>
		<height>417</height>
		<depth>3</depth>
	</size>
	<segmented>0</segmented>
	<object>
		<name>raccoon</name>
		<pose>Unspecified</pose>
		<truncated>0</truncated>
		<difficult>0</difficult>
		<bndbox>
			<xmin>81</xmin>
			<ymin>88</ymin>
			<xmax>522</xmax>
			<ymax>408</ymax>
		</bndbox>
	</object>
</annotation>
```

生成YOLO格式

```
生成两个文件 class.txt label.txt
class.txt包含了类别标签
label.txt如下：（第一位代表所属类别，后面代表矩形框的位置）
0 0.393333 0.528750 0.356667 0.942500
```

安装方法

```
pip install labelImg
lableImg
```

常用快捷键

```
w	Create a rect box
d	Next image
a	Previous image
del	Delete the selected rect box
↑→↓←	Keyboard arrows to move selected rect box
Space	Flag the current image as verified
```

2.[labelme](https://github.com/wkentaro/labelme)

以PASCAL VOC格式生成的XML文件

以COCO格式生成的json文件

```
{
  "flags": {},
  "shapes": [
    {
      "label": "person",
      "line_color": null,
      "fill_color": null,
      "points": [
        [
          191,
          107
        ],
        [
          313,
          329
        ]
      ],
      "shape_type": "rectangle"
    },
    {
      "label": "person",
      "line_color": null,
      "fill_color": null,
      "points": [
        [
          365,
          83
        ],
        [
          500,
          333
        ]
      ],
      "shape_type": "rectangle"
    }
  ],
  "lineColor": [
    0,
    255,
    0,
    128
  ],
  "fillColor": [
    255,
    0,
    0,
    128
  ],
  "imagePath": "2011_000003.jpg",
  "imageData": null
}
```

安装方法同上