# Computer Aided Geometric Design(CAGD)

## 资料参考
* [PPT](http://staff.ustc.edu.cn/~renjiec/CAGD_2022S1/default.htm)
* [网课](https://www.bilibili.com/video/BV1AW411F7u6)
* [GAMES 102](https://www.bilibili.com/video/BV1NA411E7Yr)
* 计算机辅助几何设计-王国瑾等人著

## 代码说明
* 依赖Eigen, OpenMesh
* 没有依赖Qt等图形库, 输入输出数据均使用obj格式, 可以到blender中查看效果(blender自带了python, 似乎用python可以更好的交互)

已实现算法:
* bezier
  * de casteljau
  * degree elevation
* B-Spline
  * NURBS
* subdivision
  * catmull clark subdivision

# 一些效果图
## bezier: de casteljau 和 升阶
![](https://raw.githubusercontent.com/zone-1614/pic/main/img/bezier.png)


## NURBS
![NURBS](https://raw.githubusercontent.com/zone-1614/pic/main/img/nurbs.png)


## catmull clark subdivision
![catmull clark subdivision](https://raw.githubusercontent.com/zone-1614/pic/main/img/catmull_clark_subdivision.png)

![catmull clark subdivision](https://raw.githubusercontent.com/zone-1614/pic/main/img/catmull_clark_subdivision2.png)