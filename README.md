# SNS3

卫星网络模拟器 3 (SNS3) 是网络模拟器 3 (ns-3) 平台的卫星网络扩展。


# License

SNS3 is distributed under the GPLv3 license.

# 安装手册（Installation Manual）

NS3 是作为 [NS3](https://www.nsnam.org/) 网络模拟器的扩展模块构建的。安装个人习惯waf安装，整体内容并未详述。英文部分可不看。

SNS3 is built as an extension module to the [NS3](https://www.nsnam.org/) network simulator; so their [installation instructions](https://www.nsnam.org/docs/release/3.29/tutorial/html/getting-started.html) apply, particularly concerning the dependencies. They are repeated here for convenience and proper integration of SNS3.

There are 2 methods to download and build (S)NS3:

*  the automated one using [bake](#bake);bake下载不作介绍
*  the manual one using [waf](#waf).



## Waf安装

安装NS3不做说明，安装好NS3后即可安装SNS3模块（NS3可先不构建，待SNS3模块（包括子模块data）下载好后一起构建也可），此扩展需要'satellite'   'traffic'  'magister-stats'三个模块内容，将三个模块添加克隆进contrib目录

你将需要:

```shell
$ cd ns-3.33/contrib

$ git clone https://github.com/sns3/sns3-satellite.git satellite
$ git clone https://github.com/sns3/traffic.git traffic
$ git clone https://github.com/sns3/stats.git magister-stats
    
```
克隆3个模块后，从contrib目录进入satellite模块，进行子模块绑定（下载到data中,大约2G）。

```shell
$ cd ns-3.29/contrib/satellite
$ git clone https://github.com/sns3/sns3-data.git data
```

然后，您需要配置 waf 并要求它构建 NS3。它将自动构建在 contrib 中找到的所有模块：

```shell
$ cd ns-3.33
$ ./waf configure -d debug --enable-examples --enable-tests
$ ./waf build -j 6
```
也可以勾选waf选项，随意定制：


```shell
$ ./waf --help
```

