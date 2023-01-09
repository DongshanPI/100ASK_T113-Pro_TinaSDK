# 100ASK T113 PRO开发板TinaSDK支持

1. 获取Tina-sdk V2.0源码 百度网盘获取地址 链接：https://pan.baidu.com/s/13uKlqDXImmMl9cgKc41tZg?pwd=qcw7 提取码：qcw7 压缩包路径在 Tina-SDK_DevelopLearningKits-V1/DongshanNezhaSTU-TinaV2.0-SDK
2.  拷贝进Ubuntu系统内，并进行解压缩,解压命令在README里面
3.  配置开发环境，这里以ubuntu-18举例

> sudo apt-get install build-essential subversion git libncurses5-dev zlib1g-dev gawk flex quilt libssl-dev xsltproc libxml-parser-perl mercurial bzr ecj cvs unzip lib32z1 lib32z1-dev lib32stdc++6 libstdc++6 libc6:i386 libstdc++6:i386 lib32ncurses5 lib32z1 -y

4. 获取扩展支持仓库，然后加以应用

```shell
book@ubuntu1804:~$ git clone https://github.com/DongshanPI/100ASK_T113-Pro_TinaSDK.git
book@ubuntu1804:~$ cd 100ASK_T113-Pro_TinaSDK
book@ubuntu1804:~/100ASK_T113-Pro_TinaSDK$ git submodule update --init
book@ubuntu1804:~/100ASK_T113-Pro_TinaSDK$ cp ./* -rfvd ~/tina-d1-h
```

5. 应用完成，可以进入之前解压缩过的 tina-d1-h sdk目录内，执行如下命令来开始编译T113 tinasdk

```shell
book@ubuntu1804:~/tina-d1-h$ source build/envsetup.sh
Setup env done! Please run lunch next.
book@ubuntu1804:~/tina-d1-h$ lunch

You're building on Linux

Lunch menu... pick a combo:
     1. d1-h_nezha_min-tina
     2. d1-h_nezha-tina
     3. d1s_nezha-tina
     4. t113_nezha-tina

Which would you like?: 4
============================================
TINA_BUILD_TOP=/home/book/tina-d1-h
TINA_TARGET_ARCH=arm
TARGET_PRODUCT=t113_nezha
TARGET_PLATFORM=t113
TARGET_BOARD=t113-nezha
TARGET_PLAN=nezha
TARGET_BUILD_VARIANT=tina
TARGET_BUILD_TYPE=release
TARGET_KERNEL_VERSION=5.4
TARGET_UBOOT=u-boot-2018
TARGET_CHIP=sun8iw20p1
============================================
no buildserver to clean
[1] 35382
book@ubuntu1804:~/tina-d1-h$ make 
```








