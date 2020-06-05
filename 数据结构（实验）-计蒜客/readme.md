#数据结构（实验）
本项目基于计蒜客平台的“数据结构与实验”，开发的过程用到了以下工具

- VSCode(Visual Studio Code)
- WSL(Windows Subsystem for Linux)
- ubuntu18.04

## VSCode(Visual Studio Code)
###前言
VSCode 怎么说呢，一开始是打算直接用VS2017来运行计蒜客的项目的，但是后来发现，这个方法并不可行，主要的问题出在
> 函数模板已定义

报这个错误是我没想到的，后来虽然找到了解决办法：

将下面类似这样的代码放进类里面，不要进行外部声明


	template <class T>
	Node<T>::Node() {
    ptr = NULL;
    next = NULL;
	}

原因是VS不支持这种形式，寻找模板T的时候会不匹配，于是在某一个VS版本删掉了（是不是听起来很扯），于是我就舍弃VS2017了

**PS：**计蒜客默认的调试平台也是**UNIX**,所以更换本地编译环境是非常正确的行为
###安装

官网下载地址：https://code.visualstudio.com/

##WSL(Windows Subsystem for Linux)
由于我的电脑开发环境为window10，但我又不想安装VMware或者是双系统，于是就采用了微软自带的子系统wsl
###安装
####1.启用WSL
以管理员身份打开PowerShell并运行：

	dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

**重新启动**计算机以完成WSL安装
####2.下载和安装Ubuntu
下载地址：[Ubuntu18.04](https://wsldownload.azureedge.net/CanonicalGroupLimited.Ubuntu18.04onWindows_1804.2018.817.0_x64__79rhkp1fndgsc.Appx)

双击下载好的文件安装即可
###3.更换源（就是下载库通过国内的网站）
**备份list文件**

	cd /etc/apt/
	sudo cp sources.list sources.list.bak
**修改list文件**

	sudo vim sources.list
**删除里面的内容**

	:%d
	
**拷贝国内源的代码**
	
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse

**保存并退出**

	:wq

**更新软件列表**

	sudo apt-get update

####4. 安装c++编译环境
	
	sudo apt-get install g++
	sudo apt-get install gdb

至此，你已经做完了全部的准备工作，现在你需要打开VSCode的终端
输入`bash`回车，终端即变成了**wsl**的项目，想验证的话随便进入一个文件夹，比如文件管理系统，然后输入`make`,看看会不会报错就好了

##滤镜功能项目说明
由于滤镜需要额外的libpng库，这个库又非常难装，于是我这里给一个鄙人用的方法仅供参考

### 1.下载libpng和zlib的库
**libpng**

下载地址：[libpng](https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/libpng-1.6.37.tar.gz/download)

**zlib**

下载地址：[zlib](https://sourceforge.net/projects/libpng/files/zlib/1.2.11/zlib-1.2.11.tar.xz/download)
### 2.解压这两个库

解压的路径为`\数据结构-实验-计蒜客\滤镜功能`，解压后多出两个文件夹`libpng-1.6.37`、`zlib-1.2.11`

当前目录结构为
	
>include
>>pxl.h
>
>>suan_png.h
>
>>tree.h
>
> pic
>
> src
>
> Makefile
> 
> libpng-1.6.37
> 
> zlib-1.2.11

### 3.编译安装这两个库
我们打开VSCode的终端，输入`bash`进入wsl编译环境，然后在终端下输入以下命令

**zlib**

	#cd zlib-1.2.11
	#./configure
	#sudo make
	#sudo make install

**libpng**

	#cd libpng-1.6.37
	#./configure
	#sudo make
	#sudo make install

然后我们安装`pkg-config`,输入命令`sudo apt-get install pkg-congif`

### 4.编译项目
我们之前编译项目都是直接`make`对吧，但在这个工程中，我们需要进入`src`文件夹，在终端输入以下命令

	g++  -I../include -std=c++11 -Wall -Wextra -g   -c -o test.o test.cpp
	g++  -I../include -std=c++11 -Wall -Wextra -g   -c -o suan_png.o suan_png.cpp
	g++  -I../include -std=c++11 -Wall -Wextra -g   -c -o pxl.o pxl.cpp
	g++  -I../include -std=c++11 -Wall -Wextra -g   -c -o tree.o tree.cpp
	g++ -std=c++11 -lpng  test.o suan_png.o pxl.o tree.o  `pkg-config libpng16 zlib --libs --cflags` -o test

你会发现`src`文件夹下多了`test`这个文件，不用怀疑，这个就是题目给的文件