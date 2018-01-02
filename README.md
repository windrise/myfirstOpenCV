## myfirstOpenCV
数字图像处理大作业之图像的显著性检测（FT算法特征融合的归一化改进方法）

## 改进依据原理
Lab颜色空间的三个分量L、a、b的取值范围不一样，L\[0 100\] ,而a,b的范围是\[-128 127\] 且3个分量的变化不一致，一幅图像的亮度变化旺旺比较大，而色度的变化不大，这样很可能导致基于这3个分量得到的显著性值不在同一个数量级，从而不能很好的体现出各个分量的作用。

## 经典算法



![1](https://github.com/windrise/myfirstOpenCV/blob/master/Raw/1.png)



![2](https://github.com/windrise/myfirstOpenCV/blob/master/Raw/2.png)

> #按照论文的方法Wl=Wa=Wb=1/3，本人并未得到很好的效果，我是直接把这单个量都取1，效果图在Imgs文件夹下

