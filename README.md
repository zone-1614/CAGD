# Computer Aided Geometric Design(CAGD)

## 资料参考
* [科大的PPT](http://staff.ustc.edu.cn/~renjiec/CAGD_2022S1/default.htm)
* [GAMES 102](https://www.bilibili.com/video/BV1NA411E7Yr)
* 计算机辅助几何设计-王国瑾等人著

## 代码说明
* 依赖Eigen, OpenMesh
* 没有依赖Qt等图形库, 输入输出数据均使用obj格式, 可以到blender中查看效果

已实现算法:
* bezier
  * de casteljau
  * degree elevation
* subdivision
  * catmull clark subdivision


# 一些效果图
## bezier: de casteljau 和 升阶
![](https://raw.githubusercontent.com/zone-1614/pic/main/img/bezier.png)

## catmull clark subdivision
![catmull clark subdivision](https://raw.githubusercontent.com/zone-1614/pic/main/img/catmull_clark_subdivision.png)
