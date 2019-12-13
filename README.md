# UniversityCodeWork

## 介绍

这里边放的应该是大学其间学到的最珍贵的东西了。

大学阶段的编程作业，一般为专业课作业。夹杂的还有一些自己瞎胡整的小项目（Qt Electron Arduino）。

整这个仓库的目的一方面是交流程序（交作业），另一方面是为了4年毕业了，能回过头看一下，知道自己没白混。

## 内容组织
通用内容

>所有项目均在Linux系统下编写并运行通过，读者若在Windows系统下遇到运行问题，欢迎Issues

涉及语言包括C/C++、IDL、MATLB、Fortan、JavaScript

C/C++项目采用cmake格式组织，依赖条件如下：
- [x] cmake > 3.15
- [x] CPP_STANDARD c++14


Fortan项目在GFortran编译器下编写，语法为Fortran90以后。

IDL版本为8.3

MATLB版本为2018

Qt平台为Qt5

每个项目所用到的其他库在其项目的README文件中查看。

## 使用说明

当然，并不建议读者直复制，推荐能看懂，然后自己写。

没有限制，可随意复制使用，主代码都在每一个文件夹中。、
所有项目除特殊的大型程序分主函数和函数体外，其他的都只有一个main文件。可以下载下来为自己所用。

### Clion用户

CLion是一款很不错的跨平台的C/CPP集成开发环境（IDE），本仓库中所用C/CPP均在CLion上开发。
CLion采用了Cmake的编译方式，运行项目后，会在项目目录下生成一个`cmake-build-debug`文件夹，里面会放`CMakeCache.txt`等编译所需文件。
我在这里上传的项目没有`cmake-build-debug`文件夹，所以用CLion打开后不能直接编译运行，需要重新加载一下CMake Project，具体方法如下：

拿本仓库中摄影测量/相对定向[摄影测量/相对定向](https://gitee.com/xiaoke0o/UniversityCodeWork/tree/master/Photogrammetry)项目来说，打开我的项目是这样的

![relative_orientation](https://images.gitee.com/uploads/images/2019/1211/155027_c5e34b87_5199880.png "屏幕截图.png")

我们运行一下提示cmake-build-debug不存在，当然也就无法运行

![cmake-build-debug no found](https://images.gitee.com/uploads/images/2019/1211/155157_c0ad4c0b_5199880.png "屏幕截图.png")

我们单击菜单栏Tools->CMake->Reload CMake Project，CLion就会生成一份cmake-build-debug，然后就可以运行了。

![reload CMake Project](https://images.gitee.com/uploads/images/2019/1211/155345_e31696f2_5199880.png "屏幕截图.png")



## 参与贡献
欢迎读者提交Issues，共同进步！！

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request

